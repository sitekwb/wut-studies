; EBP+8  = FILE *inputFile #NOTUSED
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile #NOTUSED
; EBP+20 = char *codes 

;for(char sign: tab1){
;	if(tab[sign].count != 0){
;		int s = sign;
;		char reg_count = 28;	//7*4B = 28B
;		char full = 0;
;		int code = 0;
;		while(tab[s].parent != ROOT){
;			code |= tab[s].flag << full;
;			++full;
;			if(full == 32){
;				codes[sign][reg_count] = code;
;				reg_count -= 4;
;				code = 0;
;				full = 0;
;			}
;			s = s.parent;
;		}
;		tab[sign].bitcountincode = 8*(28-reg_count)+full;
;		//shift
;		char reg_count_s = 0;
;		for(char i = reg_count; i != 28; reg_count_s += 4){
;			code[i] <<= 32-full;
;			code[i] |= (code[i+=4] >> full);
;			codes[sign][reg_count_s] = code;
;		}
;		code[i] <<= 32-full;
;		codes[sign][reg_count_s] = code;	
;	}
;}
	


ROOT equ 0xFFFF     ; 2B
MAX  equ 0xFFFFFFFF ; 4B 

section	.text
global createCodes 
extern test
extern writeHeader

createCodes:
	mov eax, DWORD[ebp+12]
	mov ebx, eax
	add ebx, 256*8
	push DWORD ebx	

	sub eax, 8
	push DWORD eax
				; EBP-4 = loop_finish
				; EBP-8 = sign
;for(char sign: tab1){
create_loop:
	mov edx, DWORD[ebp-8]	;sign
	add edx, 8
	mov DWORD[ebp-8], edx
	
	mov ecx, DWORD[ebp-4]	;end
	
	cmp ecx, edx		; ? sign==end
	je epilog
;	if(tab[sign].count != 0){
	mov eax, DWORD[edx]
	test eax, eax
	jz create_loop
;		int s = sign;
	push edx		; EBP-12 = s
; push codes[sign]
	mov eax, DWORD[ebp+20]	;codes
	mov ebx, DWORD[ebp-8]	;&sign
	mov edx, DWORD[ebp+12]	;tab
	sub ebx, edx		;sign-tab
	shl ebx, 2
	add eax, ebx	;codes+32*sign
	
	push eax		; EBP-16 = codes[sign]
;		char reg_count = 28;	//7*4B = 28B
	push BYTE 28			; EBP-20 = reg_count
;		char full = 0;
	xor ecx, ecx	; ecx=0
	push BYTE 0			; EBP-21 = full
;		int code = 0;
				; ECX = code

;		while(tab[s].parent != ROOT){
create_while:
	mov ax, WORD[edx+4]
	cmp eax, ROOT
	je create_shift
;			code |= tab[s].flag << full;
	mov al, BYTE[edx+6] ;flag
	mov bl, BYTE[ebp-21] ;full
	shl eax, ebx 
	or ecx, eax
;			++full;
	inc bl
	mov BYTE[ebp-21], bl
;			if(full == 32){
	cmp bl, 32
	jne create_parent
;				(codes[sign])[reg_count] = code;
	mov eax, DWORD[ebp-16]	;codes[sign]
	mov bl, BYTE[ebp-20]	;reg_count
	add eax, ebx		;&codes[sign][reg_count]
	
	mov DWORD[eax], ecx
;				reg_count -= 4;
	sub bl, 4
	mov BYTE[ebp-20], bl
;				code = 0;
	xor ecx, ecx
;				full = 0;
	mov BYTE[ebp-21], ecx
;			}//if
;			s = s.parent;
create_parent:
	mov edx, DWORD[ebp-12]	;s
	mov ax, WORD[edx+4]	;parent
	mov ebx, DWORD[ebp+12]   ;tab
	shl eax, 3
	add ebx, eax	;tab+8*parent_sign
	mov DWORD[ebp-12], ebx	;s=s.parent
	jmp create_while
;		}
create_shift:
				; EBP-4 = loop_finish
				; EBP-8 = sign
				; EBP-12 = s
				; EBP-16 = reg_count
				; EBP-17 = full
				; ECX = code
;		tab[sign].bitcountincode = 8*(28-reg_count)+full;
	mov dl, BYTE[ebp-20] 	;reg_count
	mov bl, 28	     	;28	
	sub bl, dl	     	;28-reg_count
	shl bl, 3		;8*(28-reg_count)
	mov al, BYTE[ebp-21]	;full
	add al, bl		;al <- result
	
	mov ebx, DWORD[ebp-8]	;sign
	mov BYTE[ebx+7], al	;sign.bitcountincode = result
;		//shift
;		char reg_count_s = 0;
	xor ecx, ecx		; reg_count_s = 0
	push cl		; EBP-22 = reg_count_s
			; EDX = i = reg_count
shift_while:
;		for(char i = reg_count; i != 28; reg_count_s += 4){
	cmp edx, 28
	je shift_epilog
	
	mov ebx, DWORD[ebp-16]	;codes[sign]
;			code[i] <<= 32-full;
	lea eax, DWORD[ebx+edx]	;codes[sign][i]
	mov bl, BYTE[ebp-21]	;full
	mov cl, 32
	sub cl, bl		;32-full
	shl eax, ecx		;code[i] 
;			code[i] |= (code[i+=4] >> full);
	add dl, 4		;i+=4
	mov ecx, DWORD[ebp-16]	;codes[sign]
	lea ecx, DWORD[ecx+dl]	;codes[sign][i+=4]
	shr ecx, ebx		;code[i+=4] >> full
	or  eax, ecx		;code
;			codes[sign][reg_count_s] = code;
	mov ecx, DWORD[ebp-16]	;codes[sign]
	mov bl,  BYTE[ebp-22]	;reg_count_s
	lea DWORD[ecx+ebx], eax
;	from for: reg_count_s+=4
	add bl, 4
	mov BYTE[ebp-22], bl
;		}
	jmp shift_while
shift_epilog:
;			code[i] <<= 32-full;
	lea eax, DWORD[ebx+edx]	;codes[sign][i]
	mov bl, BYTE[ebp-21]	;full
	mov cl, 32
	sub cl, bl		;32-full
	shl eax, ecx		;code[i] 
;			codes[sign][reg_count_s] = code;
	mov ecx, DWORD[ebp-16]	;codes[sign]
	mov bl,  BYTE[ebp-22]	;reg_count_s
	lea DWORD[ecx+ebx], eax
;	}
	pop al	;reg_count_s
	pop al	;full
	pop al	;reg_count
	pop eax ;codes[sign]
	pop eax	;s
	jmp create_loop
epilog:
				; EBP-4 = loop_finish
				; EBP-8 = sign
	pop eax		;loop_finish
	pop eax		;sign
	
	call test
	
	pop ebp
	ret
	;jmp writeHeader	


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
