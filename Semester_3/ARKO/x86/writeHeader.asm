; EBP+8  = FILE *inputFile
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile
; EBP+20 = char *codes

; for(char code: codes){
; 	if(tab[sign].bitcountincode != 0){
;		outputFile << sign << bitcountincode << code;
;	}
; }
; outputFile << (short)0;

extern fputc
extern fwrite

section	.text
global writeHeader
extern testHeader
extern write 

writeHeader:
	push DWORD[ebp+12]	; EBP-4  = tab[sign]
	push DWORD 0		; EBP-8  = sign
    	push DWORD[ebp+20]	; EBP-12 = codes
	push DWORD[ebp+16]	; EBP-16 = outputFile
; for(char code: codes){
lop:
	mov eax, [ebp-8];sign
	cmp eax, 256	;sign==256
	je epilog 
	
; 	if(tab[sign].bitcountincode != 0){
	mov ebx, [ebp-4];tab[sign]
	xor ecx, ecx	;prepare ecx
	mov  cl, [ebx+7];bitcountincode
	test cl, cl
	jz loop_next
;		outputFile << sign << bitcountincode << code;
;sign
	push eax	;sign = EBP-20
	call fputc
;bitcountincode	
	mov [ebp-20], ecx
	call fputc
;code
	shr ecx, 3	;bytecountincode
	inc ecx
	mov [ebp-20], ecx
	push DWORD 1	;size
	push DWORD[ebp-12];code
	call fwrite

	pop ebx;code
	pop ebx;size
	pop ebx;sign
loop_next:
	inc eax		;sign++
	mov [ebp-8], eax;save sign

	mov ebx, [ebp-4];tab[sign]
	add ebx, 8
	mov [ebp-4], ebx

	mov ebx, [ebp-12];codes
	add ebx, 32
	mov [ebp-12], ebx
	
	jmp lop
	
epilog:

; outputFile << (short)0;
	push DWORD 0
	call fputc
	call fputc

	pop eax
	pop eax
	pop eax
	pop eax
	
	call testHeader

	jmp write 
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
