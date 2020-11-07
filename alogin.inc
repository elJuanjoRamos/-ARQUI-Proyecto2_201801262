


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
    IGUAL:
        COMPARARPASS pass        
    DIFERENTE:
        COMPARARUSERENLISTA user, pass        
ENDM



COMPARARUSERENLISTA MACRO user, pass
LOCAL INICIO, FIN, ERROR, GETUSER, VERIFICARUSER, IGUAL, IGUAL2, DIFERENTE, COMPARARPASS, GETPASS
    MOV DI, 0
    MOV SI, 0
   ;HOLA
   ;LOLA
    clear usuariotemp
INICIO: 
    
    MOV AL, listausuarios[SI]
    CMP AL, '$'
    JE ERROR
    CMP AL, ';'
    JE GETUSER
    INC SI
    JMP INICIO

GETUSER:
    INC SI
    MOV AL, listausuarios[SI]
    CMP AL, ':'    
    JE VERIFICARUSER
    MOV usuariotemp[DI], AL
    INC DI
    JMP GETUSER



VERIFICARUSER:
    INC  SI
    PUSH SI
   
    xor CX, CX
    mov cx,7   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, user                ; Reset pointer to arr1
    lea di, usuariotemp

    repe cmpsb  ;compara las dos cadenas
    je IGUAL ;Si fueron iguales
    jne DIFERENTE
    IGUAL:
        clear usuariotemp
        MOV DI, 0
        POP SI 
        JMP GETPASS        
    DIFERENTE:
        MOV DI, 0
        POP SI 
        clear usuariotemp
        JMP INICIO

GETPASS:
    MOV AL, listausuarios[SI]
    CMP AL, ';'
    JE COMPARARPASS
    MOV usuariotemp[DI], AL
    INC SI
    INC DI
    JMP GETPASS


COMPARARPASS:
     
    xor CX, CX
    mov cx,4   ;Determinamos la cantidad de datos a leer/comparar
    mov AX,DS  ;mueve el segmento datos a AX
    mov ES,AX  ;Mueve los datos al segmento extra
    lea si, pass                ; Reset pointer to arr1
    lea di, usuariotemp

    repe cmpsb  ;compara las dos cadenas
    je IGUAL2 ;Si fueron iguales
    jne ERROR
    IGUAL2:
        print salto
        print usuarionoexiste
        print salto
        getChar
        JMP NUEVO_JUEGO

ERROR:
    print errorlogin
    JMP INGRESAR

FIN:
    

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
LOCAL INICIO, INSERTUSERNAME, INSERTDOSPUNTOS, INSERTPASSWORD, TERMINAR
MOV listausuarios[0], ';'	
MOV DI, 0
MOV SI, 0
INICIO:
    CMP listausuarios[SI], '$'
	JE INSERTUSERNAME
	INC SI
	JMP INICIO
INSERTUSERNAME:
    CMP user[DI], '$'
    JE INSERTDOSPUNTOS
    MOV AL, user[DI]
    MOV listausuarios[SI], AL
    INC SI
    INC DI
    JMP INSERTUSERNAME

INSERTDOSPUNTOS:
    MOV AL, ':'
    MOV listausuarios[SI], AL
    INC SI
    MOV DI, 0
    JMP INSERTPASSWORD
INSERTPASSWORD:
    MOV AL, password[DI]
    CMP AL, '$'    
    JE TERMINAR
    MOV listausuarios[SI], AL
    INC SI
    INC DI
    JMP INSERTPASSWORD

TERMINAR:
    MOV listausuarios[SI], ';'
    print salto
    print listausuarios
    print salto
    JMP MENUPRINCIPAL
ENDM