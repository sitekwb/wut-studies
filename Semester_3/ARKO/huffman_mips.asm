.eqv BLOCK 2048
.eqv BLOCKRES 16384

.data
array:		.word		0:1536	# 3 words * 512 places			6 kB
temp:		.byte		0:33	# 256 bits = 32 bytes = 8 words		32 B
result:		.byte		0:BLOCKRES	#				BLOCK B
buffer:		.byte		0:BLOCK	#					BLOCK B
path:		.byte		0:32	#					32 B
q_start:	.asciiz		"\n		---HUFFMAN (DE)CODER---\n"
q_error:	.asciiz		"\n->Error! Try again!"
q_readpath:	.asciiz		"\nEnter file path to (de)code: " 
q_writepath:	.asciiz		"\nEnter file path to write in: "
q_decoding:	.asciiz		"Do you want to decode or encode file? (1=encode text / 0=decode binary): "
.text
main:
				#	---array---
#			0		4		6		8		10	  11		
# ind/sign(512 options) | Wcount	| Hchild0	| Hchild1	| Hparent(2half)| B is1Ch | BisNotRoot
# 1		   	| 3		| 243		| 3		| 15		| 1	  | 0
# 2		   	| 4		| 13		| 8		| 4		| 0	  | 0
# 3		   	| 2		| 4		| 35		| 1		| 0	  | 0
# 4		   	| 6		| 0		| 15		| 8		| 0	  | 0
	# print title
	la $a0, q_start 
	li $v0, 4
	syscall

	# print fileread prompt
	la $a0, q_readpath
	li $v0, 4
	syscall

	# read path to file
	li $v0, 8
	la $a0, path
	li $a1, 30
	syscall
	
	la $t0, path
null_terminate_loop:
	lbu $t1, ($t0)
	bge $t1, ' ', next_term_loop
	beqz $t1, program1
	sb $zero, ($t0)
	b program1
next_term_loop:
	addiu $t0, $t0, 1
	b null_terminate_loop
program1:
	# open file
	li $v0, 13
	la $a0, path
	li $a1, 0 		#readonly
	li $a2, 0
	syscall
	
	
	# check if success (if file descriptor >=0 )
	blt $v0, 0, error
	
	move $s0, $v0 # copy file descriptor		# $s0 = file_descriptor
	
	# de/en -code decision

	# print decision prompt
	la $a0, q_decoding
	li $v0, 4
	syscall

	# read decision character
	li $v0, 12
	syscall 
	
	#check decision
	beq $v0, '0', decode
	bne $v0, '1', error #if not good input
	
	li $s2, 0				# $s2 = lastIteration	
block:
	#read text to buffer
	bnez $s2, huffman_init		# if(was_last_iteration) => huffman
	
	move $a0, $s0
	li $v0, 14
	la $a1, buffer
	li $a2, BLOCK
	syscall
	
	bltz $v0, error
	subiu $s2, $v0, BLOCK		# if(chars_num != wanted_chars_num) => lastIteration!=0
	la $t4, ($v0) 				# $t4 = number of characters read
	
	#ENCODE text
	la $t0, buffer				# $t0 = buf_ptr
enter_length_loop:
	beqz $t4, block		# if(reverse_i==0) => no more signs to read => huffman_ready
	lbu $t2, ($t0)				# $t2 = sign
	mulu $t1, $t2, 12			# $t1 = array_offset = 12*sign
	la $t3, array($t1)			# $t3 = count_ptr
	lw $t2, ($t3)				#!$t2 = count
	addiu $t2, $t2, 1		# count++
	sw $t2, ($t3)			# overwrite count
	addiu $t0, $t0, 1		# buf_ptr++
	subiu $t4, $t4, 1		# chars--
	b enter_length_loop

# BUILDING HUFFMAN TREE
huffman_init:
	# close file
	li $v0, 16
	move $a0, $s0
	syscall

	la $t7, array + 3072			# $t0 = node_end_ptr
huffman:
	la $t0, array + 6144			# $t0 = array_end 6144 = 512*12 [bytes]
	la $t1, array + -12			# $t1 = array_it
	la $s0, array
	li $t3, 0x0FFFFFFF			# $t3 = *minest
	li $t4, 0x0FFFFFFF			# $t4 = *min
	li $t5, 0				# $t5 = &minest
	li $t6, 0				# $t6 = &min
# SEARCH 2 ROOTS WITH THE SMALLEST COUNT
search_root:
	addiu $t1, $t1, 12		# array_it++
	beq $t1, $t0, search_root_end	# if ( array_it == array_end ) => break;
	lbu $t2, 11($t1)			# $t2 = array_it->isNotRoot
	bnez $t2, search_root		# if( isNotRoot ) => omit and continue
	
	lw $t2, ($t1)				#!$t2 = it->count
	beqz $t2, search_root		# if( count == 0 ) => not a node, omit and continue
	
	blt $t2, $t3, minest		# if ( it->count < *minest )	minest;
	blt $t2, $t4, min		# if ( ptr->count < *min )	min;
	b search_root
minest:
	move $t6, $t5			# &min = &minest
	move $t4, $t3			# *min = *minest
	move $t5, $t1			# &minest = ptr
	move $t3, $t2			# *minest = *ptr
	b search_root
min:
	move $t6, $t1			# &min = ptr
	move $t4, $t2			# *min = *ptr
	b search_root
search_root_end:
	beqz $t6, huffman_ready		# if( &min == 0 ) only one root => huffman ready
	
# ENTER NEW ROOT AS PARENT OF FOUND ROOTS
push_root:
					# $t7 = node_end
					# $t3 = *minest
					# $t4 = *min
					# $t5 = &minest
					# $t6 = &min
					# free: $t0, $t1, $t2, $s..
	addu $t3, $t3, $t4			#!$t3 = new_count; $t4 free
	sw $t3, ($t7)			#s store new_count
	
	# &min is 1child and isNotRoot
	li $t0, 1
	sb $t0, 10($t6)
	sb $t0, 11($t6)
	# &minest isNotRoot
	sb $t0, 11($t5)
	# &min, &minest parent
	subu $t3, $t7, $s0
	divu $t3, $t3, 12
	sh $t3, 8($t5)
	sh $t3, 8($t6)
	
	# change &min and &minest to indexes of 0child and 1child
		# $s0 = array
	subu $t5, $t5, $s0
	subu $t6, $t6, $s0
	divu $t5, $t5, 12
	divu $t6, $t6, 12
	addiu $t6, $t6, 0x100		# offset!!!
	addiu $t5, $t5, 0x100		# offset!!!
	# store 0child and 1child
	sh $t5, 4($t7)
	sh $t6, 6($t7)
	# node_end++
	addiu $t7, $t7, 12
	b huffman
huffman_ready:
	#read from file by block => read sign => find code => write to result
	
	
	# open file
	li $v0, 13
	la $a0, path
	li $a1, 0 		#readonly
	li $a2, 0
	syscall
	
	# check if success (if file descriptor >=0 )
	blt $v0, 0, error
	
	move $s0, $v0 # copy file descriptor		# $s0 = file_descriptor
	
	# print fileread prompt
	la $a0, q_writepath
	li $v0, 4
	syscall

	# read path to file
	li $v0, 8
	la $a0, path
	li $a1, 30
	syscall
	
	la $t0, path
null_terminate_loop2:
	lbu $t1, ($t0)
	bge $t1, ' ', next_term_loop2
	beqz $t1, program2
	sb $zero, ($t0)
	b program2
next_term_loop2:
	addiu $t0, $t0, 1
	b null_terminate_loop2
program2:
	# open file
	li $v0, 13
	la $a0, path
	li $a1, 1 		# write-only with create
	li $a2, 0
	syscall
	
	# check if success (if file descriptor >=0 )
	blt $v0, 0, error
	
	move $s1, $v0 # copy file descriptor		# $s1 = file_descriptor-write
	
# WRITE HEADER OF FILE AS [SIGN(B)][LENTH OF CODE IN BITS (B)][CODE (UP TO 8B)]
write_header:
					# $s5 = new_empty_res = num (from loop before)
	
	# declare vars
	li $t0, 0xFF 				# $t0 = number of characters read
	li $t1, 0				# $t1 = bit_counter
	la $t2, result				# $t2 = result_it
						# $t3 = empty_bits in this byte of result (defined in write_sign below)
	la $t4, temp+31				# $t4 = temp_rev_it
h_write_sign:
	li $s2, 0				# $s2 = busy_bits in this byte of temp
	li $t3, 8				# empty bits = 8
	bltz $t0, h_write_header_end		# 0 signs left => write next block
	la $t6, temp+32
	la $t4, temp
h_zero_temp:
	sb $zero, ($t4)
	addiu $t4, $t4, 1
	bne $t6, $t4, h_zero_temp
h_write_sign1:
	subiu $t4, $t4, 1		# decrement temp_rev_it, so it equals temp+31
						# $t0 = sign or too much
	# get array ptr
	mulu $t6, $t0, 12		# sign *= 12
	la $t6, array($t6)			# $t6 = array_ptr
	
	lw $t7, ($t6)				# $t7 = ptr->count
	beqz $t7, h_next_sign		# if( count == 0 ) => ommit sign
h_write_bit:
	lbu $t7, 11($t6)			# $t7 = isNotRoot
	beqz $t7, h_write_sign_end	# if root => continue write_sign
	# if not root => write is1Child to temp => set $t6 to parent_ptr => continue write_bit
	lbu $t7, 10($t6)			# $t7 = is1Ch
	bne $s2, 8, h_write				# if ( are empty bits ) => write
	# previous byte
	subiu $t4, $t4, 1		# next byte
	li $s2, 0			# busy_bits = 0
h_write:
	lbu $s3, ($t4)				# $s3 = temp_byte
	sllv $t7, $t7, $s2		# shift left bit by number of busy bits  -------1 => ----1---
	or $s3, $s3, $t7		# temp_byte += is1Ch
	sb $s3, ($t4)			# store temp_byte
	addiu $s2, $s2, 1		# busy_bits++
	addiu $t1, $t1, 1		# bit_counter++
h_getParent:
	lhu $t6, 8($t6)				# $t7 = it->parent
	# get parent's array_ptr
	mulu $t6, $t6, 12
	la $t6, array($t6)
	b h_write_bit
h_write_sign_end:
	# FREE: t5, t6, t7, s3+
						# REPEAT
						# $t0 = number of characters read
						# $t1 = buf_it
						#= $t2 = result_it
						# $t3 = empty_bits in this byte of result
						#= $t4 = temp_rev_it
						# $s2 = busy_bits in this byte of temp
	
	# prepare for next sign after write_sign_end					
	sb $t0, ($t2)			# store second part of sign
	sb $t1, 1($t2)			# store bits_counter in result
	li $t1, 0
	addiu $t2, $t2, 2
	subiu $t0, $t0, 1		# chars --
	# HERE busy_temp <= empty_result
	
	# $t7 temp: 	-------1 | 11111111  1
	# $t6 result: 	1111---- | --------  4
	subu $t5, $t3, $s2			# $t5 = x = empty_res - busy_temp
	li $s5, 8
	subu $s5, $s5, $t5			# new empty_res = empty_res - busy_temp
	move $s4, $t4
	la $t4, temp + 31
h_left:
	lbu $t6, ($t2)				# $t6 = result_byte
	lbu $t7, ($s4)				# $t7 = temp_byte
	sllv $t7, $t7, $t5
	or $t6, $t6, $t7		# enter bits to result
	
	lbu $t7, 1($s4)			# load next temp byte
	srlv $s3, $t7, $s5			# $s3 = shift right next_temp_byte > (8-x)
	or $t6, $t6, $s3		# enter last bits of this result_byte
	
	sb $t6, ($t2)			# store result
	addiu $t2, $t2, 1		# result_it ++
	beq $s4, $t4, h_write_sign	# if ( temp_it == last_temp ) break;
	addiu $s4, $s4, 1		# temp_it ++
	b h_left
h_next_sign:
	subiu $t0, $t0, 1		# chars --
	b h_write_sign

h_write_header_end:
						# REPEAT
						# $t0 = number of characters read
						# $t1 = buf_it
						# $t2 = result_it
						# $t3 = empty_bits in this byte of result
						# $t4 = temp_rev_it
						# $s2 = busy_bits in this byte of temp
	# FINISH HEADER WITH FF LENGTH (not possible normally)
	li $t0, 0xFF
	sb $t0, ($t2)				# finishing sign
	sb $t0, 1($t2)				# x2
	addiu $t2, $t2, 2			# $t2 = overbits_ptr
	
	# WRITE TO FILE
	# write result to file
	move $a0, $s1			# file decriptor
	la $a1, result
	subu $a2, $t2, $a1		# num of characters = overbits_ptr - result_start
	li $v0, 15
	syscall
	
	# clear result
h_clear_result:
	sb $zero, ($a1)
	addiu $a1, $a1, 1
	bne $a1, $t2, h_clear_result
	
	
	
#WRITE BLOCK 
	li $s7, 0
	li $s6, 0					# $s6 = overbits
	li $s5, 8					# $s5 = empty_result
write_block:
	bnez $s7, finish		# if(was_last_iteration) => terminate
	
	#read text to buffer
	move $a0, $s0
	li $v0, 14
	la $a1, buffer
	li $a2, BLOCK
	syscall
	
	bltz $v0, error
	subiu $s7, $v0, BLOCK		# if(chars_num != wanted_chars_num) => lastIteration!=0
	
	
	
	# enter overbits into result
	sb $s6, result
					# $s5 = new_empty_res = num (from loop before)
	
	# declare vars
	la $t0, ($v0) 				# $t0 = number of characters read
	la $t1, buffer				# $t1 = buf_it
	la $t2, result				# $t2 = result_it
						# $t3 = empty_bits in this byte of result (defined in write_sign below)
write_sign:
	la $t4, temp+32				# $t4 = temp_rev_it
	li $s2, 0				# $s2 = busy_bits in this byte of temp
	move $t3, $s5			# set empty_res to new_empty_res
	beqz $t0, write_block_end		# 0 signs left => write next block
	la $t6, temp
zero_temp:
	sb $zero, ($t6)
	addiu $t6, $t6, 1
	bne $t6, $t4, zero_temp
write_sign1:
	subiu $t4, $t4, 1		# decrement temp_rev_it, so it equals temp+31
	lbu $t6, ($t1)				# $t6 = sign
	# get array ptr
	mulu $t6, $t6, 12		# sign *= 12
	la $t6, array($t6)			# $t6 = array_ptr
	
write_bit:
	lbu $t7, 11($t6)			# $t7 = isNotRoot
	beqz $t7, write_sign_end	# if root => continue write_sign
	# if not root => write is1Child to temp => set $t6 to parent_ptr => continue write_bit
	lbu $t7, 10($t6)			# $t7 = is1Ch
	bne $s2, 8, write				# if ( are empty bits ) => write
	# previous byte
	subiu $t4, $t4, 1		# next byte
	li $s2, 0			# busy_bits = 0
write:
	lbu $s3, ($t4)				# $s3 = temp_byte
	sllv $t7, $t7, $s2		# shift left bit by number of busy bits  -------1 => ----1---
	or $s3, $s3, $t7		# temp_byte += is1Ch
	sb $s3, ($t4)			# store temp_byte
	addiu $s2, $s2, 1		# busy_bits++
getParent:
	lhu $t6, 8($t6)				# $t7 = it->parent
	# get parent's array_ptr
	mulu $t6, $t6, 12
	la $t6, array($t6)
	b write_bit
write_sign_end:
	# FREE: t5, t6, t7, s3+
						# REPEAT
						# $t0 = number of characters read
						# $t1 = buf_it
						#= $t2 = result_it
						# $t3 = empty_bits in this byte of result
						#= $t4 = temp_rev_it
						# $s2 = busy_bits in this byte of temp
	
	# prepare for next sign after write_sign_end					
	addiu $t1, $t1, 1		# buf_it++
	subiu $t0, $t0, 1		# chars --
	# if( busy_temp > empty_result ) 
	# temp: 	---11111    5
	# result: 	1111111-    1
	sub $t5, $s2, $t3			# $t5 = x = busy_temp - empty_result
	la $s4, temp + 31			# $s4 = last_byte_temp
						# $t4 = temp_it
	
	li $s3, 8
	subu $s3, $s3, $t5			# $s3 = 8-x
	move $s5, $s3			
	
	lbu $t6, ($t2)				# $t6 = result_byte
	lbu $t7, ($t4)				# $t7 = temp_byte
	bgtz $t5, right			# temp is bigger than places in res => we must shift right temp
	# HERE busy_temp <= empty_result
	
	# $t7 temp: 	-------1 | 11111111  1
	# $t6 result: 	1111---- | --------  4
	subu $t5, $t3, $s2			# $t5 = x = empty_res - busy_temp
	li $t8, 8
	subu $t8, $t8, $t5		# $t8 = 8-x
	move $s5, $t5			# new empty_res = empty_res - busy_temp
left:
	lbu $t6, ($t2)				# $t6 = result_byte
	lbu $t7, ($t4)				# $t7 = temp_byte
	sllv $t7, $t7, $t5
	or $t6, $t6, $t7		# enter bits to result
	
	lbu $t7, 1($t4)			# load next temp byte
	srlv $s3, $t7, $t8			# $s3 = shift right next_temp_byte > (8-x)
	or $t6, $t6, $s3		# enter last bits of this result_byte
	
	sb $t6, ($t2)			# store result
	
	beq $s4, $t4, write_sign	# if ( temp_it == last_temp ) break;
	addiu $t2, $t2, 1		# result_it ++
	addiu $t4, $t4, 1		# temp_it ++
	b left
right:
						# $t6 = result_byte
						# $t7 = temp_byte
	srlv $t7, $t7, $t5
	or $t6, $t6, $t7		# enter bits to result
	
	sb $t6, ($t2)			# store result
	
	lbu $t7, ($t4)			# $t7 = temp_byte
	sllv $t6, $t7, $s5			# $t7 = temp_byte < (8-x)
	lbu $t7, 1($t4)
	
	sb $t6, 1($t2)
	
	addiu $t2, $t2, 1		# result_it ++
	
	beq $s4, $t4, write_sign	# if ( temp_it = last_temp ) break;
	
	addiu $t4, $t4, 1		# temp_it ++
	b right
write_block_end:
						# REPEAT
						# $t0 = number of characters read
						# $t1 = buf_it
						# $t2 = result_it
						# $t3 = empty_bits in this byte of result
						# $t4 = temp_rev_it
						# $s2 = busy_bits in this byte of temp
	# write only full bytes
	# ommit last byte in sign and wait till it will be full
	# don't write last byte of each block => remember and treat as first byte of next
	lbu $s6, ($t2)			# save overbits in s6
	# write result to file
	move $a0, $s1			# file decriptor
	la $a1, result
	subu $a2, $t2, $a1		# num of characters = overbits_ptr - result_start

	li $v0, 15
	syscall
	
	# save overbits
	
	
	b write_block
finish:
	# write overbits to file
	beq $s5, 8, close_file
	sb $s6, result
	li $v0, 15
	move $a0, $s1
	la $a1, result
	li $a2, 1
	syscall
	
	#write number of rubbish bits at last bit
	li $v0, 15
	sb $s5, result
	syscall
	
close_file:
	move $a0, $s0
	li $v0, 16
	syscall
	
	move $a0, $s1
	syscall
terminate:
	li $v0, 10
	syscall
error:
	# print error info 
	la $a0, q_error 
	li $v0, 4
	syscall
	b terminate
	
	
	#DECODE TEXT

decode: # labels with prefix d


# DECODE HEADER OF FILE AND BUILD HUFFMAN TREE ON BASE OF IT
d_header:
					# $s5 = new_empty_res = num (from loop before)
	#read header from file
	move $a0, $s0
	li $v0, 14
	la $a1, buffer
	li $a2, BLOCK
	syscall
	
	move $t9, $v0				# $t9 = number of bytes read
	subu $a3, $t9, BLOCK			# $a3 = last_iteration
	
	# declare vars
	la $s1, buffer + -1			# $t0 = buf_it
d_loop: # loop entering letter and their parents
	la $t0, 1($s1)				# next_sign_ptr = last_byte_ptr + 1
	
	lbu $t2, ($t0)				# $t2 = sign
	
	mulu $s7, $t2, 12
	la $s7, array($s7)			# $s7 = array_ptr
	
	lbu $t4, 1($t0)				# $t4 = bits_num
	beq $t4, 0xFF, d_huffman_ready
	sw $t4, ($s7) 		# store length as count
	
	li $t1, 8
	divu $t4, $t1				# lo: bytes_num; hi: busy_bits
	mfhi $t3				
	subu $t3, $t1, $t3			# $t3 = empty_bits
	mflo $t1				# $t1 = bytes_num
	
	#IF all bits of this byte used
	bne $t3, 8, d_loop2
	#THEN
	li $t3, 0
	subiu $t0, $t0, 1		# buf_it--
d_loop2:
	addu $t0, $t0, $t1			# t1 FREE
	addiu $t0, $t0, 2			# $t0 = last_byte_ptr
	move $s1, $t0				# $s1 = last_byte_ptr
	move $t6, $t3				# $t6 = which_bit (empty_bits at start)
	
d_inner_loop: # iterates through next code values (reversely)
	beqz $t4, d_loop		# checkes length (decremented 3 lines down)
	lbu $t7, ($t0)			# $t7 = code_byte
	srlv $t7, $t7, $t6
	and $t7, 1			# $t7 = code_bit
	sb $t7, 10($s7)			# ptr->is1Child = code_bit
	li $t1, 1
	sb $t1, 11($s7)			# ptr->isNotRoot = 1 or 0 if root
	sll $t7, $t7, 1			# code *= 2
	
	addiu $t6, $t6, 1		# which_bit++
	bne $t6, 8, d_inner_loop2	# if all bits of this byte used
	li $t6, 0
	subiu $t0, $t0, 1		# buf_it--
d_inner_loop2:
	subiu $t4, $t4, 1		# length--
	# search for node with this length
	la $t5, array+3060			# $t5 = array_ptr (start of non-signs)
d_search_loop: #searches for existing parent or adds new
	addiu $t5, $t5, 12		# array_ptr++
	addu $s2, $t7, $t5		# $s2 = ptr + offset
	#check if not end of array
	lw $s3, ($t5)
	lw $s4, 4($t5)
	or $s3, $s3, $s4	# is 0 if all values are 0
	beqz $s3, d_add_node	# if( isEmpty( node ) ) => add_node
	
	lw $s3, ($t5)			# $s3 = ptr->length
	
	bne $s3, $t4, d_search_loop	# if ( ptr->length != length ) continue
	
	lhu $s4, 4($s2)			# $s2 = loads 0child/1child
	bnez $s4, d_search_loop		# if some other child is busy here => continue searching	
	#check if it is right node; then write index in it
	beqz $t4, d_approved		# if( isRoot() ) => approve
	
	
	move $s6, $t0				# $s6 = new buf_it
	move $t3, $t6				# $t3 = new which_bit
	la $s3, -1($t4)				# $s3 = new length
	
	la $s4, array
	subu $s4, $t5, $s4
	divu $s4, $s4, 12			# $s4 = new index
	
	move $t1, $t5				# $t1 = new array_ptr
	lhu $s5, 8($t1)				# get parent
d_check:
	# search for node which has 0/1child equal my node => till root
	mulu $t1, $s5, 12
	la $t1, array($t1)			# $t1 = new array_ptr
	
	move $a0, $s5			# CURRENT
	lhu $s5, 8($t1)			# PARENT	# get new's parent
	
	bne $t3, 8, d_check2	# if all bits of this byte used
	li $t3, 0
	subiu $s6, $s6, 1		# buf_it--
d_check2:
	lbu $t8, ($s6)			# $t8 = code_byte
	srlv $t8, $t8, $t3
	andi $t8, 1			# $t8 = code_bit
	addiu $t3, $t3, 1	# which_bit++
	sll $t8, $t8, 1			# code *= 2
	addu $t8, $t8, $t1		# $t8 = ptr + ch_offset
	lhu $t8, 4($t8)			# $t8 = 0/1Child
	subiu $t8, $t8, 0x100
	bne $t8, $s4, d_search_loop
	beqz $s5, d_approved		# root found
	move $s4, $a0			# $s4 = CHILD
	b d_check
d_approved:
	#get sign index:
	# $t5 = array_ptr to insert
	# $s2 = array_ptr with offset
	addiu $t2, $t2, 0x100
	sh $t2, 4($s2)		# store child
	#get index
	la $t2, array
	subu $t2, $t5, $t2
	divu $t2, $t2, 12
	sh $t2, 8($s7)			# store parent of child as this
	b d_loop
d_add_node:
	sw $t4, ($t5)			# ptr->length = length
	addiu $t2, $t2, 0x100		# add child offset
	sh $t2, 4($s2)			# store child
	#get index
	la $t2, array
	subu $t2, $t5, $t2
	divu $t2, $t2, 12
	sh $t2, 8($s7)			# store parent of child as this
	# set pointer to this
	move $s7, $t5
	b d_inner_loop

next_term_loop3:
	addiu $t2, $t2, 1
	b null_terminate_loop3
d_huffman_ready:
	addiu $t0, $t0, 2	# ommit 0xFF finishing byte
	# find number of bytes to read
	la $t1, buffer
	subu $t1, $t0, $t1
	subu $s6, $t9, $t1	# $s6 = bytes_left


	# print fileread prompt
	la $a0, q_writepath
	li $v0, 4
	syscall

	# read path to file
	li $v0, 8
	la $a0, path
	syscall
	
	la $t2, path
null_terminate_loop3:
	lbu $t1, ($t2)
	bge $t1, ' ', next_term_loop3
	beqz $t1, program3
	sb $zero, ($t2)
program3:
	# open file
	li $v0, 13
	la $a0, path
	li $a1, 1		#writeonly with create	
	syscall

	# check if success (if file descriptor >=0 )
	bltz $v0, error
	
	move $s1, $v0 # copy file descriptor
	
	
# SEARCH FOR ROOT IN HUFFMAN TREE
	# 1. search for root
	la $t1, array + -12	# $t1 = array_ptr
d_search_root:	# $t0 = ptr to first 0/1; rest FREE
	addiu $t1, $t1, 12
	lw $t2, ($t1)		# ptr->length
	bnez $t2, d_search_root
	lw $t2, 4($t1)		# ptr->childs
	beqz $t2, d_search_root
	# HERE t1 = root
	
	move $s7, $a3
	la $s2, array + 3072
	b d_block_init
	
	# GET BLOCK AND DECODE IT TO ANOTHER FILE
d_block:
	bnez $s7, close_file		# if(was_last_iteration) => terminate
	
	#read text to buffer
	move $a0, $s0
	li $v0, 14
	la $a1, buffer
	li $a2, BLOCK
	syscall
	
	bltz $v0, error
	subiu $s7, $v0, BLOCK		# if(chars_num != wanted_chars_num) => lastIteration!=0
	move $s6, $v0			# $s6 = bytes left
	
	la $t0, buffer
	la $s3, result
	b d_write_loop
d_block_init: # as first iteration it continues buffer
	la $s3, result		# $s3 = result_ptr
	move $t3, $t1		# $t3 = ptr = root_ptr
	li $t5, 7		# $t5 = which_bit_rev
d_write_loop_prologue:
	la $t3, ($t1)				# ptr = root_ptr
	beqz $s6, d_to_file		# if 0 bytes left in this block => next block
d_write_loop:
					# $t0 = buffer_ptr
					# $t1 = root_ptr
					# $t3 = ptr
	# 2. if isset(sign) => write; else find child
	bge $t3, $s2, d_write_child		# if (!isset(sign)) => find child and continue
	
	# if (isset(sign)) => write sign to result_ptr
	la $t7, array
	subu $t3, $t3, $t7
	divu $t3, $t3, 12
	sb $t3, ($s3)		# store sign in result
	addiu $s3, $s3, 1	# result_ptr++
	
	
	b d_write_loop_prologue
d_write_child:		
	beqz $s6, d_to_file
			
	lbu $t2, ($t0)			# $t2 = byte from buffer
	srlv $t2, $t2, $t5	# shift right by which_bit_rev
	andi $t2, 1		# mask, getting last bit
	bnez $t5, d_write_child3
	# if all bits used => increment buffer
	addiu $t0, $t0, 1	# buf++
	subiu $s6, $s6, 1	# bytes_left--
	
	beqz $s7, d_write_child2	# if ( not last iteration ) => continue
	beq $s6, 2, d_last_byte		# if ( last_iteration && last_info_byte ) => escape
d_write_child2:
	li $t5, 8		# which_bit = 8
d_write_child3:
	subiu $t5, $t5, 1	# which_bit--
	# find child: 0/1child in t2
	sll $t2, $t2, 1		# child *= 2
	addu $t2, $t2, $t3	# $t2 = ptr + child_offset
	lhu $t2, 4($t2)		# get child index
	subiu $t2, $t2, 0x100
	# get array ptr
	mulu $t3, $t2, 12
	la $t3, array($t3)
	
	b d_write_loop
	
d_last_byte:
	lbu $s6, ($t0)		# $s6 = last_info_byte
	lbu $s4, 1($t0)		# $s4 = rubbish_num
	srlv $s6, $s6, $s4	# shift right by rubbish_num
	sb $s6, ($t0)		# store byte in buffer
	
	li $s5, 8
	subu $t5, $s5, $s4	# which_bit = 9-rubbish_num
	li $s6, 1		# only one info byte left
	b d_write_child3
	
d_to_file:
	li $v0, 15
	move $a0, $s1		# file descriptor
	la $a1, result
	subu $a2, $s3, $a1	# $a2 = bytes_num
	syscall
	
d_delete_loop:
	sb $zero, ($a1)
	addiu $a1, $a1, 1
	subiu $a2, $a2, 1
	bnez $a2, d_delete_loop
	b d_block
				
