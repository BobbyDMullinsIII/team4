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
inptVal1:.BLOCK  2           ;first input number #2d
inptVal2:.BLOCK  2           ;second input number #2d
operator:.BYTE   'x'         ;expression operator #1c
answer:  .BLOCK  2           ;answer for input expression #2d          
;end global data

;input expression code block
main:    STRO    welcome,d   ;display welcome message and input prompt to the use     
         LDBA    charIn,d    ;A = input character
         ;parse
         DECI    inptVal1,d  ;inptVal2 = first number in expression
         LDBA    charIn,d    ;A = input character
         STBA    operator,d  ;store operator in 'operator'
         LDBA    charIn,d    ;A = input character
         ;parse
         DECI    inptVal2,d  ;inptVal2 = second number in expression


stopprog:STOP                ;end program symbol

;begin .ASCII strings
welcome: .ASCII  "Welcome to the Infix2Postfix Calculator.\nPlease enter a single digit, single operation equation using addition and subtraction only. Ex. a+b or a-b.\n\x00"
;end .ASCII strings

         .END                ;end code