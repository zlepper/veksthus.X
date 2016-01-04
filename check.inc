DoAllChecks
    ; Tjek om vi er nået det valgte tidspunkt
    MOVFW   CHour
    SUBWF   hour,W
    BTFSC STATUS,Z
	CALL TimeCheck2
	
    MOVLW   D'0'
    SUBWF   hour,W
    BTFSC STATUS,Z
	CALL NulTimeCheck2
    ; Tjek om der er en spænding på over 100
    ; Hvis der er, skal vi tænde for vandingen
	; Hvis ikke skal vi slukke for vandingen
    CALL    ADReadFugt		
    MOVLW   D'100'		
    SUBWF   Fugt,W		
    BTFSS   STATUS,C
	BSF lys
    BTFSC   STATUS,C
	BCF lys
    MOVFW   TEMP2
    MOVWF   LED

    ; Tjek om der er en spædning på under 64
;    ; Hvis der er skal vi slukke for vandingen
;    MOVLW   D'64'
;    SUBWF   Fugt,W
;    BTFSC   STATUS,C
;	BCF lys
    
    ; Tjek temperatur
;    CALL ADReadTemp
;    MOVLW   D'60'
;    SUBWF   Temp,W
;    BTFSC   STATUS,C
;	CALL TurnOnCooler
;	
;    MOVLW   D'50'
;    SUBWF   Temp,W
;    BTFSC   STATUS,C
;	CALL TurnOffCooler
;    
    
    
    RETURN
    
; Del 2 af tidstjek
TimeCheck2
    MOVWF   CMin
    SUBWF   min,W
    BTFSC   STATUS,Z
	CALL TimeCheck3
    RETURN
    
; Del 3 af tidstjek
TimeCheck3
    MOVWF   CSec
    SUBWF   sec,W
    BTFSC   STATUS,Z
	CALL TurnOffTheLight
    RETURN

; Sluk for lyset
TurnOffTheLight
    BCF	    vander		
    MOVFW   TEMP2
    MOVWF   LED
    RETURN
    
; Del 2 af tjek om tiden er 00:00:00
NulTimeCheck2
    MOVLW   D'0'
    SUBWF   min,W
    BTFSC   STATUS,Z
	CALL NulTimeCheck3
    RETURN
    
; Del 3 af tjek om tiden er 00:00:00
NulTimeCheck3
    MOVLW   D'0'
    SUBWF   sec,W
    BTFSC   STATUS,Z
	CALL TurnOnTheLight
    RETURN
    
; Tænd for lyset
TurnOnTheLight
    BSF	    vander
    MOVFW   TEMP2
    MOVWF   LED
    RETURN
    