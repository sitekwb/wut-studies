; EBP+8  = FILE *inputFile
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile
; EBP+20 = char *codes

; int it = tab[sign]
; int busyOutput=0, busyCode, code, output;
; for(char sign: input){
;	busyCode = it.bitcount;
;	int emptyThis = busyCode%BITS_PER_REG;
;	int lastFullReg = busyCode/BITS_PER_REG;
;	for(int i=0; i != lastFullReg; ++i){
;		code_reg = codes[i*(4or8)];
;		output = output | (code_reg >> busyOutput);
;		file << output_reg;
;		output = code_reg << (32/64 - busyOutput);
;		busyOutput = 32/64 - busyOutput;
;	}
;	if(busyOutput <= emptyThis){
;		code_reg = codes[(4/8)*(lastFullReg+1)];
;		output = output | (code_reg >> busyOutput);
;		file << output_reg;
;	}
;	else{
;		code_reg = codes[(4/8)*(lastFullReg+1)];
;		output = output | (code_reg >> busyOutput);
;		file << output;
;		output = code_reg << (32/64 - busyOutput);
;		busyOutput = 32/64 - busyOutput;
;	}
; }
; file << busyOutput //rubbish bits num

ROOT equ 0xFFFF 
EOF equ -1

extern fgetc
extern fputc

section	.text
global write

write:
	push DWORD 0		; EBP-4 = busyOutput
	push DWORD 0		; EBP-8  = lastFullReg
	push DWORD 0		; EBP-12 = emptyThis
	push DWORD 0		; EBP-16 = i
	push DWORD 0		; EBP-20 = sign
	push DWORD[ebp+16]	; EBP-24 = outputFile
	push DWORD 0		; EBP-28 = char to put

write_loop:
; get sign
	push DWORD[ebp+8]           ; inputFile
	call fgetc                  ; eax = sign
	pop ebx
; if(EOF) break;
	cmp eax, EOF 
	je epilog

;							 EBP+8  = FILE *inputFile
;							 EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
;							 EBP+16 = FILE *outputFile
;							 EBP+20 = char *codes
;	int emptyThis = 32/64 - bitcount%BITS_PER_REG;
	mov ebx, [ebp+12];tab[sign]
	mov ecx, eax	 ;sign
	shl eax, 3	 ;8*sign
	add eax, 7	 ;8*sign+7
	add ebx, eax	 ;tab[sign]+8*sign+7
	xor eax, eax	 ;clear eax
	mov al, [ebx];bitcount
	mov ebx, 32	;BITS_PER_REG
	div bl		;bitcount/BITS_PER_REG: al:/, ah:%
	sub bl, ah	;emptyThis                               
;	int lastFullReg = bitcount/BITS_PER_REG;
	;al = lastFullReg
				; EDX    = output_reg 
	mov [ebp-8], eax	; EBP-8  = lastFullReg
	mov [ebp-12], ebx	; EBP-12 = emptyThis
	mov [ebp-16], DWORD 0		; EBP-16 = i
	mov [ebp-20], ecx	; EBP-20 = sign
;	for(int i=0; i != lastFullReg; ++i){
copy:
	mov eax, [ebp-16];i
	mov ebx, [ebp-8] ;lastFullReg
	cmp ebx, eax
	je copy_end
;		code_reg = codes[i*(4or8)];
	mov ebx, [ebp+20];codes
	shl eax, 2;4*i
	add ebx, eax		;codes+4*i
	mov ecx, [ebp-20]	;sign
	shl ecx, 5	;32*sign
	lea ebx, [ecx+ebx]	;code_reg
	mov eax, ebx		;code_reg
;		output = output | (code_reg >> busyOutput);
	mov ecx, [ebp-4]	;busyOutput
	shr ebx, cl;code_reg>>busyOutput
	or edx, ebx
;		file << output_reg;
	mov ebx, edx
	shr ebx, 24
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov ebx, edx
	shr ebx, 16
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov ebx, edx
	shr ebx, 8
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov [ebp-28], edx
	call fputc
;		output = code_reg << (32/64 - busyOutput);
	mov edx, 32
	sub dl, cl
	mov cl, dl	;32-busyOutput
	shl eax, cl	;code_reg<<(32-busyOutput)
;		busyOutput = 32/64 - busyOutput;
	mov [ebp-4], ecx;busyOutput
	mov edx, eax;output
;	++i	
	mov eax, [ebp-16]
	inc eax
	mov [ebp-16], eax

	jmp copy
;	}
copy_end:
;		code_reg = codes[(4/8)*(lastFullReg)];
	mov eax, [ebp-8]	;lastFullReg
	shl eax, 2		;4*lastFullReg
	
	mov ebx, [ebp-20]	;sign
	shl ebx, 5		;sign*32

	mov ecx, [ebp+20];codes
	add eax, ebx;32*sign+4*lastFullReg
	mov eax, [1*eax+ecx];codes[sign][lastFullReg*4]
	mov [ebp-16], eax		; EBP-16 = code_reg
;		output = output | (code_reg >> busyOutput);
	mov ecx, [ebp-4]	;busyOutput
	shr eax, cl;code>>busyOutput
	or edx, eax
;		file << output_reg;
	mov ebx, edx
	shr ebx, 24
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov ebx, edx
	shr ebx, 16
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov ebx, edx
	shr ebx, 8
	mov [ebp-28], ebx
	call fputc
	
	shr edx, 8
	mov [ebp-28], edx
	call fputc	
;	if(busyOutput <= emptyThis){
	mov eax, [ebp-4]	;busyOutput
	mov ebx, [ebp-12]	;emptyThis
	cmp eax, ebx
	jbe write_loop
shift:
;		output = code_reg << (32/64 - busyOutput);
	mov eax, [ebp-4]	;busyOutput
	mov ecx, 32
	sub cl, al;32-busyOutput
	mov edx, [ebp-16]	;code_reg
	shl edx, cl
;		busyOutput = 32/64 - busyOutput;
	mov [ebp-4], ecx	;busyOutput
;	}
; }
	jmp write_loop
epilog:
; file << busyOutput //rubbish bits num
	pop eax 	;ebp-28
	pop eax 	;ebp-24
	pop eax 	;ebp-20
	pop eax 	;ebp-16
	pop eax 	;ebp-12
	pop eax 	;ebp-8
	pop eax 	;ebp-48
	
	mov esp, ebp
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
