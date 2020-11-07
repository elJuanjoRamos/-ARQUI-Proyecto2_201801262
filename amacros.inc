
print macro cadena ; print-> id del macro; macro > reservada, cadena
MOV ah,09h
MOV dx,@data
MOV ds,dx
MOV dx, offset cadena
int 21h
endm        


getChar MACRO 
mov ah,01h
int 21h
endm


printChar macro char 
mov ah,02h
mov dl,char
int 21h
endm




getRuta macro buffer
LOCAL INICIO,FIN
	xor si,si
INICIO:
	getChar
	cmp al,0dh
	je FIN
	mov buffer[si],al
	inc si
	jmp INICIO
FIN:
	mov buffer[si],00h
endm


getUser macro buffer
LOCAL INICIO,FIN, FIN2, EXIT
	MOV SI, 0
INICIO:
	CMP SI, 8
	JE FIN2
	getChar
	cmp al,0dh
	je FIN
	mov buffer[si],al
	inc si
	jmp INICIO
FIN:
	mov buffer[si],'$'
	JMP EXIT
FIN2:
	print salto
    print msmError5
    getChar
    print salto
JMP REGISTRAR
EXIT:

endm




getPassword macro buffer
LOCAL INICIO,FIN, FIN2,INSERT, EXIT
	MOV SI, 0
INICIO:
	CMP SI, 5
	JE FIN2
	getChar
	cmp al,0dh
	je FIN
	CMP AL, '0'
	JE INSERT
	CMP AL, '1'
	JE INSERT
	CMP AL, '2'
	JE INSERT
	CMP AL, '3'
	JE INSERT
	CMP AL, '4'
	JE INSERT
	CMP AL, '5'
	JE INSERT
	CMP AL, '6'
	JE INSERT
	CMP AL, '7'
	JE INSERT
	CMP AL, '8'
	JE INSERT
	CMP AL, '9'
	JE INSERT
	print salto
    print msmError7
    getChar
    print salto
	JMP REGISTRAR
INSERT:
	mov buffer[si],al
	inc si
	jmp INICIO

FIN:
	mov buffer[si],'$'
	JMP EXIT
FIN2:
	print salto
    print msmError6
    getChar
    print salto
	JMP REGISTRAR
EXIT: 
endm








;OBTENER FECHA
getfecha macro
    MOV AH,2AH
    INT 21H
endm

;OBTENER HORA
gethora macro
    MOV AH,2CH
    INT 21H
endm

;OBTENER FECHA
obtenerFechaHora macro dia, mes, ano, hora, minuto, segundo
    XOR AX,AX
    XOR BX,BX
    XOR CX,CX
    getfecha
    MOV BX,CX
    convertirString1 BX,ano
    XOR BX,BX
    getfecha
    MOV BL,DH
    convertirString1 BX,mes
    getfecha
    MOV BL,DL
    convertirString1 BX,dia
    XOR BX,BX
    gethora
    MOV BL,CH
    convertirString1 BX,hora
    gethora
    MOV BL,CL
    convertirString1 BX,minuto 
    gethora
    MOV BL,DH
    convertirString1 BX,segundo 
endm







ConvertirString macro buffer
	LOCAL Dividir,Dividir2,FinCr3,NEGATIVO,FIN2,FIN
	xor si,si
	xor cx,cx
	xor bx,bx
	xor dx,dx
	mov dl,0ah
	test ax,1000000000000000
	jnz NEGATIVO
	jmp Dividir2

	NEGATIVO:
		neg ax
		mov buffer[si],45
		inc si
		jmp Dividir2

	Dividir:
		xor ah,ah
	Dividir2:
		div dl
		inc cx
		push ax
		cmp al,00h
		je FinCr3
		jmp Dividir
	FinCr3:
		pop ax
		add ah,30h
		mov buffer[si],ah
		inc si
		loop FinCr3
		mov ah,24h
		mov buffer[si],ah
		inc si
	FIN:
endm


CovertirAscii macro numero
	LOCAL INICIO,FIN
	xor al,al
	xor bl,bl
	xor cl,cl
	mov bl,10	;multiplicador 10
	xor si,si
	INICIO:
		mov cl,numero[si] 
		cmp cl,48
		jl FIN
		cmp cl,57
		jg FIN
		inc si
		sub cl,48	;restar 48 para que me de el numero
		mul bl		;multplicar ax por 10
		add al,cl	;sumar lo que tengo mas el siguiente
		jmp INICIO
	FIN:
endm





;CONVERTIR STRING
convertirString1 macro reg, buffer
    LOCAL Dividir, Dividir2, FINC3, Final
    XOR SI,SI       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    XOR CX,CX       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    XOR AX,AX       ; COLOCA A CERO LOS REGISTROS DEL SEGMENTO
    MOV AX,reg
    MOV dl,0ah
    JMP Dividir2

    Dividir:
        XOR AH,AH

    Dividir2:
        DIV DL
        INC CX
        PUSH AX
        CMP AL,00H
        JE FINC3
        JMP Dividir
    FINC3:
        POP AX
        ADD AH,30H
        MOV buffer[SI], AH
        INC SI
        LOOP FINC3
        INC SI
    Final:
endm




clear macro buffer
LOCAL INICIO, SALIR
    PUSH DI 
    xor DI,DI
INICIO:
    CMP DI,20
    JE SALIR
    CMP buffer[DI], '$'
    JE SALIR
    
    MOV buffer[DI], '$'
    INC DI
    JMP INICIO
SALIR:
    XOR DI, DI
    POP DI
endm







Sound macro hz
	mov al, 86h
	out 43h, al
	mov ax, (1193180 / hz) ;numero de hz
	out 42h, al
	mov al, ah
	out 42h, al 
	in al, 61h
	or al, 00000011b
	out 61h, al
	delay 1000 ;mando a ejecutar el delay para que se escuche el sonido por varios segundos
	 ; apagar la bocina
	in al, 61h
	and al, 11111100b
	out 61h, al
endm


Delay macro const
LOCAL D1, D2, FIN
PUSH SI
PUSH DI
MOV SI, const
D1:
	DEC SI
	JZ FIN
	MOV DI, const
D2:
	DEC DI
	JNZ D2
	JMP D1
FIN:
	POP DI
	POP SI
endm
