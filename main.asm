;**** FIL OPLYSNINGER ******************************************************************
;	Fil:		Væksthus
;   Dato:		11 december 2015
;	forfatter:	Rasmus Hansen & Mathias Madsen
; ****** BESKRIVELSE **********************************************************************
;	Afhængig af hvilken tast der er blevet trykket på går vi til en bestemt side
;	Her kan vi så udskrive forskellige ting, fx "temperatur", "Vindhastighed" og "Nedbørsmængde"
; ******* PROCESSOR DEFINITIONER **********************************************************
    processor	16f877a					;Sets processor
    #include 	p16f877a.inc
    errorlevel -302		
;   Set configuration bits using definitions from the include file, p16f877A.inc
    __config	_HS_OSC & _PWRTE_OFF & _WDT_OFF & _CP_OFF & _CPD_OFF & _LVP_OFF
; ******* DEFFINITION AF VARIABLE *********************************************************
#include	"SDUboard.var"			
;VARME1		EQU		B'00000111'
;VARME2		EQU		B'00000110'
;VARME3		EQU		B'00000100'
;KULDE		EQU		B'00001000'
counter		EQU		0X20
sec			EQU		0X21
min			EQU		0X22
hour		EQU		0X23
ADC			EQU		0X24
FLAG		EQU		0X25
#define		Second		FLAG,0
#define		ButtonClicked	FLAG,1
#define		ReturnWhenDone	FLAG,2
#define		Sand		FLAG,3
#define		SkippingRead	FLAG,4
#define		SkippingReadTemp    FLAG,5
MenuPunkt	EQU		0x26
Wtemp		EQU		0x27
Stemp		EQU		0x28
CHour		EQU		0x29
CMin		EQU		0x2A
CSec		EQU		0x2B
UrSelector	EQU		0x2C
#define		IsHour		UrSelector,0
#define		IsMin		UrSelector,1
#define		IsSec		UrSelector,2	
#define		IsSecond	UrSelector,3
#define		ShouldSkipSelector  UrSelector,4
Fugt		EQU		0x2D
TEMP		EQU		0x2E
Math		EQU		0x2F
DivCounter	EQU		0x30
TimeoutHusk	EQU		0x31
TEMP2		EQU		0x32
Temp		EQU		0x33
; ******* OPSÆTNING AF PROGRAM POINTERE ***************************************************
    org		0x0000			
    GOTO	INIT			
    org		0x0004		
    GOTO 	ISR
; ******* INCLUDEREDE FILER ***************************************************************
#Include 	"SDUboard.lib"	
#Include	"disp.inc"
#Include	"delay.inc"
; ******* Deffinition af porte ************************************************************
#define 	SWITCH  PORTB
#define		hojre		SWITCH,0
#define		venstre		SWITCH,1
#define		valg		SWITCH,2
#define		tilbage		SWITCH,3
#define		op			SWITCH,4
#define		ned			SWITCH,5
#define 	LED			PORTC
#define		vander		TEMP2,4
#define		lys			TEMP2,5
#define		inputSwitch	TEMP2,7
#define		blower		TEMP2,6
; ******* OPSÆTNING AF STRENGE TIL UDSKRIVNING ********************************************
    ORG 	0X600
temperatur	string "TEMPERATUR"
setur		string "SÆT UR"
fugtighed	string "FUGTIGHED"
    ; ******* Inkluder de andre projektfiler
#include	"math.inc"
#include	"menu.inc"
#include	"fugt.inc" 
#include	"check.inc"
;#include	"temp.inc"
;#include	"ur.inc"
; ******* INITIALISERING AF CONTROLER *****************************************************
INIT		CALL   	LCD_Init		; Initialiser LCD og indsæt DK-bogstaver (æøå)	
    CALL	LED_init		; Initialiser lysdionerne
    CLRF	LED
    CALL	InitPortA
    CALL   	AD_init			; initialiser og aktiver A/D-converteren
		; Opsætning og start timer 2
    BSF		STATUS,5		; Skift til Bank 1
    MOVLW	D'195'   		; Sæt Period registeret 
    MOVWF	PR2				;
    BCF		STATUS,5		; Skift til Bank 0
    MOVLW	B'01111111'   	; Indstil post- og pre-scaler 
    MOVWF	T2CON			; og start timer 2	
    BCF		PIR1,1			; Clear timer 2 flag		
		; Enable timer interrupt.
    BSF		STATUS,5		; Skift til Bank 1
    BSF		PIE1,1			; Enable timer 2 interrrupt.
    BCF		STATUS,5		; Skift til Bank 0
    BSF		INTCON,6		; Enable timer 2 interrupt.
    BSF		INTCON,7		; Enable Global interrupt.	
    clrf	FLAG			; Undgå at mærkelige flag er blevet sat
    MOVLW	D'1'
		; Sæt default værdier
    BSF	    ReturnWhenDone	; \	
    CALL    MainFugt		;	Initialiser fugtighedsmåleren
    BCF	    ReturnWhenDone	; /
    BSF	    vander			; Sluk for vandingssystemet
    clrf    hour			; Nulstil timetælleren
    clrf    min				; Nulstil minuttælleren
    clrf    sec				; Nulstil sekund tæleren
    MOVLW   D'12'			; 	Sæt timetælleren til 12 timer
    MOVWF   CHour			; /
    BSF	    TEMP2,2			; \
    BCF	    TEMP2,3			; 	Forsøg at undgå ionisering af fugtighedsmåleren
    
    BSF	IsHour				; Sørg for at time viseren blinker i ur instillingerne
    GOTO SkiftTilUr			; Begynd at vise uret

; ******* CHECK AF HVILKE STAGES DER SKAL KØRES **************************************
MAIN
    CALL DoAllChecks		; Udfør alle tjeks, fx fugtighed og tid.
    BTFSC   hojre 			; Tjek om vi skal navigere til højre i menuen
    GOTO    SkiftTilHojre	; Naviger til højre
    
    BTFSC   venstre			; Tjek om vi skal navigere til venstre i menuen
    GOTO	SkiftTilVenstre	; Naviger til venstre (Slået fra)
    
    BTFSC   valg			; Tjek om vi skal vælge den nuværende menu
    GOTO	ValgNuverende	; Vælg den nuværende menu

    ; Hvis ingen knapper har været trykket skal uret bare udskrives igen
    ; Dette sker kun hvis vi er på menupunkt 1
    BCF	    ButtonClicked
    MOVLW   D'1'
    SUBWF   MenuPunkt,W
    BTFSC   STATUS,Z
    GOTO	FLAGChecker
    GOTO MAIN
    
FLAGChecker
	; Tjek om der er gået et sekund siden vi sidst opdaterede uret
    BTFSS	FLAG,0			
    GOTO	MAIN
    BCF		FLAG,0
    GOTO	SkiftTilUr	; Hvis uret igen
; ******* Interupt service rutine --- Holder styr på uret --- Kaldes hvert 20ms ************
ISR			
    Movwf	Wtemp			; Backup af værdien i W arbejds registeret
    MOVF	STATUS,W
    MOVWF	Stemp 			; Backup af værdien i status registeret 
    BCF		STATUS,RP0		; Sørg for at være i den rigtige bank under ISR
		; opdatering af ur millisekunder 
    INCF	counter			;tæl counter op med 1
    MOVLW	D'50'			;\ 
    SUBWF	counter,W		;  undersøg om counteren er nået op på 50
;    MOVWF	LED
    BTFSS	STATUS,Z		;/ 
    GOTO	exitISR			;hvis nej: så slut ISR her...
		; opdatering af ur sekunder 
    CLRF	counter			;hvis ja: så nulstil counter
    BSF		FLAG,0
;   GOTO MINUTERRRRR
    INCF	sec				;tæl sekunder en op
    MOVLW	D'60'			;\
    SUBWF	sec,W			;  undersøg om sekunder er lig med 60
    BTFSS	STATUS,Z		;/
    GOTO	exitISR				;hvis nej: så udskriv tiden...
		; opdatering af ur Minutter 
    CLRF	sec				;hvis ja: så nulstil sekunder
;MINUTERRRRR    
    INCF	min				;og tæl minutter op med en
    MOVLW	D'60'			;\
    SUBWF	min,W			;  undersøg om minutter er lig med 60
    BTFSS	STATUS,Z		;/
    GOTO	exitISR				;hvis nej: så udskriv tiden...
		; opdatering af ur Timer
    CLRF	min				;hvis ja: så nulstil minutter
    INCF	hour			;og tæl timer op med en
    MOVLW	D'24'			;\
    SUBWF	hour,W			;  undersøg om timer er lig med 24
    BTFSS	STATUS,Z		;/
    GOTO	exitISR			;hvis nej: så udskriv tiden...
		; opdatering af ur 24 timer
    CLRF	hour			;hvis ja: så nulstil timer og udskriv tiden...
exitISR		MOVF	Stemp,W			; Re-store af W
    MOVWF	STATUS			; Re-store af status 
    MOVF	Wtemp,W			
    BCF		PIR1,1			; Clear timer 2 flag
    RETFIE
; ******* UDSKRIFT PROCEDURE *****************************************************
UDSKRIV		
    MOVWF	TEMP			; Gem W
    MOVLW	LCDline1+1		; Skift til første linje på LCD
    CALL	LCD_Reg			; /
    MOVFW	TEMP			; Load W
    CALL	BIN2DEC			; Lav W om til decimaltal
    MOVF	CIF100,W		; \
    CALL 	CONV2ASCII		;  Lav hundrede om til ASCII og udskriv
    CALL 	LCD_Data		; /
    MOVF	CIF10,W			; \
    CALL	CONV2ASCII		;	Lav tiere om til ASCII og udskriv
    CALL	LCD_Data		; /
    MOVF	CIF1,W			; \ 
    CALL	CONV2ASCII		;	Lav enere om til ASCII og udskriv
    CALL	LCD_Data		; /
    RETURN

InitPortA
	; Sørg for at fugtighedsmåleren ikke ioniserer
    BCF		TEMP2,2
    BSF		TEMP2,3
    RETURN
    
    END						;her slutter programmet...