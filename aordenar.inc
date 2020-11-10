ORDENAR_TOPPUNTOS MACRO 
    PUSH_NUMEROS
    MOV AH, 00h ; video mode
    MOV AL, 13h
    int 10H
	MOV ax,0A000h
	MOV ds ,ax
	DRAW_BORDE_BARRA
    POP_NUMERO

ENDM
PUSH_NUMEROS macro
	LOCAL INICIO,FIN  
		;CANT_ELEMENTOS numeros
		MOV DX,10 
		MOV si,0
		xor AX,AX 
		INICIO:
			CMP si,DX
			JE FIN 
			MOV AL,numeros[si]
			push AX
			INC si 
			JMP INICIO
		FIN:
		push DX 

	endm 

POP_NUMERO macro 
    LOCAL INICIO, FIN
    POP DX  
    MOV SI, 9
    INICIO:
        POP AX
        MOV numeros[SI], AL
        DEC SI
        CMP SI, -1
        JE FIN
        JMP INICIO
    FIN:
ENDM

;================ORDENAMIENTO BURBUJA

BUBBLE_SORT MACRO
LOCAL FOR_EXT, FOR_INT, CARRY, FIN

    MOV CX,DX ;Cx is counter for FOR_EXT CX=5    
    DEC CX     ; CX = 4   
    
 FOR_EXT:  
    MOV SI,0         ;    SI is the index of array N   
    MOV BX,CX  ; Dx is counter for FOR_INT   
 FOR_INT:    
    MOV AH,numeros[SI]    ; assign the number numeros[SI] into reg.AH  
    MOV AL,numeros[SI+1]  ; assign the next number numeros[SI+1] into reg.AL   
    CMP AH,AL       ; Compare between numeros[SI] and numeros[SI+1] <BR> 
    JC CARRY        ; if AL > AH => Carry Flag =1 ,THEN jump to carry   
    MOV numeros[SI] , AL  ; else , Do Switching bteween  numeros[SI] and numeros[SI+1]   
    MOV numeros[SI+1] ,AH
    PUSH CX
    CLEAR_SCREEN
    DRAW_BAR numeros
	Sound 7
    POP CX
 CARRY:   
    INC SI   
    DEC BX
    CMP BX, 0   
    JNE FOR_INT   
    DEC CX
    CMP CX, 0
    JNE FOR_EXT 
    JE  FIN
FIN:
ENDM

;================= ORDENAMIENTO BURBUJA DESCENDENTE

BUBBLE_SORT_DESC MACRO
LOCAL FOR_EXT, FOR_INT, CARRY, FIN

    MOV CX,DX ;Cx is counter for FOR_EXT CX=5    
    DEC CX     ; CX = 4   
    
 FOR_EXT:  
    MOV SI,0         ;    SI is the index of array N   
    MOV BX,CX  ; Dx is counter for FOR_INT   
 FOR_INT:    
    MOV AH,numeros[SI]    ; assign the number numeros[SI] into reg.AH  
    MOV AL,numeros[SI+1]  ; assign the next number numeros[SI+1] into reg.AL   
    CMP AH,AL       ; Compare between numeros[SI] and numeros[SI+1] <BR> 
    JNC CARRY        ; if AL > AH => Carry Flag =1 ,THEN jump to carry   
    MOV numeros[SI] , AL  ; else , Do Switching bteween  numeros[SI] and numeros[SI+1]   
    MOV numeros[SI+1] ,AH
    PUSH CX
    CLEAR_SCREEN
    DRAW_BAR numeros
	Sound 10
    POP CX
 CARRY:   
    INC SI   
    DEC BX
    CMP BX, 0   
    JNE FOR_INT   
    DEC CX
    CMP CX, 0
    JNE FOR_EXT 
    JE  FIN
FIN:
ENDM

;================== QUICKSORT



DRAW_BAR macro  valor 
LOCAL INICIO, FIN 
        MOV AX,DX 
		MOV datos[2],dl
		GET_ANCHO
		MOV datos[0],AL;datos0 50 
		MOV AX,0 
		GET_MAYOR numeros
		
        MOV datos[1],AL; datos1 9
		MOV SI,0 
		MOV DI,1
		
        INICIO:
 			MOV dl,datos[2]
 			CMP SI,DX 
			jge FIN
			CMP numeros[SI],'$'
			JE FIN
			MOV dl,numeros[SI]
			MOV AX,0 
			MOV AL, datos[1]

			MOV CX, 0 
			MOV CL, DL
		    MOV AX, 0

		MOV AL,datos[1]
			GET_ALTURA numeros[SI]

			;MOV AX,100
			MOV cx,AX ;cx es ALtura barra 
			xor AX,AX 
			MOV AL,datos[0]
			MOV BX,cx 
			MOV DX,AX 
			PUSH AX 
			MOV AX,DI 
			mul DX 
			MOV DX,AX 
			POP AX 


		    ;BX;ALtura
		    ;AX; ancho 
		    ;DX; poSIcion x 
		    ;CX; color
			GET_COLOR numeros[SI]
			INC DI 
			INC SI 
			INC DI
			PUSH DX 		
			PUSH SI 
			PUSH DI  

			GET_BARRA 

			POP DI 
			POP SI 
			POP DX 

            MOV AX,DX
            MOV DX,8
            DIv dl
            MOV DX,AX 

            MOV ah,02h
            MOV bh,0h
            MOV dh,23
            int 10h

		MOV AX, 0 
		MOV AL,numeros[SI-1]

        ;MOV CONTADOR_ITER, di
        ;LOOP_MENSAJE1 numeros[SI], di, 17h    

		MOV DX, 0 
		JMP INICIO

		FIN:
		MOV DX,  0
		POP AX 
		POP BX 
        ;Delay 5

endm 




GET_BARRA macro 
	LOCAL FOR_EXT,ENDF

		add DX,5
	
		PUSH AX 
		PUSH BX
		PUSH DX 

		MOV AX,180
		sub AX,BX

		MOV BX,320
		mul BX 

		POP DX 
		add DX,AX

		POP BX
		POP AX
		PUSH DX 
		PUSH AX 

		mul BX
		MOV BX,AX
		POP AX 
		POP DX 
	
		MOV DI,0
		MOV SI,0
		MOV DI,DX;7099h; DX; pixel iniciAL esquina superior izquierda
		MOV DX,cx ; color 
		MOV cx, BX;1388h;BX ; area de la barra en pixeles 
		;MOV BX,SI 
 
		FOR_EXT:
			MOV [DI],DX 
			INC DI 
			INC SI 
			CMP SI,AX;50;AX; 50 ancho de la barra
			jne ENDF
			add DI,320
			sub DI,AX;50;AX
			xor SI,SI 
		ENDF:
		loop FOR_EXT

	endm 
GET_ALTURA macro numeroo
    MOV CX, 0
    MOV cl, numeroo
    MOV BX,AX 
    MOV AX,170
    mul cx 
    DIv BX 
ENDM





GET_COLOR MACRO valor
LOCAL DRAW_RED,DRAW_BLUE,DRAW_YELLOW,DRAW_GREEN,DRAW_WHITE,FIN
    CMP valor,20
    JLE DRAW_RED 
    CMP valor,40
    JLE DRAW_BLUE
    CMP valor,60
    JLE DRAW_YELLOW
    CMP valor,80
    JLE DRAW_GREEN
    CMP valor,100
    JLE DRAW_WHITE
    DRAW_RED:
        MOV CX,12
        JMP FIN 
    DRAW_BLUE:
        MOV CX,9
        JMP FIN 
    DRAW_YELLOW:
        MOV CX,14
        JMP FIN 
    DRAW_GREEN:
        MOV CX,10
        JMP FIN 
    DRAW_WHITE:
        MOV CX,15
    FIN:
endm


GET_ANCHO macro 
    MOV BX,2
    MUL BX 
    MOV BX,AX 
    MOV AX,310
    DIV BX  
endm


GET_MAYOR macro buffer 
	local INICIO,AVANZAR,FIN 
		MOV DX, 0 
		mov dl,buffer[0]
		MOV DI, 1 

		INICIO:
			cmp di,SIZEOF buffer
			je FIN 
			cmp buffer[di],'$'
			je FIN 
			cmp buffer[di],dl
			jg AVANZAR
			inc di 
			jmp INICIO
		AVANZAR:
			mov dl,buffer[di]
			inc di 
			jmp  INICIO
		FIN:
			mov ax,dx
	endm

    
Sound macro hz
	mov al, 86h
	out 43h, al
	mov ax, (1193180 / 1200) ;numero de hz
	out 42h, al
	mov al, ah
	out 42h, al 
	in al, 61h
	or al, 00000011b
	out 61h, al

	delay hz;mando a ejecutar el delay para que se escuche el sonido por varios segundos
	 ; apagar la bocina
	in al, 61h
	and al, 11111100b
	out 61h, al
endm


Delay macro const
LOCAL D1, D2, FIN, delay, delay2
mov bp, const
mov si, const
delay2:
dec bp
nop
jnz delay2
dec si
cmp si,0    
jnz delay2

endm




CLEAR_SCREEN MACRO 
local LOOP_FOR,REPETIR
    ORDENAR_TOPPUNTOS
ENDM



LOOP_MENSAJE1 MACRO caracter, columna, linea
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


CANT_ELEMENTOS MACRO buffer
LOCAL INICIO, FIN
    MOV DI, 0
    MOV SI, 0
        
    INICIO:
        CMP buffer[DI], '$'
        JE FIN
        INC SI
        INC DI
        JMP INICIO
    FIN:
        MOV AX, SI    

ENDM



DRAW_BORDE_BARRA MACRO 
LOCAL INICIO, FIN
local SUPERIOR, INFERIOR, IZQUIERDO, DERECHO, REPETIR, REPETIR_INFERIOR, REPETIR_IZQUIERDO, REPETIR_DERECHO, STOP
	;MARGEN SUPERIOR
    LOOP_BORDE 1610
	; MARGEN INFERIOR
    LOOP_BORDE 58570
	
	
    LOOP_MARGEN 1610, 5Ah

    LOOP_MARGEN 1915, 5Ah
	
    STOP:


endm

LOOP_BORDE MACRO pixel
LOCAL SUPERIOR, REPETIR
    ;MARGEN SUPERIOR	
	MOV DI, pixel ;pixel de inicio = esquina superior izquierda
	MOV DX, 0Fh ; color 
	MOV CX, 131h
	
		SUPERIOR:
			MOV [DI],dx 
			INC DI 	
		REPETIR:
		loop SUPERIOR
ENDM

LOOP_MARGEN MACRO pixel, tope
LOCAL IZQUIERDO, REPETIR_IZQUIERDO
	MOV DI, pixel ;pixel de inicio = esquina superior izquierda
	MOV DX, 0Fh ; color 
	MOV CX, tope
	
		IZQUIERDO:
			MOV [DI],dx 
			ADD DI, 640 	
		REPETIR_IZQUIERDO:
		loop IZQUIERDO
ENDM