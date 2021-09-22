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
chekVal1:.BYTE   'x'         ;temo character val for checking for double-digit and negative numbers
chekVal2:.BYTE   'x'         ;temp character val for checking for double-digit and negative numbers
inptVal1:.BLOCK  2           ;first input number #2d
inptVal2:.BLOCK  2           ;second input number #2d
operator:.BYTE   'x'         ;expression operator #1c
answer:  .BLOCK  2           ;answer for input expression #2d
;end global data

;input expression code block
main:    STRO    welcome,d   ;display welcome message and input prompt to the use  

         ;(code for first number(and checking if it is negative or double-digit) goes here)
         LDBA    charIn,d    ;A = input character
         
         ;code for storing operator
         LDBA    charIn,d    ;A = input character
         STBA    operator,d  ;store operator in 'operator'

         ;(code for second number(and checking if it is negative or double-digit) goes here)
         LDBA    charIn,d    ;A = input character


;store negative number if negative number detected code block
storeneg:;(code for putting negative number in stack goes here)

;store double-digit number if double-digit number detected code block
storedub:;(code for putting double-digit number in stack goes here)

;calculate final answer code block
calcansw:LDBA    operator,d  ;A = value in operator
         CPBA    '+',i       ;is operator equal to + ?
         BRNE    subtcalc    ;no  ->go to subtcalc to subtract second number from first number
                             ;yes  ->add first number and second number together
         ;(code for adding numbers together goes here)

subtcalc:;(code for subtracting first number from second number goes here)

;output postfix expression code block
psfxdisp:;(output first number code goes here)
         ;(use delineator if negative or double-digit)

         ;(output second number code goes here)
         ;(use delineator if negative or double-digit)

         LDBA    operator,d  ;load operator into accumulator
         STBA    charOut,d   ;output display operator


stopprog:STOP                ;end program symbol

;begin .ASCII strings
welcome: .ASCII  "Welcome to the Infix2Postfix Calculator.\nPlease enter a single digit, single operation equation using addition and subtraction only. Ex. a+b or a-b.\n\x00"
;end .ASCII strings

         .END                ;end code