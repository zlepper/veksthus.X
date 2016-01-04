;org 0x800
#include "urnav.inc" ; Load navigationen i uret

MainUr
    BTFSC   hojre
	GOTO UrHojre
	
    BTFSC   venstre
	GOTO UrVenstre
    
    BTFSC   op
	GOTO UrOp
	
    BTFSC   ned
	GOTO UrNed
    
    BTFSC   tilbage
	GOTO GotoSkiftTilUr
	
    BCF	    ButtonClicked
    BCF	    ShouldSkipSelector
    BTFSC	Second
	CALL UdskrivValgtTid
	
    
    GOTO MainUr
    
GotoSkiftTilUr
;    BCF	    PCLATH,3
    GOTO    SkiftTilUr
    
UdskrivValgtTid
    ; Tjek om vi har lige har skjult. Hvis vi har, skal vi vise igen
    MOVLW	B'00001000'
    XORWF	UrSelector,F
    
    BCF		ShouldSkipSelector
    MOVLW	LCDCLR
    CALL   	LCD_Reg
    MOVLW	LCDLine2+1			;\  flyt til position 1 på
    CALL   	LCD_Reg			;/ linie 2 på LCD-displayet

    BTFSC	IsHour
	CALL	ShouldSkipCurrent
    BTFSC	ShouldSkipSelector
	GOTO	SpaceHour

    MOVF	CHour,W			;hent antal timer ind i W-reg
    CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
    MOVF	CIF10,W			;hent 10'erne (CIF10)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data   		;og udskriv det på LCD-displayet
    MOVF	CIF1,W			;hent 1'erne (CIF1)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data   		;og udskriv det på LCD-displayet

UDSKRIVMIN
    MOVLW	':'			;\ Udskriv kolon
    CALL   	LCD_Data   		;/

    BCF ShouldSkipSelector
    BTFSC	IsMin
	CALL	ShouldSkipCurrent
    BTFSC   ShouldSkipSelector
	GOTO SpaceMin
    ; Udskriv minutter
    MOVF	CMin,W			;hent antal minutter ind i W-reg
    CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
    MOVF	CIF10,W			;hent 10'erne (CIF10)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data   		;og udskriv det på LCD-displayet
    MOVF	CIF1,W			;hent 1'erne (CIF1)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data   		;og udskriv det på LCD-displayet

UDSKRIVSEC
    MOVLW	':'			;\ Udskriv kolon
    CALL   	LCD_Data 		;/

    BCF		ShouldSkipSelector
    BTFSC	IsSec
	CALL	ShouldSkipCurrent
    BTFSC   ShouldSkipSelector
	GOTO SpaceSec
	
    ; Udskriv sekunder
    MOVF	CSec,W			;hent antal sekunder ind i W-reg
    CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
    MOVF	CIF10,W			;hent 10'erne (CIF10)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data  		;og udskriv det på LCD-displayet
    MOVF	CIF1,W			;hent 1'erne (CIF1)
    CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
    CALL   	LCD_Data   		;og udskriv det på LCD-displayet
    BCF		Second
    RETURN					; UDSKRIFT AF TID

ShouldSkipCurrent
    BCF	    ShouldSkipSelector
    BTFSC   IsSecond
	BSF ShouldSkipSelector
    RETURN
    
SpaceHour
    CALL DoubleSpace
    GOTO    UDSKRIVMIN
SpaceMin
    CALL DoubleSpace
    GOTO    UDSKRIVSEC
SpaceSec
    CALL DoubleSpace
    BCF		Second
    RETURN
DoubleSpace
    MOVLW   ' '
    CALL LCD_Data
    MOVLW   ' '
    CALL LCD_Data
    RETURN
    
IncrementHour
    INCF    CHour,F
    MOVLW   D'24'
    SUBWF   CHour,W
    BTFSC   STATUS,C
	MOVWF	CHour
    RETURN
    
IncrementMin
    INCF    CMin,F
    MOVLW   D'60'
    SUBWF   CMin,W
    BTFSC   STATUS,C
	MOVWF	CMin
    BTFSC   STATUS,C
	CALL IncrementHour
    RETURN
    
IncrementSec
    INCF    CSec,F
    MOVLW   D'60'
    SUBWF   CSec,W
    BTFSC   STATUS,C
	MOVWF	CSec
    BTFSC   STATUS,C
	CALL IncrementMin
    RETURN
    
DecrementHour
    BCF	    STATUS,C
    MOVLW   D'0'
    SUBWF   CHour,W	    ; Tjek om vi er på nul
    BTFSC   STATUS,Z
	MOVLW	D'24'	    ; Vi er på nul
    MOVWF   CHour
    DECF    CHour	    ; Gå en time ned
    RETURN
   
DecrementMin
    BCF	    STATUS,C
    MOVLW   D'0'
    SUBWF   CMin,W	    ; Tjek om vi er på nul
    BTFSC   STATUS,Z
	MOVLW	D'60'	    ; Vi er på nul
    MOVWF   CMin
    DECF    CMin	    ; Gå en time ned
    RETURN
    
DecrementSec
    BCF	    STATUS,C
    MOVLW   D'0'
    SUBWF   CSec,W	    ; Tjek om vi er på nul
    BTFSC   STATUS,Z
	MOVLW	D'60'	    ; Vi er på nul
    MOVWF   CSec
    DECF    CSec	    ; Gå en time ned
    RETURN