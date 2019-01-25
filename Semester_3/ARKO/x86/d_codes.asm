; EBP+8  = FILE *inputFile
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile
; EBP+20 = char *codes

; new_node = tab+4*256
; root = createRoot();
; do{
;	cin>>sign>>bits_num;
;	if(EOHeader) break;
;	reg_count=bits_num/8;
;	rest = bits_num - reg_count*8;
;	if(rest==0){
;		rest=8;
;		reg_count--;
;	}
;	full = 0;
;	reg_count++;
;	node = root;
;	do{
;		if(full==0){
;			reg_count--;
;			'jz' break;
;			full=8;
;			fgetc(reg);
;		}
;		full--;
;		if( *(node+(reg>>full & 0x1)<<1) == 0){
;			*() = new_node;
;			new_node++;
;			node = &new_node;
;		}
;		else{
;			node = &( *(node+...) );
;		}
;	}
;	fgetc(reg);
;	do{
;		if(rest==1){
;			*() = sign+0x200;
;			break;
;		}
;		if( *(node+(reg>>full & 0x1)<<1) == 0){
;			*() = new_node;
;			new_node++;
;			node = &new_node;
;		}
;		else{
;			node = &( *(node+...) );
;		}
;	}//lastDo				
; }//for(sign)

ROOT equ 0xFFFF 
EOF equ -1

extern fgetc

section	.text
global decode 
extern d_test
extern d_write

decode:
d_codes:
	push	ebp
	mov	    ebp,    esp
    	
; new_node = tab+8*256
; root = createRoot();
	mov eax, [ebp+12];tab
	add eax, 8*256
	push eax			; EBP-4 = root
	add eax, 8
	push eax			; EBP-8 = new_node

; do{
loop:

;	cin>>sign>>bits_num;

	push DWORD[ebp+8];inputFile          
   	call fgetc                
	mov ebx, eax			; EBX = sign
	call fgetc			; EAX = bits_num	
	pop edx;pop inputFile
; 	if(EOHeader) break;
    	test eax, eax 
	jz epilog
	push ebx			; EBP-12 = sign
;	reg_count=bits_num/8;
	mov edx, eax	;bits_num
	shr edx, 3	;reg_count
;	rest = bits_num - reg_count*8;
	sub eax, edx	;rest
;	if(rest==0){
	jnz loop1
;		rest=8;
		mov eax, 8
;		reg_count--;
		dec edx
;	}
loop1:
;	full = 0;
	xor ecx, ecx	;full
;	reg_count++;
	inc edx
	push edx			; EBP-16 = reg_count
	push eax			; EBP-20 = rest
;	node = root;
	push DWORD[ebp-4]		; EBP-24 = node
;	do{
wc_loop:
;		if(full==0){
	test ecx, ecx
	jnz wc_loop1
;			reg_count--;
	mov eax, [ebp-16]
	dec eax
;			'jz' break;
	jz last_loop_init
	mov [ebp-16], eax
;			full=8;
	mov ecx, 8
;			fgetc(reg);
	push DWORD[ebp+8];inputFile          
   	call fgetc                
	pop ebx
;		}
wc_loop1:
;		full--;
	dec ecx
;		if( *(node+(reg>>full & 0x1)<<2) == 0){
	mov ebx, eax
	shr ebx, cl;reg>>ful
	and ebx, 0x1;()&0x1
	shl ebx, 2;()*4
	mov edx, [ebp-24];node
	lea ebx, [ebx+edx];*()
	test ebx, ebx
	jnz wc_loop2
;			*() = new_node;
	mov edx, [ebp-8];new_node
	mov [ebx], edx
;			new_node++;
	inc edx;new_node++
	mov [ebp-8], edx
;			node = &new_node;
	mov [ebp-24], edx
;		}
	jmp wc_loop
;		else{
wc_loop2:
;			node = *(node+...);
	mov [ebp-24], ebx;node = *()
;		}
	jmp wc_loop
;	}

last_loop_init:
;	fgetc(reg);
	push DWORD[ebp+8];inputFile          
   	call fgetc                
	pop ebx
;	do{
last_loop:
;		if(rest==1){
	mov ebx, [ebp-20];rest
	cmp ebx, 1
	jne last_loop1
;			*() = tab+8*sign;
	shr eax, cl;reg>>ful
	and eax, 0x1;()&0x1
	shl eax, 2;()*4
	mov edx, [ebp-24];node
	add edx, eax		;EDX = node+offset
	
	mov eax, [ebp+12];tab
	mov ebx, [ebp-12];sign
	shl ebx, 3	 ;8*sign
	add eax, ebx	 ;tab+8*sign
	mov [edx], eax
;			break;
	jmp loop_next
;		}
last_loop1:
;		if( *(node+(reg>>full & 0x1)<<2) == 0){
	mov ebx, eax
	shr ebx, cl;reg>>ful
	and ebx, 0x1;()&0x1
	shl ebx, 2;()*4
	mov edx, [ebp-24];node
	add edx, ebx		;EDX = node+offset
	mov ebx, [edx]
	test ebx, ebx
	jnz last_loop2
;			*() = new_node;
	mov ebx, [ebp-8];new_node
	mov [edx], ebx
;			new_node++;
	inc ebx
	mov [ebp-8], ebx;new_node
;			node = &new_node;
	mov [ebp-20], ebx
;		}
	jmp last_loop
;		else{
last_loop2:
;			node = &( *(node+...) );
	mov [ebp-20], ebx
;		}
	jmp last_loop
;	}//lastDo
loop_next:
	pop eax;-24
	pop eax;-20
	pop eax;-16
	pop eax;-12
	jmp loop			
; }//for(sign)

epilog:
	pop eax
	pop eax

	call d_test

	jmp d_write
;============================================
; STOS
;============================================
;
; wieksze adresy
; 
;  |                             |
;  | ...                         |
;  -------------------------------
;  | parametr funkcji - char *a  | EBP+8
;  -------------------------------
;  | adres powrotu               | EBP+4
;  -------------------------------
;  | zachowane ebp               | EBP, ESP
;  -------------------------------
;  | ... tu ew. zmienne lokalne  | EBP-x
;  |                             |
;
; \/                         \/
; \/ w ta strone rosnie stos \/
; \/                         \/
;
; mniejsze adresy
;
;
;============================================
