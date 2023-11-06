;begin data segment
DAGS	.BYT 'D'
		.BYT 'A'
		.BYT 'G'
		.BYT 'S'
GADS    .INT #-99
SPACE   .BYT ' '
DASH    .BYT '-'
ENDL    .BYT '\n'
EQL     .BYT '='
rel     .BYT
;end data segment

;begin code segment
;begin pointer initialization
		LDA  R15, DAGS   ;R15 contains pointer to first byte of DAGS
		LDA  R14, GADS   ;R14 contains pointer to first byte of GADS
		ADI  R15, #2     ;Make R15 point to third element of DAGS
		LDB  R0, R15     ;Load third byte of DAGS into R0
		STB  R0, R14     ;Store the third byte of DAGS (in R0) into the first byte of GADS (pointed to by R14)
		
		ADI  R14, #1     ;R14 contains pointer to second byte of GADS
		ADI  R15, #-1    ;Make R15 point to second element of DAGS
		LDB  R0, R15     ;Load second byte of DAGS into R0
		STB  R0, R14     ;Store the second byte of DAGS (in R0) into the second byte of GADS (pointed to by R14)

		ADI  R14, #1     ;R14 contains pointer to third byte of GADS
		ADI  R15, #-1    ;Make R15 point to first element of DAGS
		LDB  R0, R15     ;Load first byte of DAGS into R0
		STB  R0, R14     ;Store the first byte of DAGS (in R0) into the third byte of GADS (pointed to by R14)

		ADI  R14, #1     ;R14 contains pointer to fourth byte of GADS
		ADI  R15, #3     ;Make R15 point to fourth element of DAGS
		LDB  R0, R15     ;Load fourth byte of DAGS into R0
		STB  R0, R14     ;Store the fourth byte of DAGS (in R0) into the fourth byte of GADS (pointed to by R14)
;end pointer initialization

;begin FOR
		MOVI R10, #0     ;R10 is for loop iterator
FOR     MOV  R11, R10
		CMPI R11, #4
		BRZ  R11, ENDFOR ;if R10 iterator is equal to 4 we exit loop
		MOVI R0, #0
		MOVI R1, #0
		MOVI R2, #0
		LDA  R15, DAGS   ;make R15 point to first byte of DAGS again
		ADD  R15, R10    ;make R15 point to the jth byte of DAGS (R10 is j, iterator)
		LDA  R14, GADS   ;make R14 point to the first byte of GADS again
		ADD  R14, R10    ;make R14 point to the jth byte of GADS (R10 is j, iterator)
		LDB  R0, R15     ;load the jth byte of DAGS into R0 from pointer in R15
		MOV  R2, R0
		LDB  R1, R14     ;load the jth byte of GADS into R1 from pointer in R14
		CMP  R2, R1      ;compare the jth byte of DAGS in R0 with the jth byte of GADS in R1 (if R0 is less than R1 R0 will be -1)
		BRZ  R2, ELSE    ;if cmp produced 0 go to else block, jth element of DAGS is equal to jth element of GADS
		BGT  R2, ELSEIF  ;if cmp produced 1 go to else if block, jth element of DAGS is greater than jth element of GADS
		
		MOVI R2, '<'     ;load character into R2
		STB  R2, rel     ;store the character loaded into R2 into global rel
		JMP  ENDIF       ;jump to end of if statement

ELSEIF  MOVI R2, '>'     ;load character into R2
		STB  R2, rel     ;store the character loaded into R2 into global rel
		JMP  ENDIF       ;jump to end of if statement

ELSE    MOVI R2, '='     ;load character into R2
		STB  R2, rel     ;store the character loaded into R2 into global rel

ENDIF	MOV  R3, R0      ;move/copy the jth element of DAGS (contained in R0) into R3
		TRP  #3          ;print jth element of DAGS
		LDB  R3, SPACE
		TRP  #3
		LDB  R3, rel     ;load character from global rel
		TRP  #3          ;print
		LDB  R3, SPACE
		TRP  #3
		MOV  R3, R1      ;move/copy the jth element of GADS (contained in R1) into R3
		TRP  #3
		LDB  R3, SPACE
		TRP  #3
		LDB  R3, DASH
		TRP  #3
		TRP  #3
		LDB  R3, SPACE
		TRP  #3
		ADI  R10, #1     ;increment the iterator in R10
		JMP  FOR

;end FOR
ENDFOR  LDB  R3, ENDL
		TRP  #3
		TRP  #3
		LDA  R15, DAGS
		LDR  R0, R15
		MOV  R1, R0
		LDA  R14, GADS
		LDR  R2, R14
		SUB  R1, R2
		MOV  R3, R0
		TRP  #1
		LDB  R3, SPACE
		TRP  #3
		LDB  R3, DASH
		TRP  #3
		LDB  R3, SPACE
		TRP  #3
		MOV  R3, R2
		TRP  #1
		LDB  R3, SPACE
		TRP  #3
		LDB  R3, EQL
		TRP  #3
		LDB  R3, SPACE
		TRP  #3
		MOV  R3, R1
		TRP  #1
		LDB  R3, ENDL
		TRP  #3
		TRP #0
;end code segment