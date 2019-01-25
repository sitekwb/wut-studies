; EBP+8  = FILE *inputFile
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]

; for(char sign: input){
;   tab[sign].count++;
;   tab[sign].parent = ROOT; (2)
; }

ROOT equ 2
EOF equ -1

extern fgetc

section	.text
global  count

count:
	push	ebp
	mov	    ebp,    esp
    push DWORD ebp+8            ; ebp-4 = *file

    mov ebx, [ebp+12]           ; ebx = tab
loop:

; get sign
    call fgetc                  ; eax = sign

; if(EOF) break;
    test eax, EOF
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
    pop eax                     ; pop *file
	pop	ebp
	ret

