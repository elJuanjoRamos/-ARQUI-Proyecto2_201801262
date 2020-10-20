


COMPARARUSER MACRO user, pass
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,7   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, user                ; Reset pointer to arr1
    lea di, admin

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE
        print errorlogin
        jmp ENDGAME
    IGUAL:
        COMPARARPASS pass        
    DIFERENTE:

ENDM


COMPARARPASS MACRO password
LOCAL IGUAL, DIFERENTE
   
    xor CX, CX
    mov cx,4   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, password                ; Reset pointer to arr1
    lea di, pass

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE
        print errorlogin
        jmp ENDGAME
    
    IGUAL:
        JMP USERLOGUEADO
    DIFERENTE:
ENDM




;=================registo



COMPARARREGISTRO MACRO buffer
LOCAL INICIO, ENDF, REGRESAR, SIEXISTE, TERMINAR
    push CX
	push AX
	push SI
	push DI
	xor DI, DI
	xor SI, SI
	mov SI, 0
    MOV DI, 0
INICIO:
    MOV AL, buffer[DI]
    CMP listausuarios[SI], AL
    JNE REGRESAR
    INC SI
    INC DI
    CMP listausuarios[SI], '$'
    JE ENDF
    
    CMP listausuarios[SI], ':'
    JE SIEXISTE
    
    JMP INICIO


SIEXISTE:
    print usuarioexiste
    JMP TERMINAR

REGRESAR:
    xor di, di
    MOV DI, 0
    INC SI
    JMP INICIO

ENDF:
    print usuarionoexiste
    POP DI
    POP SI
    POP AX
    POP CX
    JMP REGISTRAR2
TERMINAR:
    POP DI
    POP SI
    POP AX
    POP CX
    clear usuario
ENDM




INSERTARUSER MACRO user, password
LOCAL INICIO, INSERTUSERNAME, INSERTPASSWORD1, INSERTPASSWORD, TERMINAR
print user
print salto
print password
print salto
    push CX
	push AX
	push SI
	push DI
	mov SI, 0
    MOV DI, 0
INICIO:
	CMP listausuarios[SI], '$'
	JE INSERTUSERNAME
	INC SI
	JMP INICIO

INSERTUSERNAME:
	MOV AL, user[DI]
    CMP AL, '$'
	JE INSERTPASSWORD1
	MOV listausuarios[SI], AL
	INC SI
	INC DI
	JMP INSERTUSERNAME

INSERTPASSWORD1:
    MOV listausuarios[SI], ':'
    INC SI
    MOV DI, 0
INSERTPASSWORD:
	CMP password[DI], '$'
	JE TERMINAR
	MOV AL, password[DI]
	MOV listausuarios[SI], AL
	INC SI
	INC DI
	JMP INSERTPASSWORD

TERMINAR:
MOV listausuarios[SI], ','
;POP DI
;POP SI
;POP AX
;POP CX
print listausuarios
print salto
ENDM