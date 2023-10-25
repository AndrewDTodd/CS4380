;  FIRST FOUR BYTES: Initial Program Counter 
;      The address/offset of the first instruction:  6 (0x00000006)

;  First Static/Global Variable in the Data Segment
H            .BYT 'H'         ; offset 4 (first pass create symbol table  { <label_name>: offset })
e            .BYT 'e'         ; offset 5
l            .BYT 'l'         ; offset 6
o            .BYT 'o'         ; offset 7
SPACE        .BYT ' '         ; offset 8
A            .BYT 'A'         ; offset 9
n            .BYT 'n'         ; offset 10
d            .BYT 'd'         ; offset 11
r            .BYT 'r'         ; offset 12
w            .BYT 'w'         ; offset 13
T            .BYT 'T'         ; offset 14
I            .BYT 'I'         ; offset 15
c            .BYT 'c'         ; offset 16
a            .BYT 'a'         ; offset 17
p            .BYT 'p'         ; offset 18
i            .BYT 'i'         ; offset 19
t            .BYT 't'         ; offset 20
SEMICOLON    .BYT ';'         ; offset 21
CHAR_ONE     .BYT '1'         ; offset 22
CHAR_PLUS    .BYT '+'         ; offset 23
CHAR_THREE   .BYT '3'         ; offset 24
CHAR_EQUALS  .BYT '='         ; offset 25
CHAR_TWO     .BYT '2'         ; offset 26
CHAR_MUL     .BYT '*'         ; offset 27
CHAR_MINUS   .BYT '-'         ; offset 28
CHAR_FIVE    .BYT '5'         ; offset 29
CHAR_DIV     .BYT '/'         ; offset 30
ONE          .INT #1          ; offset 31
TWO          .INT 0x2         ; offset 35
THREE        .INT 0x3         ; offset 39
FIVE         .INT #5          ; offset 43
G            .BYT 'G'         ; offset 47
b            .BYT 'b'         ; offset 48
y            .BYT 'y'         ; offset 49
RIGHT_BR     .BYT '<'         ; offset 50
LEFT_BR      .BYT '>'         ; offset 51
ENDL         .BYT '\n'        ; offset 52
RES          .INT #0          ; offset 53

;  First Instruction in the Code Segment 
; (No Static/Global Variables Allowed After the First Instruction)
         JMP  MAIN            ; offset 57  => 0x00000001, 0x00000012, 0x00000000 ;First Instruction
MAIN     LDB  R3, H           ; offset 69  => 0x0000000C, 0x00000003, 0x00000004
         TRP  #3              ; offset 81
         LDB  R3, e           ; offset 93
         TRP  #3              ; offset 105
         LDB  R3, l           ; offset 
         TRP  #3              ; offset 
         LDB  R3, l           ; offset 
         TRP  #3              ; offset 
         LDB  R3, o           ; offset 
         TRP  #3              ; offset 
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset 
         LDB  R3, RIGHT_BR    ; offset 
         TRP  #3              ; offset 
         LDB  R3, A           ; offset 
         TRP  #3              ; offset 
         LDB  R3, n           ; offset 
         TRP  #3              ; offset 
         LDB  R3, d           ; offset 
         TRP  #3              ; offset 
         LDB  R3, r           ; offset 
         TRP  #3              ; offset 
         LDB  R3, e           ; offset 
         TRP  #3              ; offset 
         LDB  R3, w           ; offset 
         TRP  #3              ; offset 
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset 
         LDB  R3, T           ; offset 
         TRP  #3              ; offset 
         LDB  R3, o           ; offset 
         TRP  #3              ; offset 
         LDB  R3, d           ; offset 
         TRP  #3              ; offset 
         LDB  R3, d           ; offset 
         TRP  #3              ; offset 
         LDB  R3, LEFT_BR     ; offset 
         TRP  #3              ; offset 
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 510

         LDR  R3, ONE         ; offset 522
         LDR  R1, THREE       ; offset
         ADD  R3, R1          ; offset 
         STR  R3, RES         ; offset
         LDB  R3, CHAR_ONE    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_PLUS   ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_THREE  ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_EQUALS ; offset 
         TRP  #3              ; offset
         LDR  R3, RES         ; offset 
         TRP  #1              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 

         LDR  R3, TWO         ; offset
         LDR  R1, THREE       ; offset 
         MUL  R3, R1          ; offset 
         STR  R3, RES         ; offset
         LDB  R3, CHAR_TWO    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_MUL    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_THREE  ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_EQUALS ; offset 
         TRP  #3              ; offset
         LDR  R3, RES         ; offset 
         TRP  #1              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 

         LDR  R3, ONE         ; offset 
         LDR  R1, FIVE        ; offset
         SUB  R3, R1          ; offset 
         STR  R3, RES         ; offset
         LDB  R3, CHAR_ONE    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_MINUS  ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_FIVE   ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_EQUALS ; offset 
         TRP  #3              ; offset
         LDR  R3, RES         ; offset 
         TRP  #1              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 

         LDR  R3, FIVE        ; offset 
         LDR  R1, TWO         ; offset
         DIV  R3, R1         ; offset 
         STR  R3, RES         ; offset
         LDB  R3, CHAR_FIVE   ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_DIV    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_TWO    ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, CHAR_EQUALS ; offset 
         TRP  #3              ; offset
         LDR  R3, RES         ; offset 
         TRP  #1              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 

         LDB  R3, I           ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, c           ; offset 
         TRP  #3              ; offset
         LDB  R3, a           ; offset 
         TRP  #3              ; offset
         LDB  R3, n           ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, p           ; offset 
         TRP  #3              ; offset
         LDB  R3, r           ; offset 
         TRP  #3              ; offset
         LDB  R3, i           ; offset 
         TRP  #3              ; offset
         LDB  R3, n           ; offset 
         TRP  #3              ; offset
         LDB  R3, t           ; offset 
         TRP  #3              ; offset
         LDB  R3, SPACE       ; offset 
         TRP  #3              ; offset
         LDB  R3, SEMICOLON   ; offset 
         TRP  #3              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 

         LDB  R3, G           ; offset 
         TRP  #3              ; offset
         LDB  R3, o           ; offset 
         TRP  #3              ; offset
         LDB  R3, o           ; offset 
         TRP  #3              ; offset
         LDB  R3, d           ; offset 
         TRP  #3              ; offset
         LDB  R3, b           ; offset 
         TRP  #3              ; offset
         LDB  R3, y           ; offset 
         TRP  #3              ; offset
         LDB  R3, e           ; offset 
         TRP  #3              ; offset
         LDB  R3, ENDL        ; offset 
         TRP  #3              ; offset 
         TRP  #0              ; offset 