;======================= SECCION MACROS
include amacros.inc
include alogin.inc
include archivos.inc
include aordenar.inc
include ajuego.inc
;=======================SECCION DE EJECUTABLE
.model small
.stack  
.data

;====================== SEGMENTO DE DATOS =================
;========== VARIABLES



encab           db 'UNIVERSIDAD DE SAN CARLOS DE GUATEMALA', 10,13,  'FACULTAD DE INGENIERIA',10,13, 'CIENCIAS Y SISTEMAS',10,13,'ARQUITECTURA DE COMPUTADORES Y ENSAMBLADORES', 10,13, 'JUAN JOSE RAMOS CAMPOS', 10,13, '201801262', 10,13,'SECCION:A',10,13, ' ',10,13, '1) Ingresar',10,13,'2) Registrar',10,13, '3) Salir', 10,13,10,13, 'Escoja Una opcion:','$'  
encablogin      db 10,13,'==================    LOGIN     ===================', 10,13,'$'  
encabregist     db 10,13,'==================   REGISTRO   ===================', 10,13,'$'  

AUX_TIEMPO      db 0    ; auxiliar para verificar si cambia el tiempo 

BALL_ORIGINAL_X dw 0A0h
BALL_ORIGINAL_Y dw 64h
BALL_X          dw 0A0h ; posicion x columna
BALL_Y          dw 64h ; posicion y linea
BALL_SIZE       dw 04h
BALL_VELOCIDADX dw 02h ; VELOCIDAD EN X DE LA PELOTA
BALL_VELOCIDADY dw 02h  ; VELOCIDAD EN Y DE LA PELOTA

PANTALLA_ALTO   dw  0C8h
PANTALLA_ANCHO  dw  130h
PANTALLA_MARGEN dw 6    ; variable para ver las coliciones

PADDLE_LEFT_x   dw 08Ch
PADDLE_LEFT_Y   dw 0A0h




PADDLE_ANCHO    dw 05h
PADDLE_ALTO     dw 32h

PADDLE_VEL      dw 0Fh







;=============== USER
usuario         db 8 dup('$') ; username
usuariotemp     db 8 dup('$') ; username
passw           db 5 dup('$') ; username
listausuarios   db 100 dup('$'), '$'


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
salto           db 10,13,'$'




;================ archivo

filepath    db 100 dup('$') ; ruta archivo
buffread    db 500 dup('$') ; buffer lectura
buffwrite   db 500 dup('$') ; buffer escritura
handlefile  dw ?

msmError1   db 0ah,0dh,'Error al abrir archivo','$'
msmError2   db 0ah,0dh,'Error al leer archivo','$'
msmError3   db 0ah,0dh,'Error al crear archivo','$'
msmError4   db 0ah,0dh,'Error al Escribir archivo','$'
msmError5   db 0ah,0dh,'Nombre de usuario demaciado largo','$'
msmError6   db 0ah,0dh,'Password de usuario demaciado largo','$'
msmError7   db 0ah,0dh,'Password no es numerica','$'

msgOpenFile db 0ah,0dh, 'Ingrese el nombre de archivo: ', 32, '$'

mensaje   db 0ah,0dh,'USERS IGUALES','$'
mensaje1   db 0ah,0dh,'estoy aqui','$'


;======================= SEGMENTO CODIGO ==================
.code
main proc
    MENUPRINCIPAL:
    print encab
    getChar
    cmp al,'1' 
    je NUEVO_JUEGO
    cmp al,'2'
    je REGISTRAR
    ;cmp al,'3'
    ;je ENDGAME
    ;jmp MENUPRINCIPAL



;======================= INGRESAR
INGRESAR:
    print encablogin
    print ingreseuser
    clear usuario

    print salto
    print listausuarios
    print salto
    
    getUser usuario
    clear passw
    print ingresepass
    getPassword passw
    COMPARARUSER usuario, passw

JMP INGRESAR


;===================== REGISTRAR

REGISTRAR:
    print encabregist
    print ingreseuser
    clear usuario
    getUser usuario
    COMPARARREGISTRO usuario
JMP REGISTRAR

REGISTRAR2:
    clear passw
    print ingresepass
    getPassword passw

    INSERTARUSER usuario, passw
JMP MENUPRINCIPAL











USERLOGUEADO:   
    print bordes

    print encabadmin

    getChar

    cmp al,'1' 
    ;je TOPPUNTOS
    cmp al,'2'
    ;je TOPTIEMPOS
    cmp al,'3'
    je MENUPRINCIPAL

JMP USERLOGUEADO






ErrorAbrir:
	;print msmError1
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




;======================= SECCION JUEGO =============================





NUEVO_JUEGO:
  
    
    INIT:
        ENTER_VIDEOMODE
        DRAW_BLOCK
        CALL PINTBALL
        CALL DRAWPADDLES
        
    INICIO_JUEGO:

        
        ;VERIFICAR SI SE PRESIONO UNA TECLA, SI NO, SALIR
        MOV AH, 01h
        INT 16h
        JZ INICIO_JUEGO ; SI ZF = 1, entonces JZ-> jump a la tag
        ; SI SE PRECIONO VERIFICAR QUE TECLA FUE; AL = ASCII code
        MOV AH, 00h 
        INT 16h    
        ;SI ES 'SPACE' SALTA AL JUEGO, SI NO REGRESA
        CMP AL, 32 ; -> 'SPACE'
        JE VERIFICAR_TIEMPO
        JNE INICIO_JUEGO




    VERIFICAR_TIEMPO:
        MOV AH, 2Ch ; obtener tiempo del sistema
        INT 21h     ; ch = hora, cl = minuto, dh = segundo

        CMP DL, AUX_TIEMPO ; el tiempo actual es igual al anterior(AUX_TIME)?
                       
        JE VERIFICAR_TIEMPO

        MOV AUX_TIEMPO, DL ; ACTUALIZAR TIEMPO
        
        ;ENTER_VIDEOMODE
        ;CALL videomode ; limpiar la pantalla
        CALL WRITE_TIME
        DRAW_BLOCK
        

        CALL MOVERBALL ; mover la pelota
        CALL PINTBALL
        CALL MOVEPADDLES
        CALL DRAWPADDLES
        JMP VERIFICAR_TIEMPO

    JMP FIN


;======= PINTA LOS BORDES

DRAWPADDLES PROC near
    MOV CX, PADDLE_LEFT_x
    MOV DX, PADDLE_LEFT_Y

    DRAW_PADDLE_LEFT_HORIZONTAL:
        MOV AH, 0Ch ;config para escribir pixel
        MOV AL, 0FH ; choose color
        MOV BH, 00h ; set the page number
        INT 10H         ; execute configuration 
        INC CX      ; CX = CX + 1
        MOV AX, CX
        SUB AX, PADDLE_LEFT_x
        CMP AX, PADDLE_ALTO
        JNG DRAW_PADDLE_LEFT_HORIZONTAL
        MOV CX, PADDLE_LEFT_x
        INC DX
        MOV AX, DX
        SUB AX, PADDLE_LEFT_Y
        CMP AX, PADDLE_ANCHO
        JNG DRAW_PADDLE_LEFT_HORIZONTAL
    RET
DRAWPADDLES ENDP


;======== RESETEA LA POSICION DE LA PELOTA CUANDO LLEGA AL MARGEN DE ABAJO
RESET_POSICION_PELOTA proc near
    MOV BALL_VELOCIDADX, 02h ; VELOCIDAD EN X DE LA PELOTA
    MOV BALL_VELOCIDADY, 02h  ; VELOCIDAD EN Y DE LA PELOTA
    MOV AX, BALL_ORIGINAL_X
    MOV BALL_X, AX
    MOV AX, BALL_ORIGINAL_Y
    MOV BALL_Y, AX

    RET
RESET_POSICION_PELOTA endp


;===== PROCEDIMIENTO PARA MOVER PELOTA
MOVERBALL proc near
    


    BLOQUES:        
        ; COLICION CON BLOQUES
        MOV AH, 0Dh	
        MOV CX, BALL_X 
        MOV DX, BALL_Y
        INT 10H
        CMP AL, 5
        JE NEG_VELOCIDAD_Y
        JNE NORMAL


    NORMAL:
            MOV AX, BALL_VELOCIDADX 
            ADD BALL_X, AX  ; MOVER PELOTA HORIZONTAL


            ; COLICIONES
            
            
            ; COLICION EN LOS MARGENES
                                            
            ; MARGEN IZQUIERDO
            MOV AX, PANTALLA_MARGEN         ; BALL_X < 0 (Y-> colicion IZQUIERDA)
            CMP BALL_X, AX
            JL NEG_VELOCIDAD_X                    ;

            ; MARGEN DERECHO
            MOV AX, PANTALLA_ANCHO          ; BALL_x > BORDE DE LA PANTALLA =  COLICION DERECHA
            SUB AX, BALL_SIZE
            SUB AX, PANTALLA_MARGEN
            CMP BALL_X, AX
            JG NEG_VELOCIDAD_X


            ; COLICION CON LOS MARGEN SUPERIOR E INFERIOR


            MOV AX, BALL_VELOCIDADY        
            ADD BALL_Y, AX  ; MOVER PELOTA VERTICAL

            ; MARGEN SUPERIOR
            MOV AX, PANTALLA_MARGEN
            CMP BALL_Y, AX
            JL COLICION_ARRIBA
                                ;
            ; MARGEN INFERIOR
            MOV AX, PANTALLA_ALTO
            SUB AX, BALL_SIZE
            SUB AX, PANTALLA_MARGEN
            CMP BALL_Y, AX
            JG RESET_POSICION


            ; VERIFICAR SI COLICIONA
            ; ball_Y + BALL SIZE > PADDLE_LEFT_Y && BALL_Y < PADDLE_LEFT_Y + PADDLE_ALTO && BALL_x + BALL SIZE  > PADDLE_LEFT_X && BALL_X < PADDLE RIGT X + PADDLE_ANCHO


            ; COLICION CON BARRA
            MOV AX, BALL_X
            ADD AX, BALL_SIZE
            CMP AX, PADDLE_LEFT_x
            JNG CHECK_COLISION

            MOV AX, PADDLE_LEFT_X
            ADD AX, PADDLE_ALTO
            CMP BALL_X, AX
            JNL CHECK_COLISION

            MOV AX, BALL_Y
            ADD AX, BALL_SIZE
            CMP AX, PADDLE_LEFT_Y
            JNG CHECK_COLISION


            MOV AX, PADDLE_LEFT_Y
            ADD AX, PADDLE_ANCHO
            CMP BALL_Y, AX 
            JNL CHECK_COLISION 


            NEG BALL_VELOCIDADY
            RET


    
    NEG_VELOCIDAD_Y:
        DELETE_BLOCK BALL_Y
        NEG BALL_VELOCIDADY
        JMP NORMAL
        
    CHECK_COLISION:
        ENTER_VIDEOMODE
        ;NEG BALL_VELOCIDADY

    RET

    NEG_VELOCIDAD_X:
        NEG BALL_VELOCIDADX
        RET
    
   
    

    RESET_POSICION:
        CALL RESET_POSICION_PELOTA
        RET

    COLICION_ARRIBA:
        ;NEG BALL_VELOCIDADX
        NEG BALL_VELOCIDADY
        RET

        
MOVERBALL endp

MOVEPADDLES PROC near

    
    ;VERIFICAR SI SE PRESIONO UNA TECLA, SI NO, SALIR
    MOV AH, 01h
    INT 16h
    JZ CHECK_MOVIMIENTO ; SI ZF = 1, entonces JZ-> jump a la tag


   
    ; SI SE PRECIONO VERIFICAR QUE TECLA FUE; AL = ASCII code
    MOV AH, 00h 
    INT 16h    
    ;SI ES 'A' IQUIERDA, 'D' DERECHA
    CMP AL, 61h ; -> 'a'
    JE MOVE_IZQUIERDA
    CMP AL, 41h ; -> 'A' 
    JE MOVE_IZQUIERDA


    CMP AL, 64h ; -> 'd'
    JE MOVE_DERECHA
    CMP AL, 44h ; -> 'D' 
    JE MOVE_DERECHA


    CMP AL, 1Bh ; -> 'ESC'
    JE INIT

    JMP CHECK_MOVIMIENTO

    MOVE_IZQUIERDA:
        MOV AX, PADDLE_VEL
        SUB PADDLE_LEFT_x, AX
        MOV AX, PANTALLA_MARGEN
        CMP PADDLE_LEFT_X, AX
        JL  ARREGLAR_PADDLE_POSICION_IZ
        JMP DRAW_NEW_POSITION


    MOVE_DERECHA:
        MOV AX, PADDLE_VEL
        ADD PADDLE_LEFT_X, AX
        MOV AX, PANTALLA_ANCHO
        SUB AX, PANTALLA_MARGEN
        SUB AX, PADDLE_ALTO
        CMP PADDLE_LEFT_X, AX 
        JG ARREGLAR_PADDLE_POSICION_DER
        JMP DRAW_NEW_POSITION

    ARREGLAR_PADDLE_POSICION_IZ:
        MOV AX, PANTALLA_MARGEN
        MOV PADDLE_LEFT_X, AX
        ENTER_VIDEOMODE
        JMP CHECK_MOVIMIENTO

    ARREGLAR_PADDLE_POSICION_DER:
        MOV PADDLE_LEFT_X, AX
        ENTER_VIDEOMODE
        JMP CHECK_MOVIMIENTO

    DRAW_NEW_POSITION:
        ENTER_VIDEOMODE
        DRAW_BLOCK
        JMP CHECK_MOVIMIENTO

    CHECK_MOVIMIENTO:
        
    
    RET
MOVEPADDLES ENDP


;============= PRINTAR LA PELOTA
PINTBALL proc near

    MOV CX, BALL_X ; set column x
    MOV DX, BALL_Y ; set column y
    
    DIV_PELOTA_HORIZONTAL:
        MOV AH, 0Ch ;config para escribir pixel
        MOV AL, 0FH ; choose color
        MOV BH, 00h ; set the page number
        INT 10H         ; execute configuration 
        INC CX      ; CX = CX + 1
        MOV AX, CX
        SUB AX, BALL_X
        CMP AX, BALL_SIZE
        JNG DIV_PELOTA_HORIZONTAL 
        MOV CX, BALL_X
        INC DX
        MOV AX, DX
        SUB AX, BALL_Y
        CMP AX, BALL_SIZE
        JNG DIV_PELOTA_HORIZONTAL
    
    ret
PINTBALL endp


videomode proc near
    
    MOV AH, 00h ; video mode
    MOV AL, 13h
    int 10H
	mov ax,0A000h

    MOV AH, 0Bh ; set configuracion
    MOV BH, 00h ; background color
    MOV BL, 00h ; color para el background
    INT 10H     ; ejecutar configuracion
    ret 
videomode endp

WRITE_TIME proc near
    MOV AH, 0Ah
    MOV AL, 53
    MOV BH, 0
    MOV CX, 2
    RET
WRITE_TIME endp



FIN:


end


