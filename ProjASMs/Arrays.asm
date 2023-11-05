;Data segment begin
SIZE	.INT #10
ARR		.INT #10
		.INT #2
		.INT #3
		.INT #4
		.INT #15
		.INT #-6
		.INT #7
		.INT #8
		.INT #9
		.INT #10
ITR		.INT #0
SUM		.INT #0
TEMP	.INT
RESULT  .INT
SPACE   .BYT ' '
i		.BYT 'i'
s		.BYT 's'
e		.BYT 'e'
v		.BYT 'v'
n		.BYT 'n'
o		.BYT 'o'
d		.BYT 'd'
ENDL	.BYT '\n'
S		.BYT 'S'
u		.BYT 'u'
m		.BYT 'm'
;data segment end

;code segment begin
		 LDR  R13, SIZE
WHILE	 LDR  R15, ITR
		 LDA  R14, ARR
		 MOV  R10, R15
		 CMP  R15, R13
		 BRZ  R15, ENDWHILE
		 LDR  R0, SUM
		 MULI R10, #4
		 ADD  R14, R10
		 LDR  R1, R14
		 ADD  R0, R1
		 STR  R0, SUM
		 MOV  R2, R1
		 DIVI R2, #2
		 MULI R2, #2
		 CMP  R2, R1
		 BNZ  R2, ELSE
IF		 MOV  R3, R1
		 TRP  #1
		 LDB  R3, SPACE
		 TRP  #3
		 LDB  R3, i
		 TRP  #3
		 LDB  R3, s
		 TRP  #3
		 LDB  R3, SPACE
		 TRP  #3
		 LDB  R3, e
		 TRP  #3
		 LDB  R3, v
		 TRP  #3
		 LDB  R3, e
		 TRP  #3
		 LDB  R3, n
		 TRP  #3
		 LDB  R3, ENDL
		 TRP  #3
		 JMP  ENDIF
ELSE     MOV  R3, R1
		 TRP  #1
		 LDB  R3, SPACE
		 TRP  #3
		 LDB  R3, i
		 TRP  #3
		 LDB  R3, s
		 TRP  #3
		 LDB  R3, SPACE
		 TRP  #3
		 LDB  R3, o
		 TRP  #3
		 LDB  R3, d
		 TRP  #3
		 LDB  R3, d
		 TRP  #3
		 LDB  R3, ENDL
		 TRP  #3
ENDIF	 LDR  R15, ITR
		 ADI  R15, #1
		 STR  R15, ITR
		 JMP  WHILE
ENDWHILE LDB  R3, S
		 TRP  #3
		 LDB  R3, u
		 TRP  #3
		 LDB  R3, m
		 TRP  #3
		 LDB  R3, SPACE
		 TRP  #3
		 LDB  R3, i
		 TRP  #3
		 LDB  R3, s
		 TRP  #3
		 LDB  R3, SPACE
		 TRP  #3
		 LDR  R3, SUM
		 TRP  #1
		 LDB  R3, ENDL
		 TRP  #3
		 TRP  #0
;code segment end