UrHojre
    CALL TIMEOUT50
    BTFSS   hojre
	GOTO MainUr
    ; Undgå langsomme taster
    BTFSC   ButtonClicked
	GOTO	MainUr
    BSF	    ButtonClicked
    
    BTFSC  IsHour
	GOTO UrSetMin
	
    BTFSC   IsMin
	GOTO UrSetSec
    
    BTFSC   IsSec
	GOTO UrSetHour
	
    BCF	    IsSec
    BCF	    IsMin
    BSF	    IsHour
    GOTO MainUr
    
    
UrVenstre
    CALL TIMEOUT50
    BTFSS   venstre
	GOTO MainUr
    ; Undgå langsomme taster
    BTFSC   ButtonClicked
	GOTO	MainUr
    BSF	    ButtonClicked
    
    BTFSC  IsHour
	GOTO UrSetSec
	
    BTFSC   IsMin
	GOTO UrSetHour
    
    BTFSC   IsSec
	GOTO UrSetMin
	
    BCF	    IsSec
    BCF	    IsMin
    BSF	    IsHour
    GOTO MainUr
    
UrOp
    CALL TIMEOUT50
    BTFSS   op
	GOTO MainUr
    ; Undgå langsomme taster
    BTFSC   ButtonClicked
	GOTO	MainUr
    BSF	    ButtonClicked
    
    BTFSC   IsHour
	CALL IncrementHour
	
    BTFSC   IsMin
	CALL IncrementMin
	
    BTFSC   IsSec
	CALL IncrementSec
    BSF	    Second
    GOTO MainUr
    
UrNed
    CALL TIMEOUT50
    BTFSS   ned
	GOTO MainUr
    ; Undgå langsomme taster
    BTFSC   ButtonClicked
	GOTO	MainUr
    BSF	    ButtonClicked
    
    BTFSC   IsHour
	CALL DecrementHour
	
    BTFSC   IsMin
	CALL DecrementMin
	
    BTFSC   IsSec
	CALL DecrementSec
    BSF	    Second
    GOTO MainUr
    
UrSetHour
    BSF	IsHour
    BCF	IsMin
    BCF	IsSec
    GOTO MainUr
    
UrSetMin
    BCF	IsHour
    BSF	IsMin
    BCF	IsSec
    GOTO MainUr
    
UrSetSec
    BCF	IsHour
    BCF	IsMin
    BSF	IsSec
    GOTO MainUr