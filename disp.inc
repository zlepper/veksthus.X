; ******* Display rutine --- Udskriver tiden --- Køres hvert sekund --- Indenfor ISR *******

display
			MOVLW	LCDCLR
			CALL   	LCD_Reg
			MOVLW	LCDLine2+1		;\  flyt til position 1 på
			CALL   	LCD_Reg			;/ linie 2 på LCD-displayet

			; Udskriv timer
			MOVF	hour,W			;hent antal timer ind i W-reg
			CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
			MOVF	CIF10,W			;hent 10'erne (CIF10)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data   		;og udskriv det på LCD-displayet
			MOVF	CIF1,W			;hent 1'erne (CIF1)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data   		;og udskriv det på LCD-displayet

			MOVLW	':'				;\ Udskriv kolon
			CALL   	LCD_Data   		;/

			; Udskriv minutter
			MOVF	min,W			;hent antal minutter ind i W-reg
			CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
			MOVF	CIF10,W			;hent 10'erne (CIF10)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data   		;og udskriv det på LCD-displayet
			MOVF	CIF1,W			;hent 1'erne (CIF1)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data   		;og udskriv det på LCD-displayet

			MOVLW	':'				;\ Udskriv kolon
			CALL   	LCD_Data 		;/

			; Udskriv sekunder
			MOVF	sec,W			;hent antal sekunder ind i W-reg
			CALL   	BIN2DEC			;oversæt tal til 100'ere, 10'ere og 1'ere
			MOVF	CIF10,W			;hent 10'erne (CIF10)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data  		;og udskriv det på LCD-displayet
			MOVF	CIF1,W			;hent 1'erne (CIF1)
			CALL   	CONV2ASCII		;oversæt tallet til ASCII-værdi
			CALL   	LCD_Data   		;og udskriv det på LCD-displayet
			

			RETURN					; UDSKRIFT AF TID

