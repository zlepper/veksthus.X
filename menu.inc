SkiftTilHojre
	; Vent et øjeblik for at undgå prel
    CALL TIMEOUT50
    BTFSS   hojre
	GOTO MAIN
	; Undgå at menuen skifter hvis man holder knappen i bund hele tiden
    BTFSC   ButtonClicked
	GOTO MAIN
    BSF	ButtonClicked
    
    ; Tjek om vi er på menupunkt 1.
    ; Hvis vi er skal vi rykke til punkt 2
    MOVLW   D'1'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
	GOTO SkiftTilTemperatur
	
	; Og så fremdeles for andre menupunkter
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
    ; Hvis vi er færdige skal vi bare tilbage og tjekke knapper
    GOTO MAIN
    
SkiftTilVenstre
; Samme logik som SkiftTilHøjre, men modsat
;    CALL TIMEOUT50
;    BTFSS   venstre
;	GOTO MAIN
;    BTFSC   ButtonClicked
;	GOTO MAIN
;    BSF	ButtonClicked
;    
;    ; Tjek om vi er på menupunkt 1.
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
;    ; Hvis vi er færdige skal vi bare tilbage og tjekke knapper
    GOTO MAIN
    
ValgNuverende
    ; Tjek om vi er på sæt ur valget
;    MOVLW   D'3'    
;    SUBWF   MenuPunkt,W
;    BTFSC   STATUS,Z
;	GOTO GotoUr

	; Tjek om vi er på fugtighedsmenuen, og vælg den hvis vi er
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
    
; Udskriver uret på displayet
SkiftTilUr
    MOVLW   D'1'
    MOVWF   MenuPunkt
    CALL display
    GOTO MAIN
    
SkiftTilTemperatur
    ; Skriv "temperatur" på lcd display
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL    LCD_Reg
    LCDstr temperatur
    
    MOVLW   D'2'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
SkiftTilSetUr
    ; Skriv "Sæt ur" på lcd display
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL LCD_Reg
    LCDstr  setur
    
    MOVLW   D'3'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
SkiftTilFugt
    ; Skriv "Fugtighed" på lcd dispaly
    MOVLW   LCDCLR
    CALL    LCD_Reg
    MOVLW   LCDline1
    CALL    LCD_Reg
    LCDstr  fugtighed
    
    MOVLW   D'4'
    MOVWF   MenuPunkt
    GOTO    MAIN
    
    
    
