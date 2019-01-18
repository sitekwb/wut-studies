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
;		file << output;	
;	}
; }
; file << busyOutput //rubbish bits num

ROOT equ 0xFFFF 
EOF equ -1

extern fgetc
extern fputc

section	.text
global write
extern testWrite

write:
; get sign
    	push DWORD[ebp+8]            ; ebp-4 = *file
   	call fgetc                  ; eax = sign
	pop ebx
; if(EOF) break;
    	cmp eax, EOF 
	je epilog

;							 EBP+8  = FILE *inputFile
;							 EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; 							 EBP+16 = FILE *outputFile
;							 EBP+20 = char *codes
;	int emptyThis = 32/64 - bitcount%BITS_PER_REG;
	mov ebx, [ebp+12];tab[sign]
	lea bl, BYTE[ebx+8*eax+7];bitcount
	
		
;	int lastFullReg = busyCode/BITS_PER_REG;
	xor edx, edx		; EDX = output_reg 
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
;		file << output;	
;	}
; }
; tab[sign].count++
    	lea ecx, [ebx+8*eax]        ; ecx = tab[sign].count
    	mov edx, [ecx]
    	inc edx
    	mov [ecx], edx
; tab[sign].parent = ROOT
	mov WORD [ecx + 4], ROOT

	jmp loop
epilog:
	pop eax
	call test
	jmp huffman
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
