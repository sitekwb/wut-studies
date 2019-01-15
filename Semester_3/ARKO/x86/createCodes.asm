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
	push DWORD 28			; EBP-20 = reg_count
;		char full = 0;
	xor ebx, ebx	; ebx=0
	push DWORD 0			; EBP-24 = full
;		int code = 0;
				; EBX = code

;		while(tab[s].parent != ROOT){
create_while:
	mov ax, WORD[edx+4]
	cmp eax, ROOT
	je create_shift
;			code |= tab[s].flag << full;
	mov al, BYTE[edx+6] ;flag
	mov cl, BYTE[ebp-24] ;full
	shl eax, cl
	or ebx, eax
;			++full;
	inc cl
	mov BYTE[ebp-24], cl
;			if(full == 32){
	cmp cl, 32
	jne create_parent
;				(codes[sign])[reg_count] = code;
	mov eax, DWORD[ebp-16]	;codes[sign]
	mov cl, BYTE[ebp-20]	;reg_count
	add eax, ecx		;&codes[sign][reg_count]
	
	mov DWORD[eax], ebx
;				reg_count -= 4;
	sub cl, 4
	mov BYTE[ebp-20], cl
;				code = 0;
	xor ebx, ebx
;				full = 0;
	mov BYTE[ebp-24], bl 
;			}//if
;			s = s.parent;
create_parent:
	mov edx, DWORD[ebp-12]	;s
	mov ax, WORD[edx+4]	;parent
	mov ecx, DWORD[ebp+12]   ;tab
	shl eax, 3
	add ecx, eax	;tab+8*parent_sign
	mov DWORD[ebp-12], ecx	;s=s.parent
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
	mov cl, 28	     	;28	
	sub cl, dl	     	;28-reg_count
	shl cl, 3		;8*(28-reg_count)
	mov al, BYTE[ebp-24]	;full
	add al, cl		;al <- result
	
	mov ecx, DWORD[ebp-8]	;sign
	mov BYTE[ecx+7], al	;sign.bitcountincode = result
;		//shift
;		char reg_count_s = 0;
	xor ecx, ecx		; reg_count_s = 0
	push DWORD 0		; EBP-28 = reg_count_s
			; EDX = i = reg_count
shift_while:
;		for(char i = reg_count; i != 28; reg_count_s += 4){
	cmp edx, 28
	je shift_epilog
	
	mov ebx, DWORD[ebp-16]	;codes[sign]
;			code[i] <<= 32-full;
	add ebx, edx
	mov eax, ebx		;codes[sign][i]
	mov bl, BYTE[ebp-24]	;full
	mov cl, 32
	sub cl, bl		;32-full
	shl eax, cl		;code[i] 
;			code[i] |= (code[i+=4] >> full);
	add dl, 4		;i+=4
	mov cl, bl		;cl=full
	mov ebx, DWORD[ebp-16]	;codes[sign]
	lea ebx, [edx*1+ebx]	;codes[sign][i+=4]
	shr ebx, cl		;code[i+=4] >> full
	or  eax, ebx		;code
;			codes[sign][reg_count_s] = code;
	mov ebx, DWORD[ebp-16]	;codes[sign]
	mov cl,  BYTE[ebp-28]	;reg_count_s
	add ebx, ecx
	mov DWORD[ebx], eax
;	from for: reg_count_s+=4
	add cl, 4
	mov BYTE[ebp-28], cl
;		}
	jmp shift_while
shift_epilog:
;			code[i] <<= 32-full;
	add ebx, edx
	mov eax, DWORD[ebx]	;codes[sign][i]
	mov bl, BYTE[ebp-24]	;full
	mov cl, 32
	sub cl, bl		;32-full
	shl eax, cl		;code[i] 
;			codes[sign][reg_count_s] = code;
	mov ecx, DWORD[ebp-16]	;codes[sign]
	mov bl,  BYTE[ebp-28]	;reg_count_s
	add ecx, ebx
	mov DWORD[ecx], eax
;	}
	pop eax	;28reg_count_s
	pop eax	;24full
	pop eax	;20reg_count
	pop eax ;16codes[sign]
	pop eax	;12s
	jmp create_loop
epilog:
				; EBP-4 = loop_finish
				; EBP-8 = sign
	pop eax		;8loop_finish
	pop eax		;4sign
	
	jmp test ;later call
	
	;pop ebp
	;ret
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
