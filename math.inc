IsDivisableBy10
    BCF STATUS,C
    MOVWF   Math
    MOVLW   D'0'
    SUBWF   Math,W
    BTFSC   STATUS,Z
	GOTO IsTrue
    MOVLW   D'10'
    SUBWF   Math,W
    BTFSC   STATUS,Z
	GOTO IsTrue
    BTFSC   STATUS,C
	GOTO IsFalse
    GOTO IsDivisableBy10
    
IsFalse
    BCF	Sand
    RETURN
    
IsTrue
    BSF	Sand
    RETURN