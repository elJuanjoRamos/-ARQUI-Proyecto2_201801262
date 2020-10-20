;======================= SECCION MACROS
include amacros.inc
include alogin.inc
include archivos.inc
include aordenar.inc
;include aregistro.inc
;=======================SECCION DE EJECUTABLE
.model small
.stack  
.data

;====================== SEGMENTO DE DATOS =================
;========== VARIABLES



encab           db 'UNIVERSIDAD DE SAN CARLOS DE GUATEMALA', 10,13,  'FACULTAD DE INGENIERIA',10,13, 'CIENCIAS Y SISTEMAS',10,13,'ARQUITECTURA DE COMPUTADORES Y ENSAMBLADORES', 10,13, 'JUAN JOSE RAMOS CAMPOS', 10,13, '201801262', 10,13,'SECCION:A',10,13, ' ',10,13, '1) Ingresar',10,13,'2) Registrar',10,13, '3) Salir', 10,13,10,13, 'Escoja Una opcion:','$'  
encablogin      db 10,13,'==================    LOGIN     ===================', 10,13,'$'  
encabregist     db 10,13,'==================   REGISTRO   ===================', 10,13,'$'  


;=============== USER
usuario         db 7 dup('$') ; username
passw           db 4 dup('$') ; username
listausuarios   db 100 dup('$'), '$'

;============== ordenamiento
ordenartemp     db 100 dup('$'), '$'
ordenartemp2    db 100 dup('$'), '$'
arraypuntos     db 100 dup('$'), '$'
ordenado           db 100 dup('$'), '$'


;======================


bordes          db 10,13,'---------------------------------------------------',10,13,'$'
encabtopt       db 10,13,'                  TOP 10 TIEMPOS                   ', 10,13,'$'  
encabtopP       db 10,13,'                   TOP 10 PUNTOS                   ', 10,13,'$'  




;========LOGIN
admin           db 'adminap', '$'
pass            db '1234', '$'


ingreseuser     db 10,13,'Ingrese Usuario: ','$'
ingresepass     db 10,13,'Ingrese Pass: ','$'
errorlogin      db 10,13,'User o Password incorrecta', 10,13,'$'
usuarioexiste   db 10,13,'El usuario con el username ya existe: ','$'
usuarionoexiste db 10,13,'Usuario ingresado correctamente ',10,13,'$'

;=========login admin

encabadmin      db 10,13,'1) Top 10 putnos',10,13,'2) Top 10 tiempos',10,13, '3) Salir', 10,13,10,13, 'Escoja Una opcion:','$'  
salto           db 10,13, 10,13,'$'


salto1          db 10,13,'$'
prueba          db 10,13,'entro', 10,13,'$'


arraynumeros db 45,42,2,6,8,9,32,65,1,55


;================ archivo

filepath    db 100 dup('$') ; ruta archivo
buffread    db 500 dup('$') ; buffer lectura
buffwrite   db 500 dup('$') ; buffer escritura
handlefile  dw ?

msmError1   db 0ah,0dh,'Error al abrir archivo','$'
msmError2   db 0ah,0dh,'Error al leer archivo','$'
msmError3   db 0ah,0dh,'Error al crear archivo','$'
msmError4   db 0ah,0dh,'Error al Escribir archivo','$'
msgOpenFile db 0ah,0dh, 'Ingrese el nombre de archivo: ', 32, '$'








;======================= SEGMENTO CODIGO ==================
.code
main proc
    MENUPRINCIPAL:
        JMP TOPPUNTOS
    ;print encab
    ;getChar
    ;cmp al,'1' 
    ;je INGRESAR
    ;cmp al,'2'
    ;je REGISTRAR
    ;cmp al,'3'
    ;je ENDGAME
    ;jmp MENUPRINCIPAL


;========== ARCHIVO






INGRESAR:
    print encablogin
    print ingreseuser
    clear usuario
    getlogin usuario
    clear passw
    print ingresepass
    getlogin passw
    COMPARARUSER usuario, passw

JMP INGRESAR



REGISTRAR:
    print encabregist
    print ingreseuser
    clear usuario
    getlogin usuario
    COMPARARREGISTRO usuario
JMP REGISTRAR

REGISTRAR2:
    clear passw
    print ingresepass
    getlogin passw

    INSERTARUSER usuario, passw



JMP MENUPRINCIPAL




USERLOGUEADO:   
    print bordes

    print encabadmin

    getChar

    cmp al,'1' 
    je TOPPUNTOS
    cmp al,'2'
    je TOPTIEMPOS
    cmp al,'3'
    je MENUPRINCIPAL

JMP USERLOGUEADO



TOPPUNTOS:
    print bordes
    print encabtopt
    clear filepath
    print msgOpenFile
    getRuta filepath
    openFile filepath, handlefile
    readFile SIZEOF buffread,buffread,handlefile
    ordenar buffread

    bubble buffread
JMP TOPPUNTOS
    






TOPTIEMPOS:


JMP TOPTIEMPOS




































ErrorAbrir:
	print msmError1
	getChar
	jmp MENUPRINCIPAL
ErrorLeer:
;	print msmError2
;	getChar
	jmp MENUPRINCIPAL
ErrorCrear:
;	print msmError3
;	getChar
	jmp MENUPRINCIPAL
ErrorEscribir:
;	print msmError4
;	getChar
	jmp MENUPRINCIPAL


ENDGAME:
 ;   print final
    mov ah,4ch
    int 21h

main endp


ord PROC FAR ; es un procedimiento que llama

LOCAL valor1, valor2, i, j, k, n, bcontinuar,nmenos1
PUSH DI
PUSH SI
PUSH BX

INICIO:
    MOV nmenos1, -1
    dec nmenos1
    MOV BX, OFFSET arraypuntos
    MOV j, -1
    MOV i, 0
    MOV SI, 2
MIENTRASBCONTINUARES1:
    MOV bcontinuar, 0
    MOV BX, OFFSET arraypuntos

POP BX
POP SI
POP DI

ord ENDP



end
