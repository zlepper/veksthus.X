; Initialiser fugt, gør ikke så meget, men er her af legacy grunde. 
MainFugt
    BTFSC   ReturnWhenDone
	RETURN
    
LoopFugt
	; Vent 0.5 sekund inden vi kører videre
    CALL TIMEOUT250			
    CALL TIMEOUT250
	; Tjek om tilbage knappen er klikket, og gå tilbage hvis den er. 
    BTFSC   tilbage
	GOTO    FugtTilbage
	; Ryd displayed
    MOVLW   LCDCLR
    CALL    LCD_Reg
	; Læs fugtigheden
    CALL    ADReadFugt
    MOVFW   Fugt
	; Udskriv fugtigheden
    CALL    UDSKRIV
    GOTO    LoopFugt
	
FugtTilbage
	; Gå tilbage til hovedmenuen hvis tilbage knappen er klikket
    CALL TIMEOUT50
    BTFSC   tilbage
	GOTO SkiftTilUr
	; Ellers bare fortsæt med at udskriv fugtigheden
    GOTO LoopFugt
    
ADReadFugt
	; Sikrer at vi læser ind fra fugtighedsmåleren
    BCF		inputSwitch
    MOVFW	TEMP2
    MOVWF	LED
	; Skift retning på spændingsdeleren for at undgå ionisering
    MOVLW	B'00001100'
    XORWF	TEMP2,F
    MOVFW	TEMP2
    MOVWF	LED
	; Vent et øjeblik med at lære ind
    CALL	TIMEOUT50
	; Tjek om vi skal skippe i den her omgang. Det skal vi hver anden omgang
	; For at undgå modsatte resultater
    BTFSC	SkippingRead
	GOTO 	SkipADReadFugt
	; Indlæs fugtigheden
    CALL	AD_Read
	; Fugtigheden skal læses fra bank 1
    BSF		STATUS,RP0
    MOVF	ADRESL,W
    BCF		STATUS,RP0
	; Gem fugtigheden til fremtidig reference
    MOVWF	Fugt
	; Husk at vi skal skippe læsning næste gang
    BSF		SkippingRead
    RETURN
    
SkipADReadFugt
	; Husk at vi skal læse næste gang
    BCF	    SkippingRead
    RETURN
    
    
GivVand
	; Start vandingssystemet
    BSF	    vander
    RETURN
    
StopVand
	; Stop vandingsystemet
    BCF	    vander 
    RETURN