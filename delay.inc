Delay1 equ 0xFF
Delay2 equ 0xFE
Delay3 equ 0xFD

TIMEOUT250 ; Timeout funktion
			; ********  Start p� tidsspild rutine
			MOVLW	D'25'				; Tidsforsinkelse p� ca. 250 ms
			MOVWF	Delay3				;
Loop12		MOVLW	h'73'				;
			MOVWF	Delay1				;
			MOVLW	h'DF'				;
			MOVWF	Delay2				;
Loop1		INCFSZ	Delay1,F			;
			GOTO	Loop1				;
			MOVLW	h'73'				;
			MOVWF	Delay1				;
			INCFSZ	Delay2,F			;
			GOTO	Loop1				;
			DECFSZ	Delay3,F			;
			GOTO	Loop12				;
; ********  Slut p� tidsspild rutine
			RETURN
			
TIMEOUT50 ; Timeout funktion
			; ********  Start p� tidsspild rutine
			MOVLW	D'5'				; Tidsforsinkelse p� ca. 50 ms
			MOVWF	Delay3				;
Loop32			MOVLW	h'73'				;
			MOVWF	Delay1				;
			MOVLW	h'DF'				;
			MOVWF	Delay2				;
Loop3			INCFSZ	Delay1,F			;
			GOTO	Loop1				;
			MOVLW	h'73'				;
			MOVWF	Delay1				;
			INCFSZ	Delay2,F			;
			GOTO	Loop32				;
			DECFSZ	Delay3,F			;
			GOTO	Loop3				;
; ********  Slut p� tidsspild rutine
			RETURN
			

; Tidsforsinkelse p� 1 sekund
TIMEOUT1
    MOVWF   TimeoutHusk
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    MOVFW   TimeoutHusk
    RETURN