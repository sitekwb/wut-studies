; EBP+8  = FILE *inputFile #NOTUSED
; EBP+12 = char *tab [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
; EBP+16 = FILE *outputFile #NOTUSED
; EBP+20 = char *codes #NOTUSED

;do{
;	//searchMin
;	int min = MAX, minest = MAX, minIndex = MAX, minestIndex = MAX;
;	for(char sign: tab1){
;		if( tab[sign].parent == ROOT ){
;			if( tab[sign].count < min ){
;				if( tab[sign].count < minest ){
;					min = minest;
;					minInd = minestInd;
;					minest = tab[sign].count;
;					minestInd = sign;
;				}
;				else{
;					min = tab[sign].count;
;					minInd = sign;
;				}
;			}
;		}
;	}
;	short sign;
;	for(sign: tab2){
;		if( ... == ROOT){ ... }
;		else if( tab[sign].count == 0 ){
;			break;
;		}
;	}
;	if(minIndex == MAX){
;		break;//huffman ready
;	}
;	//createRoot
;	short ind = sign;
;	tab[ind].count = min + minest;
;	tab[ind].parent = ROOT;
;	
;	tab[min].flag = 0;
;	tab[minest].flag = 1;
;
;	tab[min].parent = ind;
;	tab[minest].parent = ind;
;}while(true)
	


ROOT equ 0xFFFF     ; 2B
MAX  equ 0xFFFFFFFF ; 4B 

section	.text
global huffman 
extern test

;do{
huffman:

;	int min = MAX, minest = MAX, minIndex = MAX, minestIndex = MAX;
    	mov ecx, DWORD[ebp+12]        	; ecx = &sign
	mov edx, ecx
	add edx, 8*256			; edx = finishSign
	push DWORD MAX			; EBP-4 = MIN
	push DWORD MAX			; EBP-8 = MINEST
	push DWORD MAX			; EBP-12 = minIndex
	push DWORD MAX 			; EBP-16 = minestIndex

;	for(char sign: tab1){
	sub ecx, 8
lop:
	add ecx, 8
	cmp ecx, edx
	je loop2_init
;		if( tab[sign].parent == ROOT ){
	mov ax, WORD[ecx+4]
	cmp ax, ROOT
check_if_root:
	jne lop
is_root:	;TODO delete
;			if( tab[sign].count < min ){
	mov eax, DWORD[ecx]						; eax = tab[sign].count
	mov ebx, DWORD[ebp-4]
	cmp eax, ebx
	jae lop
is_smaller:	;TODO delete
;				if( tab[sign].count < minest ){
	mov ebx, DWORD[ebp-8]
	cmp eax, ebx
	jae change_min
is_smallest:	;TODO delete
;					min = minest;
	mov ebx, DWORD[ebp-8]
	mov DWORD[ebp-4], ebx
;					minInd = minestInd;
	mov ebx, DWORD[ebp-16]
	mov DWORD[ebp-12], ebx
;					minest = tab[sign].count;
	mov DWORD[ebp-8], eax
;					minestInd = sign;
	mov DWORD[ebp-16], ecx
;				}
	jmp lop
;				else{
change_min:
;					min = tab[sign].count;
	mov DWORD[ebp-4], eax
;					minInd = sign;
	mov DWORD[ebp-12], ecx
;				}
	jmp lop
;			}
;		}
;	}
loop2_init:
;	short sign;
	add edx, 256*8
	sub ecx, 8
;	for(sign: tab2){
;COPIED		if( ... == ROOT){ ... }
loop2:
	add ecx, 8
	cmp ecx, edx
	je finish
;		if( tab[sign].count == 0 ){
	mov ebx, DWORD[ecx]						; ebx = tab[sign].count
	test ebx, ebx
;			break;
;		}
	jz finish
;		else if( tab[sign].parent == ROOT){
	mov ax, WORD[ecx+4]
	cmp ax, ROOT
	jne loop2

;			if( tab[sign].count < min ){
	mov eax, ebx							; eax = tab[sign].count
	mov ebx, DWORD[ebp-4]
	cmp eax, ebx
	jge loop2
;				if( tab[sign].count < minest ){
	mov ebx, DWORD[ebp-8]
	cmp eax, ebx
	jge change_min2
;					min = minest;
	mov ebx, DWORD[ebp-8]
	mov DWORD[ebp-4], ebx
;					minInd = minestInd;
	mov ebx, DWORD[ebp-16]
	mov DWORD[ebp-12], ebx
;					minest = tab[sign].count;
	mov DWORD[ebp-8], eax
;					minestInd = sign;
	mov DWORD[ebp-16], ecx
;				}
	jmp loop2
;				else{
change_min2:
;					min = tab[sign].count;
	mov DWORD[ebp-4], eax
;					minInd = sign;
	mov DWORD[ebp-12], ecx
;				}
	jmp loop2
;			}
;		}
finish:
;	if(min == MAX){
;		break;//huffman ready
;	}
	mov eax, DWORD[ebp-4]
	cmp eax, MAX
	je epilog
				; TO REMEMBER
				; EBP-4 = MIN
				; EBP-8 = MINEST
				; EBP-12 = minIndex
				; EBP-16 = minestIndex
;	short ind = sign;
						; ecx = tab[ind]
;	tab[ind].count = min + minest;
	;mov eax, DWORD[ebp-4]
	mov ebx, DWORD[ebp-8]
	add eax, ebx
	mov DWORD[ecx], eax

;	tab[ind].parent = ROOT;
	mov WORD[ecx+4], ROOT

;	tab[minest].parent = ind;
	mov ebx, DWORD[ebp+12]		; ebx = tab
	sub ecx, ebx
	shr ecx, 3
	pop eax
	mov WORD[eax+4], cx 
;	tab[minest].flag = 0;
	mov BYTE[eax+6], 0
;	tab[min].parent = ind;
	pop eax
	mov WORD[eax+4], cx 
;	tab[min].flag = 1;
	mov BYTE[eax+6], 1
;}while(true)
	pop eax
	pop eax
	jmp huffman
epilog:
    	pop 	eax	; ebp-16
	pop	eax	; ebp-12
	pop	eax	; ebp-8
	pop	eax	; ebp-4
	
	call test

	mov esp, ebp	
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
