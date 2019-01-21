; EBP+8  = FILE *inputFile
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile
; EBP+20 = char *codes

; for(char sign: input){
;   tab[sign].count++;
;   tab[sign].parent = ROOT; (2)
; }

ROOT equ 0xFFFF 
EOF equ -1

extern fgetc

section	.text
global encode 
extern test
extern huffman

encode:
count:
	push	ebp
	mov	    ebp,    esp
    	push DWORD[ebp+8]            ; ebp-4 = *file

    	mov ebx, [ebp+12]           ; ebx = tab
loop:

; get sign
   	call fgetc                  ; eax = sign

; if(EOF) break;
    	cmp eax, -1 
	je epilog 

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
