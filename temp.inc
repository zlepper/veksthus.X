ADReadTemp
    BSF		inputSwitch
    MOVFW	TEMP2
    MOVWF	LED
    CALL	TIMEOUT50
    BTFSC	SkippingReadTemp
	GOTO	SkipADReadTemp
    CALL	AD_Read
    BSF		STATUS,RP0
    MOVF	ADRESL,W
    BCF		STATUS,RP0
    MOVWF	Temp
    BSF		SkippingReadTemp
    RETURN
    
LoopTemp
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    BTFSC   tilbage
	GOTO    TempTilbage
    MOVLW   LCDCLR
    CALL    LCD_Reg
    CALL    ADReadTemp
    MOVFW   Temp
    CALL    UDSKRIV
    GOTO    LoopTemp
    
TempTilbage
    CALL    TIMEOUT50
    BTFSC   tilbage
	GOTO SkiftTilUr
    GOTO LoopTemp
    
SkipADReadTemp
    BCF	    SkippingReadTemp
    RETURN
    
TurnOffCooler
    BCF	    blower
    MOVFW   TEMP2
    MOVWF   LED
    RETURN
    
TurnOnCooler
    BSF	    blower
    MOVFW   TEMP2
    MOVWF   LED
    RETURN