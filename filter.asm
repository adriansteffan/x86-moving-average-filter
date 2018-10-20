BITS 32

GLOBAL filter
extern printf

section .data
errortext: db `\nError: Alpha + Beta equals 0`,0
float_zero: dd 0.0

; Note: As this was my first bigger assembler project, I made quite heavy use of comments to stay on top of what was happening

; Iterates over an given Signal and filters it by applying the following formular onto each value:
; gk = ((gk-1*alpha)+(fk*beta))/(alpha+beta) with g0 = s
; (gk = filtered value at position k) 
; (fk = unfiltered value at position k) 
;
; Argumente : alpha [+8]
;		      beta [+12]
;		      s [+16]
;		      Source Address Signal [+20]
;		      Length Signal [+24]
;		      Destination Adress filtered Signal [+28]

filter:
	push ebp
	mov  ebp, esp
	
	; Save registers and load arguments
	
	; ESI for the source address
	push esi
	mov esi,[ebp+20]
	
	; EDI for the destination address
	push edi
	mov edi,[ebp+28]
	
	; EBX as a counter variable
	push ebx
	mov ebx,[ebp+24]
	
	
	;length == 0?
	cmp ebx,0
	jle endfunc
	
	fninit
	
	;Load values from arguments
	fld dword [ebp+8] ; alpha onto the stack
	fld dword [ebp+12] ; beta onto the stack
	fadd st0,st1 ; alpha+beta into st0
	
	;Alpha+Beta == 0? Jump to error handling
	fcom dword [float_zero]
	fstsw ax
	sahf
	jz errorhandling
	
	
	fild dword [ebp+16]; starting value (s) onto the stack
	fmul st0,st2 ;(s * alpha) into st0
	fld dword [ebp+12] ;beta onto the stack
	fild dword [esi] ;fk onto the stack
	fmul st0,st1  ;(fk * beta) into st0
	fadd st0,st2  ;(gk-1 * alpha) + (fk * beta) into st0
	fdiv st0, st3 ;[(gk-1 * alpha) + (fk * beta)]/(alpha+beta) into st0
	fist dword [edi] ;Save the result
	
	; Increment destination and source address
	add edi,4
	add esi,4
	
	inc ebx
	start_main_loop:
	
	dec ebx
	
	jz end_main_loop

	
	fmul st0,st4 ;(gk-1)*Alpha into st0
	fincstp ; Counterclockwise rotation of the FPU stack by 2
	fincstp
	fstp st0 ; discard the uppermost value
	fild dword [esi] ; fk onto the stack
	fmul st0, st7 ; fk*beta into st0
	fadd st0, st6 ; fk*beta+((gk-1)*alpha) into st0
	fdiv st0, st1 ;[(gk-1 * alpha) + (fk * beta)]/(alpha+beta) into st0
	fist dword [edi] ; Save the result
	
	
	; Increment destination and source address
	add esi,4
	add edi,4
	dec ebx
	jz end_main_loop
	
	
	fmul st0,st2 ;(gk-1)*a into st0
	fdecstp ; Clockwise rotation of the FPU stack by 2
	fdecstp
	fstp st0 ; discard the uppermost value
	fild dword [esi] ; fk onto the stack
	fmul st0, st1 ; fk*Beta into st0
	fadd st0, st2 ; fk*Beta+((gk-1)*Alpha) into st0
	fdiv st0, st3 ;[(gk-1 * alpha) + (fk * beta)]/(alpha+beta) into st0
	fist dword [edi] ; Save the result
	
	; Increment destination and source address
	add esi,4
	add edi,4
	
	jmp start_main_loop
	end_main_loop:
	
	jmp endfunc
	
	errorhandling:
	
	; output an error message 
	push errortext
	call printf
	add esp,4
	
	; fill destination address with zeros
	errorloop:
	mov dword [edi],0
	add edi,4
	dec ebx
	jnz errorloop
	endfunc:
	
	fninit
	
	; restore saved registers
	pop edi
	pop esi
	pop ebx
	
	mov esp, ebp
	pop ebp
	
ret
