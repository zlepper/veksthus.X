SkiftTilHojre
	; Vent et �jeblik for at undg� prel
    CALL TIMEOUT50
    BTFSS   hojre
	GOTO MAIN
	; Undg� at menuen skifter hvis man holder knappen i bund hele tiden
    BTFSC   ButtonClicked
	GOTO MAIN
    BSF	ButtonClicked
    
    ; Tjek om vi er p� menupunkt 1.
    ; Hvis vi er skal vi rykke til punkt 2
    MOVLW   D'1'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilTemperatur
	
	; Og s� fremdeles for andre menupunkter
    MOVLW   D'2'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilSetUr
	
    MOVLW   D'3'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilFugt
	
    MOVLW   D'4'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilTemperatur
    
    MOVLW   D'5'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilUr
    ; Hvis vi er f�rdige skal vi bare tilbage og tjekke knapper
    GOTO MAIN
    
SkiftTilVenstre
; Samme logik som SkiftTilH�jre, men modsat
;    CALL TIMEOUT50
;    BTFSS   venstre
;	GOTO MAIN
;    BTFSC   ButtonClicked
;	GOTO MAIN
;    BSF	ButtonClicked
;    
;    ; Tjek om vi er p� menupunkt 1.
;    ; Hvis vi er skal vi rykke til punkt 2
;    MOVLW   D'1'
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO SkiftTilSetUr
;	
;    MOVLW   D'2'
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO SkiftTilUr
;	
;    MOVLW   D'3'
;	
;    MOVLW   D'4'
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO SkiftTilTemperatur
;    ; Hvis vi er f�rdige skal vi bare tilbage og tjekke knapper
    GOTO MAIN
    
ValgNuverende
    ; Tjek om vi er p� s�t ur valget
;    MOVLW   D'3'    
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO GotoUr

	; Tjek om vi er p� fugtighedsmenuen, og v�lg den hvis vi er
    MOVLW   D'4'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO MainFugt
	
;    MOVLW   D'2'
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO LoopTemp
	
    GOTO MAIN
    
GotoUr
;    BSF	PCLATH,3
 ;   GOTO MainUr
    
; Udskriver uret p� displayet
SkiftTilUr
    MOVLW   D'1'
    MOVWF   MenuPunkt
    CALL display
    GOTO MAIN
    
SkiftTilTemperatur
    ; Skriv "temperatur" p� lcd display
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL    LCD_Reg
    LCDstr temperatur
    
    MOVLW   D'2'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
SkiftTilSetUr
    ; Skriv "S�t ur" p� lcd display
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL LCD_Reg
    LCDstr  setur
    
    MOVLW   D'3'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
SkiftTilFugt
    ; Skriv "Fugtighed" p� lcd dispaly
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL    LCD_Reg
    LCDstr  fugtighed
    
    MOVLW   D'4'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
    
    
