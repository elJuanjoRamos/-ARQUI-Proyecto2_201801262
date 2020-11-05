ordenar macro buffer
LOCAL INICIO, GETPUNTO,GETPUNTO1, FIN, ENDF

print buffer

PUSH DI
PUSH AX
PUSH SI
MOV DI, 0
MOV SI, 0
MOV Bl, 0
INICIO:
    MOV AL,buffer[DI] 
    CMP al, '+'
    JE GETPUNTO1
    CMP al, '$'
    JE ENDF
    INC DI
    JMP INICIO
GETPUNTO1:
    clear arraypuntos
    INC DI
    JMP GETPUNTO    
GETPUNTO:
    MOV AL, buffer[DI]
    CMP AL, '*'
    JE FIN 
    MOV arraypuntos[SI], AL
    INC DI
    INC SI 
    JMP GETPUNTO
FIN:

CovertirAscii arraypuntos
printChar AL
MOV arraynumeros[0], Al
INC BX
INC DI 

JMP INICIO

ENDF:
print arraypuntos
;call ord 
POP SI
POP AX
POP DI
endm




;45,42,2,6,8,9,32,65,1,55



bubble macro buffer
LOCAL INICIO, FIN, CICLO1
PUSH SI
PUSH DI

MOV CX, 15
MOV SI, 0
MOV DI, 0

CICLO1:
    PUSH CX
    MOV SI, OFFSET buffer
    MOV DI, SI
CICLO2:
    INC DI
    MOV AL, [SI]
    CMP AL, [DI]
    JA INTERCAMBIO
    JB MENOR

INTERCAMBIO:
    MOV AH, [DI]
    MOV [DI], AL
    MOV [SI], AH
MENOR:
    INC SI
    LOOP CICLO2
    POP CX
    LOOP CICLO1
FIN:
    printChar arraynumeros[0]
endm
















ordenar2 macro buffer
LOCAL INICIO, GETPUNTO,GETPUNTO1, FIN, ENDF

print buffer

PUSH DI
PUSH AX
PUSH SI
MOV DI, 0
MOV SI, 0
INICIO:
    MOV AL,buffer[DI] 
    CMP al, '+'
    JE GETPUNTO1
    CMP al, '$'
    JE ENDF
    INC DI
    JMP INICIO
GETPUNTO1:
    INC DI
    JMP GETPUNTO    
GETPUNTO:
    MOV AL, buffer[DI]
    CMP AL, '*'
    JE FIN 
    MOV arraypuntos[SI], AL
    INC DI
    INC SI 
    JMP GETPUNTO
FIN:
MOV SI, 0
INC DI 
CovertirAscii arraypuntos
ConvertirString arraypuntos
print arraypuntos


JMP INICIO

ENDF:
POP SI
POP AX
POP DI
endm