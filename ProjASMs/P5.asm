FIB_N		.INT	0x00
FIB_RES		.INT
WHILE_ITR	.INT	0x00

WHILE_MSG	.STR	"Please enter n:  "
RTN_MSG_ONE	.STR	"Fibonacci of "
RTN_MSG_TWO	.STR	" is "
ENDL		.BYT	'\n'

			JMP		MAIN

FIB			MOV		R1, R0
			CMPI	R1, #2
			BGT		R1, FIB_BODY
			JMR		R15

FIB_BODY	PUSH	R15				;store the current link register (R15) on the stack
			ADI		R0, #-1			;calculate this levels n - 1 and set it to R0 (the register used to pass argument one to a subroutine)
			PUSH	R0				;store our current n value on the stack
			BAL		R15, FIB		;recursive call one to FIB
			MOV		R1, R0			;copy value returned from call to fib into R1 (returned from fib in R0)
			POP		R0				;restore the value of n from the stack, put it back into R0 so it can be used as an argument to next branch of fib
			PUSH	R1				;store the result of that branch of recusion (FIB) that just returned. Returned DWORD in R0, we copied into R1
			ADI		R0, #1			;calculate this levels n - 2
			BAL		R15, FIB		;recursive call two to FIB
			POP		R1				;restore the result of first branch of fib back into R1
			ADD		R0, R1			;calculate fin(n - 1) + fin(n - 2), result in R0 for returning of value
			POP		R15				;restore out R15 (link register) value that we pushed at the beginning of this recursive step
			JMR		R15				;jump back to link register PC value. resursive step done
									
MAIN		LDR		R0, WHILE_ITR	;load the while loop's iterator into R0
			CMPI	R0, #15
			BLT		R0, WHILE_BODY
			TRP		#0				;if we have reached 15 iterations (WHILE_ITR == 14) we exit

WHILE_BODY	LDA		R3, WHILE_MSG
			TRP		#5
			TRP		#2
			MOV		R0, R3
			CMPI	R3, #-1
			BNZ		R3, CALL_FIB
			TRP		#0

CALL_FIB	PUSH	R0
			BAL		R15, FIB

			LDA		R3, RTN_MSG_ONE
			TRP		#5
			POP		R3
			TRP		#1
			LDA		R3, RTN_MSG_TWO
			TRP		#5
			MOV		R3, R0
			TRP		#1
			LDB		R3, ENDL
			TRP		#3

			LDR		R0, WHILE_ITR
			ADI		R0, #1
			STR		R0, WHILE_ITR

			JMP		MAIN