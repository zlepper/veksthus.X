Delay1 equ 0xFF
Delay2 equ 0xFE
Delay3 equ 0xFD

TIMEOUT250 ; Timeout funktion
			; ********  Start på tidsspild rutine
			MOVLW	D'25'				; Tidsforsinkelse på ca. 250 ms
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
; ********  Slut på tidsspild rutine
			RETURN
			
TIMEOUT50 ; Timeout funktion
			; ********  Start på tidsspild rutine
			MOVLW	D'5'				; Tidsforsinkelse på ca. 50 ms
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
; ********  Slut på tidsspild rutine
			RETURN
			

; Tidsforsinkelse på 1 sekund
TIMEOUT1
    MOVWF   TimeoutHusk
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    CALL    TIMEOUT250
    MOVFW   TimeoutHusk
    RETURN