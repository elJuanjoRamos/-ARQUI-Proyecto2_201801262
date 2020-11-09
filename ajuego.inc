
ENTER_VIDEOMODE MACRO 
	PUSH_VARS  
	PUSH_PUNTEO
	PUSH_USER
	PUSH_TIEMPO
    MOV AH, 00h ; video mode
    MOV AL, 13h
    int 10H
	MOV ax,0A000h
	MOV ds ,ax
	POP_TIEMPO
	POP_USER
    POP_PUNTEO
	POP_VARS
    MOV AH, 0Bh ; set configuracion
    MOV BH, 00h ; background color
    MOV BL, 00h ; color para el background
    INT 10H     ; ejecutar configuracion

ENDM 








PUSH_VARS MACRO

	PUSH_VARS2 BALL_ORIGINAL_X
	PUSH_VARS2 BALL_ORIGINAL_Y 

	PUSH_VARS2 BALL_X ; poSIcion x columna
	PUSH_VARS2 BALL_Y ; poSIcion y linea
	PUSH_VARS2 BALL_SIZE

	PUSH_VARS2 BALL_VELOCIDADX  ; VELOCIDAD EN X DE LA PELOTA
	PUSH_VARS2 BALL_VELOCIDADY  ; VELOCIDAD EN Y DE LA PELOTA

	PUSH_VARS2 PANTALLA_ALTO   
	PUSH_VARS2 PANTALLA_ANCHO  
	PUSH_VARS2 PANTALLA_MARGEN  ; variaBLe para ver las coliciones
	PUSH_VARS2 PADDLE_LEFT_x   
	PUSH_VARS2 PADDLE_LEFT_Y   

	PUSH_VARS2 PADDLE_ANCHO    
	PUSH_VARS2 PADDLE_ALTO     

	PUSH_VARS2 PADDLE_VEL


ENDM 


PUSH_VARS2 MACRO VALOR
    XOR AX, AX
    MOV AX, 0
    MOV AX, VALOR
    PUSH AX
ENDM






POP_VARS MACRO

	POP_VARS2 PADDLE_VEL      

	POP_VARS2 PADDLE_ALTO     
	POP_VARS2 PADDLE_ANCHO    

	POP_VARS2 PADDLE_LEFT_Y   
	POP_VARS2 PADDLE_LEFT_x   

	POP_VARS2 PANTALLA_MARGEN  ; variaBLe para ver las coliciones
	POP_VARS2 PANTALLA_ANCHO  
	POP_VARS2 PANTALLA_ALTO   

	POP_VARS2 BALL_VELOCIDADY  ; VELOCIDAD EN Y DE LA PELOTA
	POP_VARS2 BALL_VELOCIDADX  ; VELOCIDAD EN X DE LA PELOTA


	POP_VARS2 BALL_SIZE
	POP_VARS2 BALL_Y           ; poSIcion y linea
	POP_VARS2 BALL_X           ; poSIcion x columna
	POP_VARS2 BALL_ORIGINAL_Y 
	POP_VARS2 BALL_ORIGINAL_X 
	MOV AUX_TIEMPO, 0      
ENDM   


POP_VARS2 MACRO VARIABLE 
    MOV AX, 0
    POP AX
    MOV VARIABLE, AX
ENDM



PUSH_PUNTEO MACRO
	MOV AL, CONTADOR_PUNTOS
	MOV AH, 0
	PUSH AX
ENDM


POP_PUNTEO MACRO 
LOCAL INICIO, FIN
	POP AX
	MOV CONTADOR_PUNTOS, AL
	MOV AH, 0
	ConvertirString puntaje
ENDM





PUSH_USER MACRO 
LOCAL INICIO, FIN
MOV DI, 0
INICIO:
	MOV AL, usuario[DI]
	MOV AH, 0
	PUSH AX
	INC DI
	CMP DI, 8
	JE FIN
	JMP INICIO
FIN:
endm


POP_USER MACRO
LOCAL INICIO, FIN
MOV DI, 7
INICIO:
	POP AX
	MOV usuario[DI], AL
	DEC DI
	CMP DI, -1
	JE FIN
	JMP INICIO
FIN:
ENDM




PUSH_TIEMPO MACRO
	MOV AL, CONTADOR_HORA
	MOV AH, 0
	PUSH AX

	MOV AL, CONTADOR_MINUTO
	MOV AH, 0
	PUSH AX

	MOV AL, CONTADOR_SEGUNDO
	MOV AH, 0
	PUSH AX
	
ENDM

POP_TIEMPO MACRO
	POP AX
	MOV CONTADOR_SEGUNDO, AL
	MOV AH, 0
	ConvertirString timerseg

	POP AX
	MOV CONTADOR_MINUTO, AL
	MOV AH, 0
	ConvertirString timermin


	POP AX
	MOV CONTADOR_HORA, AL
	MOV AH, 0
	ConvertirString timerhor

ENDM









;=============================== DIBUJAR LOS BLOQUES 
DRAW_BLOCK macro 
	local BUCLE,REPETIR, fin
	
		MOV BX, 0 
		MOV DI, 6736 ;pixel de inicio = esquina superior izquierda
		MOV SI, 0
		MOV DX, 5 ; color 
		MOV CX, 3FC0h
	
		BUCLE:
			MOV [DI],dx 
			INC DI 
			INC SI 
			CMP SI,34 
			JNE REPETIR
			ADD DI,2
			MOV SI,0
			INC BL 
			CMP BL,8
			JNE REPETIR
			ADD DI,32
			MOV BL, 0 
			INC BH 
			CMP BH,10
			JNE REPETIR  
			ADD DI,640
			MOV BH, 0 
		
		REPETIR:
		loop BUCLE
	endm





;=============================== DIBUJAR EL BORDE 
DRAW_BORDE MACRO 
LOCAL INICIO, FIN
local SUPERIOR, INFERIOR, IZQUIERDO, DERECHO, REPETIR, REPETIR_INFERIOR, REPETIR_IZQUIERDO, REPETIR_DERECHO, STOP
	;MARGEN SUPERIOR	
	MOV DI, 5450 ;pixel de inicio = esquina superior izquierda
	MOV DX, 0Fh ; color 
	MOV CX, 127h
	
		SUPERIOR:
			MOV [DI],dx 
			INC DI 	
		REPETIR:
		loop SUPERIOR
	; MARGEN INFERIOR
	MOV DI, 54730 ;pixel de inicio = esquina inferior izquierda
	MOV SI, 0
	MOV DX, 0Fh ; color 
	MOV CX, 127h

		INFERIOR:
			MOV [DI],DX 
			INC DI
		REPETIR_INFERIOR:
		loop INFERIOR

	; MARGEN IZQUIERDO
	MOV DI, 5450 ;pixel de inicio = esquina superior izquierda
	MOV DX, 0Fh ; color 
	MOV CX, 4Eh
	
		IZQUIERDO:
			MOV [DI],dx 
			ADD DI, 640 	
		REPETIR_IZQUIERDO:
		loop IZQUIERDO


	; MARGEN DERECHO
	MOV DI, 5745 ;pixel de inicio = esquina superior izquierda
	MOV DX, 0Fh ; color 
	MOV CX, 4Eh
	
		DERECHO:
			MOV [DI],dx 
			ADD DI, 640 	
		REPETIR_DERECHO:
		loop DERECHO
		STOP:
endm
;==============================	DIBUJAR NOMBRE DE USUARIO
DRAW_USER MACRO 
LOCAL INICIO, FIN
	MOV DI, 0
	MOV CONTADOR_LOOPS, 2
INICIO:
	MOV AL, usuario[DI]
	LOOP_USER AL, CONTADOR_LOOPS
	INC DI
	INC CONTADOR_LOOPS
	CMP DI, 8
	JE FIN
	JMP INICIO
FIN:
ENDM


LOOP_USER MACRO caracter, columna
LOCAL INICIO,  FIN

INICIO:
	CMP caracter, '$'
	JE FIN
	;REPOSICIONAR EL CURSOR
	MOV AH, 02H
	MOV BH, 0 		;Página de vídeo
	MOV DH, 1h 	;Línea donde situar el cursor
	MOV DL, columna 	;Columna donde situar el cursor
	INT 10H
	; ESCRIBIR CARACTERES
	MOV AH, 09H
	MOV AL, caracter	; Código del carácter a escribir.
	MOV BH, 0	; Página de vídeo donde escribir el carácter.
	MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
	MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
	INT 10h
FIN:

ENDM

;========================== DIBUJAR EL NIVEL
DRAW_NIVEL MACRO 
	;REPOSICIONAR EL CURSOR
	MOV AH, 02H
	MOV BH, 0 		;Página de vídeo
	MOV DH, 1h 	;Línea donde situar el cursor
	MOV DL, 0Fh 	;Columna donde situar el cursor
	INT 10H
	; ESCRIBIR 'N'
	MOV AH, 09H
	MOV AL, 78	; Código del carácter a escribir.
	MOV BH, 0	; Página de vídeo donde escribir el carácter.
	MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
	MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
	INT 10h

	;REPOSICIONAR EL CURSOR
	MOV AH, 02H
	MOV BH, 0 		;Página de vídeo
	MOV DH, 1h 	;Línea donde situar el cursor
	MOV DL, 10h 	;Columna donde situar el cursor
	INT 10H
	; ESCRIBIR NIVEL
	MOV AH, 09H
	MOV AL, 49	; Código del carácter a escribir.
	MOV BH, 0	; Página de vídeo donde escribir el carácter.
	MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
	MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
	INT 10h
ENDM

;========================== DIBUJAR LOS PUNTOS
AUMENTAR_PUNTOS MACRO
	INC CONTADOR_PUNTOS
ENDM

DRAW_PUNTOS MACRO 
LOCAL INICIO, FIN, CORREGIR, NORMAL
	LOOP_PUNTOS '0', 14h

	MOV AL, CONTADOR_PUNTOS
	CMP AL, 9
	JG CORREGIR
	JMP NORMAL

CORREGIR:
	LOOP_TIEMPO puntaje[0], 15h
	LOOP_TIEMPO puntaje[1], 16h
	JMP FIN
NORMAL:
	LOOP_TIEMPO puntaje[1], 15h
	LOOP_TIEMPO puntaje[0], 16h
	
FIN:
		
ENDM

LOOP_PUNTOS MACRO caracter, columna
LOCAL INICIO, FIN, CORREGIR
	MOV AL, caracter
	CMP AL, '$'
	JE CORREGIR
	JMP INICIO
CORREGIR:
	MOV AL, '0'
INICIO:
	;REPOSICIONAR EL CURSOR POSICION 20, 0
		MOV AH, 02H
		MOV BH, 0 	;Página de vídeo
		MOV DH, 1h 	;Línea donde situar el cursor
		MOV DL, columna ;Columna donde situar el cursor
		INT 10H
		; ESCRIBIR PUNTEO
		MOV AH, 09H
		;MOV AL, caracter	; Código ASCII del carácter a escribir.
		MOV BH, 0	; Página de vídeo donde escribir el carácter.
		MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
		MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
		INT 10h

FIN:
ENDM



;========================== DIBUJAR EL TIMER

DRAW_TIMER MACRO 
LOCAL INICIO, CEROCERO, NORMAL, MOSTAR_MINUTO, AUMETAR_MINUTO, AUMENTAR_HORA, MOSTAR_HORA, CORREGIR, AVANZAR
	 
	INC CONTADOR_SEGUNDO

	LOOP_TIEMPO ':', 25h
	LOOP_TIEMPO timerseg[0], 26h
	LOOP_TIEMPO timerseg[1], 27h

	CMP CONTADOR_SEGUNDO, 100
	JE AUMETAR_MINUTO
	JMP MOSTAR_MINUTO
	CMP CONTADOR_SEGUNDO, 10
	JE AUMETAR_MINUTO
	JMP MOSTAR_MINUTO
	CMP CONTADOR_SEGUNDO, 20
	JE AUMETAR_MINUTO
	JMP MOSTAR_MINUTO

AUMETAR_MINUTO:
	INC CONTADOR_MINUTO


MOSTAR_MINUTO:
	LOOP_TIEMPO ':', 22h
	MOV AL, CONTADOR_MINUTO 
	CMP AL, 10
	JG CORREGIR
	JMP NORMAL

CORREGIR:
	LOOP_TIEMPO timermin[0], 23h
	LOOP_TIEMPO timermin[1], 24h
	JMP AVANZAR

NORMAL:	 
	LOOP_TIEMPO timermin[1], 23h
	LOOP_TIEMPO timermin[0], 24h



AVANZAR:
	CMP CONTADOR_MINUTO, 60
	JE AUMENTAR_HORA
	JMP MOSTAR_HORA

AUMENTAR_HORA:
	INC CONTADOR_HORA

MOSTAR_HORA:
	LOOP_TIEMPO timerhor[1], 20h
	LOOP_TIEMPO timerhor[0], 21h
	

ENDM


LOOP_TIEMPO MACRO caracter, columna


LOCAL INICIO, FIN, CORREGIR
	MOV AL, caracter
	CMP AL, '$'
	JE CORREGIR
	JMP INICIO
CORREGIR:
	MOV AL, '0'
INICIO:

	;REPOSICIONAR EL CURSOR POSICION 20, 0
		MOV AH, 02H
		MOV BH, 0 	;Página de vídeo
		MOV DH, 1h 	;Línea donde situar el cursor
		MOV DL, columna ;Columna donde situar el cursor
		INT 10H
		; ESCRIBIR PUNTEO
		MOV AH, 09H
		;MOV AL, caracter	; Código ASCII del carácter a escribir.
		MOV BH, 0	; Página de vídeo donde escribir el carácter.
		MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
		MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
		INT 10h

FIN:
ENDM


;==========================	MENSAJE DESPEDIDA

DRAW_MENSAJE MACRO
	;GRACIAS POR JUGAR! 
	LOOP_MENSAJE 'G', 0Ah, 5h
	LOOP_MENSAJE 'R', 0Bh, 5h
	LOOP_MENSAJE 'A', 0Ch, 5h
	LOOP_MENSAJE 'C', 0Dh, 5h
	LOOP_MENSAJE 'I', 0Eh, 5h
	LOOP_MENSAJE 'A', 0Fh, 5h
	LOOP_MENSAJE 'S', 10h, 5h
	LOOP_MENSAJE ' ', 11h, 5h
	LOOP_MENSAJE 'P', 12h, 5h
	LOOP_MENSAJE 'O', 13h, 5h
	LOOP_MENSAJE 'R', 14h, 5h
	LOOP_MENSAJE ' ', 15h, 5h
	LOOP_MENSAJE 'J', 16h, 5h
	LOOP_MENSAJE 'U', 17h, 5h
	LOOP_MENSAJE 'G', 18h, 5h
	LOOP_MENSAJE 'A', 19h, 5h
	LOOP_MENSAJE 'R', 1Ah, 5h
	LOOP_MENSAJE '!', 1Bh, 5h


	LOOP_MENSAJE 219, 13h, 0Ah

	LOOP_MENSAJE 219, 0Eh, 0Dh
	LOOP_MENSAJE 219, 0Fh, 0Dh
	LOOP_MENSAJE 219, 10h, 0Dh
	LOOP_MENSAJE 219, 11h, 0Dh
	LOOP_MENSAJE 219, 12h, 0Dh
	LOOP_MENSAJE 219, 13h, 0Dh
	LOOP_MENSAJE 219, 14h, 0Dh
	LOOP_MENSAJE 219, 15h, 0Dh
	LOOP_MENSAJE 219, 16h, 0Dh
	LOOP_MENSAJE 219, 17h, 0Dh
	

ENDM

LOOP_MENSAJE MACRO caracter, columna, linea
	;REPOSICIONAR EL CURSOR POSICION 20, 0
	MOV AH, 02H
	MOV BH, 0 	;Página de vídeo
	MOV DH, linea 	;Línea donde situar el cursor
	MOV DL, columna ;Columna donde situar el cursor
	INT 10H
	; ESCRIBIR PUNTEO
	MOV AH, 09H
	MOV AL, caracter	; Código ASCII del carácter a escribir.
	MOV BH, 0	; Página de vídeo donde escribir el carácter.
	MOV BL, 0Fh ; Atributo ó color que va a tener el carácter.  
	MOV CX, 1 	; Cantidad de veces que se debe escribir el carácter, uno a continuación de otro
	INT 10h
ENDM