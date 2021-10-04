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
chekVal1:.BLOCK  2           ;temp character val for checking double-digit and negative numbers #2c
chekVal2:.BLOCK  2           ;temp character val for checking double-digit and negative numbers #2c
chekVal3:.BLOCK  2           ;temp character val for checking double-digit and negative numbers #2c
inptVal1:.WORD   0x0000      ;first input number #2d
inptVal2:.WORD   0x0000      ;second input number #2d
inptVal3:.WORD   0x0000      ;third input number
operator:.BYTE   'x'         ;expression operator #1c
answer:  .WORD   0x0000      ;answer for input expression #2d
negdigt1:.BYTE   'x'         ;holds negative sign for a digit
negdigt2:.BYTE   'x'         ;holds negative sign for a digit
multiop: .BYTE   'x'         ;holds experssion operator for multiple operations
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
         BREQ    storneg2    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal2,d  ;no ->store current char and parse to next char
         LDBA    chekVal2,d  ;Load in chekVal2
         SUBA    0x0030,i    ;Subtract 0x0030 from chekVal2 to get it as a decimal value
         STWA    inptVal2,d  ;Store this as a word into inptVal2


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
storeneg:STBA    negdigt1,d  ;store minus sign in negdigit
         LDBA    charIn,d    ;A = input digit
         STBA    chekVal1,d  ;store first number in checkVal1
         LDBA    chekVal1,d  ;Load that number back up
         SUBA    0x0030,i    ;Subtract 0x0030 from that number to get it as a decimal value
         STWA    inptVal1,d  ;Store this as a word into inptVal1
         LDWA    inptVal1,d  ;load number back into A
         NEGA                ;negate the number to make it negative
         STWA    inptVal1,d  ;store the new negative number
         NEGA                ;negat the accumulator again to put it back into a postive state

negadd:  LDBA    charIn,d    ;A = input character for checking
         CPBA    '+',i       ;is there a plus + operator?
         BRNE    negsubt     ;no ->go to cheksubt for checking is operator is a minus sign
         STBA    operator,d  ;yes ->store operator
         BR      chek2neg    ;branch to check the second number

negsubt: CPBA    '-',i       ;is there a minus - operator?
         BRNE    storedub    ;no ->go to storedub for storing double-digit number in stack
         STBA    operator,d  ;yes ->store operator

chek2neg:LDBA    charIn,d    ;A = input character for checking
         CPBA    '-',i       ;is there a negative sign?
         BREQ    storneg2    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal2,d  ;no ->store current char and parse to next char
         LDBA    chekVal2,d  ;Load in chekVal2
         SUBA    0x0030,i    ;Subtract 0x0030 from chekVal2 to get it as a decimal value
         STWA    inptVal2,d  ;Store this as a word into inptVal2
         BR      postneg     ;if the second value is aquired then branch to the postfix output

storneg2:STBA    negdigt2,d  ;store minus sign in negdigit
         LDBA    charIn,d    ;A = input digit
         STBA    chekVal2,d  ;store first number in checkVal1
         LDBA    chekVal2,d  ;Load that number back up
         SUBA    0x0030,i    ;Subtract 0x0030 from that number to get it as a decimal value
         STWA    inptVal2,d  ;Store this as a word into inptVal1
         LDWA    inptVal2,d  ;load number back into A
         NEGA                ;negate the number to make it negative
         STWA    inptVal2,d  ;store the new negative number
         NEGA                ;negate the accumulator to put it back into a postive state
         BR      calc        


multiple:LDBA    answer,d    ;load answer into A
         CPBA    0,i         ;compare the answer to 0
         BRGT    nonegate    ;if greater than 0 branch past negate
         NEGA                ;if answer is negative negate it
nonegate:LDBA    charIn,d    ;load in next character
         CPBA    '\n',i      ;see if there is anymore input
         BREQ    output      ;if not branch to output
         STBA    multiop,d   ;store input if there is any
         LDBA    charIn,d    ;load next digit
;CPBA    '-',i       ;is there a negative sign?
;BREQ    storeneg    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal3,d  ;No --> store first number in chekVal1
         LDBA    chekVal3,d  ;Load that number back up
         SUBA    0x0030,i    ;Subtract 0x0030 from that number to get it as a decimal value
         STWA    inptVal3,d  ;Store this as a word into inptVal1
         LDWA    answer,d    ;load the answer back
         ADDA    inptVal3,d  ;add it to the next number
         STWA    answer,d    ;store it as the new answer
         BR      output      ;output




;(code for combining checkVal1 minus sign and checkVal2 digit into single number goes here)
;(code for putting negative number in stack goes here)
postneg: ADDSP   3,i         ;pop negative single digit ;WARNING: Number of bytes allocated (3) not equal to number of bytes listed in trace tag (0).
         LDBA    0,s         ;A <---- negdigt2
         STBA    negdigt2,s  ;negdigt1 off the stack
         LDWA    1,s         ;A <---- inputVal2
         STWA    inptVal2,s  ;inptVal2 off the stack

         ADDSP   3,i         ;pop negative single digit ;WARNING: Number of bytes allocated (3) not equal to number of bytes listed in trace tag (0).
         LDBA    0,s         ;A <---- negdigt1
         STBA    negdigt1,s  ;negdigt1 off the stack
         LDWA    1,s         ;A <---- inputVal1
         STWA    inptVal1,s  ;inptVal2 off the stack
         BR      calc        ;branch to calc to solve the expression
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
calc:    LDBA    operator,d  ;A = value in operator
         CPBA    '+',i       ;is operator equal to + ?
         BRNE    subtcalc    ;no  ->go to subtcalc to subtract second number from first number
         LDWA    inptVal1,d  ;yes  ->add first number and second number together from stack
         ADDA    inptVal2,d  ;add second number.
         STWA    answer,d    ;store answer as a word
         BR      multiple    ;branch to check if there are multiple operations
         BR      output      ;Branch to output when finished

;(code for subtracting first number from second number goes here)
;(remember that the first digit to be popped off the stack will be the right-hand number)
subtcalc:LDBA    operator,d  ;A = value in operator
         CPBA    '-',i       ;is operator equal to + ?
         BRNE    stopprog    ;no  ->go to subtcalc to subtract second number from first number
         LDWA    inptVal1,d  ;yes  ->add first number and second number together from stack
         SUBA    inptVal2,d  ;subtract second number.
         STWA    answer,d    ;store answer
         BR      multiple    ;branch to check if there are multiple operations
         BR      output      ;Branch to output when finished


;output postfix expression code block

;(output first number code goes here)
;(use delineator if negative or double-digit)

;(output second number code goes here)
;(use delineator if negative or double-digit)
output:  STRO    postout,d   ;output postout to specify that it is a postout expression
         LDBA    negdigt1,d  ;A = negative symbol for first number
         CPBA    '-',i       ;checks if there is a negative symbol
         BRNE    skipneg1    ;if there isnt a negative then do not output
         STBA    charOut,d   ;output first negative symbol
skipneg1:LDBA    chekVal1,d  ;load value 1
         STBA    charOut,d   ;output display 1
         LDBA    negdigt2,d  ;A = negative symbol for second number
         CPBA    '-',i       ;checks if there is a negative symbol
         BRNE    skipneg2    ;if there isnt a negative then do not output
         STBA    charOut,d   ;output second negative symbol
skipneg2:LDBA    chekVal2,d  ;load value 2
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
