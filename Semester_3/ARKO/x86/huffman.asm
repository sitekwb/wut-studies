; try to change it => it goes through all values and search min and independently save new_root

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
extern createCodes

;do{
huffman:
    	mov ecx, DWORD[ebp+12]        	; ecx = &sign
	add ecx, 8*256			; edx = finishSign
	push DWORD MAX			; EBP-4 = MIN
	push DWORD MAX			; EBP-8 = MINEST
	push DWORD MAX			; EBP-12 = minIndex
	push DWORD MAX 			; EBP-16 = minestIndex
	push DWORD ecx			; EBP-20 = new_ind
	add ecx, 8*256	
	push DWORD ecx			; EBP-24 = finish_sign
huffman_loop:
;	int min = MAX, minest = MAX, minIndex = MAX, minestIndex = MAX;
    	mov ecx, DWORD[ebp+12]        	;sign
	mov edx, DWORD[ebp-24]		;finish_sign 
	mov DWORD[ebp-4],  MAX
	mov DWORD[ebp-8],  MAX
	mov DWORD[ebp-12], MAX
	mov DWORD[ebp-16], MAX

;	for(char sign: tab1){
	sub ecx, 8
lop:
	add ecx, 8
	cmp ecx, edx
	je finish 
;		if( tab[sign].parent == ROOT ){
	mov ax, WORD[ecx+4]
	cmp ax, ROOT
check_if_root:
	jne lop
is_root:	;TODO delete
;			if( tab[sign].count < min ){
	mov eax, DWORD[ecx]						; eax = tab[sign].count
	mov ebx, DWORD[ebp-4];min
	cmp eax, ebx
	jae lop
is_smaller:	;TODO delete
;				if( tab[sign].count < minest ){
	mov ebx, DWORD[ebp-8];minest
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
	mov ecx, DWORD[ebp-20]	; ecx = tab[ind]
	mov ebx, ecx
	add ebx, 8 
	mov DWORD[ebp-20], ebx
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
	mov eax, DWORD[ebp-16]	
	mov WORD[eax+4], cx 
;	tab[minest].flag = 0;
	mov BYTE[eax+6], 0
;	tab[min].parent = ind;
	mov eax, DWORD[ebp-12]
	mov WORD[eax+4], cx 
;	tab[min].flag = 1;
	mov BYTE[eax+6], 1
;}while(true)
	jmp huffman_loop
epilog:
	pop	eax	; ebp-24
	pop	eax	; ebp-20
    	pop 	eax	; ebp-16
	pop	eax	; ebp-12
	pop	eax	; ebp-8
	pop	eax	; ebp-4
	
	call test
	
	jmp createCodes

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
