;********************************************************************************
;* Program Name: project1.pep
;* Programmer: Group 4 (Alexander Simpson, Austen Boda, Bobby Mullins, Ethan Morgan, Ty Seiber)
;* Class: CSCI 2160-001
;* Project: Project 1
;* Date: 2021-09-16
;* Purpose: project1.pep main assembly file for Infix2Postfix Calculator
;********************************************************************************

         BR      main        ;go directly to 'main' instruction to skip bytes

;begin global data
chekVal1:.BLOCK  2           ;temp character val for checkin double-digit and negative numbers #2c
chekVal2:.BLOCK  2           ;temp character val for checking double-digit and negative numbers #2c
inptVal1:.WORD   0x0000      ;first input number #2d
inptVal2:.WORD   0x0000      ;second input number #2d
operator:.BYTE   'x'         ;expression operator #1c
answer:  .WORD   0x0000      ;answer for input expression #2d
;end global data

;input expression code block
main:    STRO    welcome,d   ;display welcome message and input prompt to the use


;INFIX INPUT SECTION
;********************************************************************************
;check first number(and checking if it is negative or double-digit) code block
check1st:LDBA    charIn,d    ;A = input character for checking
         CPBA    '-',i       ;is there a negative sign?
         BREQ    storeneg    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal1,d  ;No --> store first number in chekVal1
         LDBA    chekVal1,d  ;Load that number back up
         SUBA    0x0030,i    ;Subtract 0x0030 from that number to get it as a decimal value
         STWA    inptVal1,d  ;Store this as a word into inptVal1
 
chekaddi:LDBA    charIn,d    ;A = input character for checking
         CPBA    '+',i       ;is there a plus + operator?
         BRNE    cheksubt    ;no ->go to cheksubt for checking is operator is a minus sign
         STBA    operator,d  ;yes ->store operator
         BR      check2nd    ;branch to check2nd for checking second full number in input equation

cheksubt:CPBA    '-',i       ;is there a minus - operator?
         BRNE    storedub    ;no ->go to storedub for storing double-digit number in stack
         STBA    operator,d  ;yes ->store operator

;check second number(and checking if it is negative or double-digit) code block
check2nd:LDBA    charIn,d    ;A = input character for checking
         CPBA    '-',i       ;is there a negative sign?
         BREQ    storeneg    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal2,d  ;no ->store current char and parse to next char  
         LDBA    chekVal2,d  ;Load in chekVal2
         SUBA    0x0030,i    ;Subtract 0x0030 from chekVal2 to get it as a decimal value
         STWA    inptVal2,d  ;Stroe this as a word into inptVal2


;CPBA    '',i       ;is there an empty character in input after previous charIn?
;(im not sure what the real empty input character is, if anyone knows, please put it here)

         BR      calcansw    ;yes  ->go to calcansw for calculating answer to expression
         STBA    storedub,d  ;no ->go to storedub for double-digit input

;code block for pushing inptVal1 into stack
         SUBSP   2,i         ;push single-digit #inptVal1 ;WARNING: inptVal1 not specified in .EQUATE
         LDWA    inptVal1,d  ;A = inptVal1
         STWA    0,s         ;inptVal1 on the stack

;code block for pushing inptVal2 into stack
         SUBSP   2,i         ;push single-digit #inptVal2 ;WARNING: inptVal2 not specified in .EQUATE
         LDWA    inptVal2,d  ;A = inptVal2
         STWA    0,s         ;inptVal2 on the stack

;store negative number if negative number detected code block
storeneg:STBA    chekVal1,d  ;store minus sign in checkVal1
         LDBA    charIn,d    ;A = input digit
         STBA    chekVal2,d  ;store second character in checkVal2
;(code for combining checkVal1 minus sign and checkVal2 digit into single number goes here)
;(code for putting negative number in stack goes here)

;store double-digit number if double-digit number detected code block
storedub:STBA    chekVal2,d  
;(code for combining checkVal1 digit and checkVal2 digit into single number goes here)
;(code for putting double-digit number in stack goes here)

;********************************************************************************


;ANSWER CALCULATION AND POSTFIX OUTPUT SECTION
;********************************************************************************
;code block for popping inptVal2 from stack
calcansw:ADDSP   2,i         ;pop single-digit #inptVal2 ;WARNING: inptVal2 not specified in .EQUATE
         LDWA    0,s         ;A = inptVal2
         STWA    inptVal2,s  ;inptVal2 off the stack

;code block for popping inptVal1 from stack
         ADDSP   2,i         ;pop single-digit #inptVal1 ;WARNING: inptVal1 not specified in .EQUATE
         LDWA    0,s         ;A = inptVal1
         STWA    inptVal1,s  ;inptVal1 off the stack

;(code for adding numbers together goes here)
;(remember that the first digit to be popped off the stack will be the right-hand number)
         LDBA    operator,d  ;A = value in operator
         CPBA    '+',i       ;is operator equal to + ?
         BRNE    subtcalc    ;no  ->go to subtcalc to subtract second number from first number
         LDWA    inptVal1,d  ;yes  ->add first number and second number together from stack
         ADDA    inptVal2,d  ;add second number.
         STWA    answer,d    ;store answer as a word 
         BR      output      ;Branch to output when finished

;(code for subtracting first number from second number goes here)
;(remember that the first digit to be popped off the stack will be the right-hand number)
subtcalc:LDBA    operator,d  ;A = value in operator
         CPBA    '-',i       ;is operator equal to + ?
         BRNE    stopprog    ;no  ->go to subtcalc to subtract second number from first number
         LDWA    inptVal1,d  ;yes  ->add first number and second number together from stack
         SUBA    inptVal2,d  ;subtract second number.
         STWA    answer,d    ;store answer
         BR      output      ;Branch to output when finished


;output postfix expression code block

;(output first number code goes here)
;(use delineator if negative or double-digit)

;(output second number code goes here)
;(use delineator if negative or double-digit)
output:  STRO    postout,d   ;output postout to specify that it is a postout expression
         LDBA    chekVal1,d  ;load value 1
         STBA    charOut,d   ;output display 1
         LDBA    chekVal2,d  ;load value 2
         STBA    charOut,d   ;output display value 2
         LDBA    operator,d  ;A = operator for output display is postfix expression
         STBA    charOut,d   ;output display operator
         STRO    equals,d    ;output display equals sign
         DECO    answer,d    ;output display answer

;(use delineator if negative or double-digit)

;********************************************************************************

stopprog:STOP                ;end program symbol

;begin .ASCII strings
welcome: .ASCII  "Welcome to the Infix2Postfix Calculator.\nPlease enter a single digit, single operation equation using addition and subtraction only. Ex. a+b or a-b.\n\x00"

equals:  .ASCII  "=\x00"     ;does not go to new line

postout: .ASCII  "Postfix expression: \x00"

;end .ASCII strings

         .END                  ;end code
