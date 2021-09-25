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
chekVal1:.byte  'x'          ;temp character val for checkin double-digit and negative numbers #1c 
chekVal2:.byte  'x'          ;temp character val for checking double-digit and negative numbers #1c 
inptVal1:.BLOCK  1           ;first input number #1d
inptVal2:.BLOCK  1           ;second input number #1d
operator:.BYTE   'x'         ;expression operator #1c
answer:  .byte  'x'          ;answer for input expression #1c
mask:    .WORD   0x0030      ;Mask for ASCII char
;end global data

;input expression code block
main:    STRO    welcome,d   ;display welcome message and input prompt to the use  


;INFIX INPUT SECTION
;********************************************************************************
;check first number(and checking if it is negative or double-digit) code block
check1st:LDBA    charIn,d    ;A = input character for checking
         CPBA    '-',i       ;is there a negative sign?
         BREQ    storeneg    ;yes  ->go to storeneg for storing negative number in stack
         STBA    chekVal1,d  ;no ->store current char and parse to next char
         LDBA    charIn,d    ;A = input character for checking
         
chekaddi:CPBA    '+',i       ;is there a plus + operator?
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
        
         
         LDBA    charIn,d    ;A = input character for checking
         ;CPBA    '',i       ;is there an empty character in input after previous charIn? 
         ;(im not sure what the real empty input character is, if anyone knows, please put it here)

         BR      calcansw    ;yes  ->go to calcansw for calculating answer to expression
         STBA    storedub,d  ;no ->go to storedub for double-digit input  


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
;calculate final answer code block

         ;(code for adding numbers together goes here)
         ;(remember that the first digit to be popped off the stack will be the right-hand number)
calcansw:LDBA    operator,d  ;A = value in operator
         CPBA    '+',i       ;is operator equal to + ?
         BRNE    subtcalc    ;no  ->go to subtcalc to subtract second number from first number 
         LDBA    chekVal1,d  ;yes  ->add first number and second number together from stack
         ADDA    chekVal1,d  ;add second number.
         SUBA    9,d         ;Add 9 or 30 in this case to get the correct ASCII answer
         STBA    answer,d    ;store answer
         BR      output      ;Branch to output when finished
         
         ;(code for subtracting first number from second number goes here) 
         ;(remember that the first digit to be popped off the stack will be the right-hand number)
subtcalc:LDBA    operator,d  ;A = value in operator
         CPBA    '-',i       ;is operator equal to + ?
         BRNE    stopprog    ;no  ->go to subtcalc to subtract second number from first number 
         LDBA    chekVal1,d  ;yes  ->add first number and second number together from stack
         SUBA    chekVal1,d  ;subtract second number.
         ADDA    9,d         ;Add 9 or 30 in this case to get the correct ASCII answer
         STBA    answer,d    ;store answer
         BR      output      ;Branch to output when finished
         

         ;output postfix expression code block
          
         ;(output first number code goes here) 
         ;(use delineator if negative or double-digit)

         ;(output second number code goes here)
         ;(use delineator if negative or double-digit)
output:  LDBA    chekVal1,d  ;load value 1
         STBA    charOut,d   ;output display 1
         LDBA    operator,d  ;A = operator for output display is postfix expression
         STBA    charOut,d   ;output display operator
         LDBA    chekVal2,d  ;load value 2
         STBA    charOut,d   ;output display value 2
         STRO    equals,d    ;output display equals sign
         STRO    answer,d    ;output display answer
        
         ;(use delineator if negative or double-digit)

;********************************************************************************

stopprog:STOP                ;end program symbol

;begin .ASCII strings
welcome: .ASCII  "Welcome to the Infix2Postfix Calculator.\nPlease enter a single digit, single operation equation using addition and subtraction only. Ex. a+b or a-b.\n\x00"
equals:  .ASCII  "=\x00"     ;does not go to new line
;end .ASCII strings

         .END                ;end code