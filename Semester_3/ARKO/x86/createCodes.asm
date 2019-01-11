; EBP+8 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+12 = char *codes [code(32B)]

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

createCodes:
	push ebp
	mov ebp, esp

	mov eax, DWORD[ebp-8]
	mov ebx, eax
	add ebx, 256*8
	push DWORD ebx	

	sub eax, 8
	push DWORD eax
				; EBP+4 = loop_finish
				; EBP+8 = sign
;for(char sign: tab1){
create_loop:
	mov edx, DWORD[ebp+8]
	add edx, 8
	mov DWORD[ebp+8], edx
	
	mov ecx, DWORD[ebp+4]
	
	cmp ecx, edx
	je end ;TODO
;	if(tab[sign].count != 0){
	mov eax, DWORD[edx]
	test eax, eax
	jz create_loop
;		int s = sign;
	push edx		; EBP+12 = s
;		char reg_count = 28;	//7*4B = 28B
	mov cl, 28
	push cl			; EBP+16 = reg_count
;		char full = 0;
	mov ecx, 0
	push cl			; EBP+17 = full
;		int code = 0;
				; ECX = code
;		while(tab[s].parent != ROOT){
create_while:
	mov eax, WORD[edx+4]
	cmp eax, ROOT
	je create_shift
;			code |= tab[s].flag << full;
	mov eax, BYTE[edx+6]
	mov bl, BYTE[ebp+17] ;full
	shl eax, bl
	or ecx, eax
;			++full;
	inc bl
	mov BYTE[ebp+17], bl
;			if(full == 32){
	cmp bl, 32
	jne create_parent
;				codes[sign][reg_count] = code;
	mov eax, DWORD[ebp-12]	;codes
	mov ebx, DWORD[ebp+8]	;&sign
	mov edx, DWORD[ebp-8]	;tab
	sub ebx, edx
	lea eax, eax+4*ebx	;codes+32*sign
	mov bl, BYTE[ebp+16]	;reg_count
	add eax, ebx		;&codes[sign][reg_count]
	
	mov DWORD[eax], ecx
;				reg_count -= 4;
	sub bl, 4
	mov BYTE[ebp+16], bl
;				code = 0;
	mov ecx, 0
;				full = 0;
	mov BYTE[ebp+17], ecx
;			}//if
;			s = s.parent;
create_parent:
	mov edx, DWORD[ebp+12]	;s
	mov eax, WORD[edx+4]	;parent
	mov ebx, DWORD[ebp-8]
	lea ebx, eax*8+ebx	;tab+8*parent_sign
	mov DWORD[ebp+12], ebx
	jmp create_while
;		}
create_shift:
				; EBP+4 = loop_finish
				; EBP+8 = sign
				; EBP+12 = s
				; EBP+16 = reg_count
				; EBP+17 = full
				; ECX = code
;		tab[sign].bitcountincode = 8*(28-reg_count)+full;
	mov al, BYTE[ebp+16]
	mov bl, 28
	sub bl, al
	shl bl, 3
	mov al, BYTE[ebp+17]
	add al, bl		;al <- result
	
	mov ebx, DWORD[ebp+8]	;sign
	mov BYTE[ebx+7], al
;		//shift
;		char reg_count_s = 0;
	;TODO finished here	
;		for(char i = reg_count; i != 28; reg_count_s += 4){
;			code[i] <<= 32-full;
;			code[i] |= (code[i+=4] >> full);
;			codes[sign][reg_count_s] = code;
;		}
;		code[i] <<= 32-full;
;		codes[sign][reg_count_s] = code;	
;	}
epilog:
	
	pop ebp
	ret

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
