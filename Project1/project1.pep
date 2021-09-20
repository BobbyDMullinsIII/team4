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

;end global data

main:    STRO    welcome,d   ;display welcome message and input prompt to the user

         

stopprog:STOP                ;end program symbol

;begin .ASCII strings
welcome: .ASCII  "Welcome to the Infix2Postfix Calculator.\nPlease enter a single digit, sinlge operation equation using addition and subtraction only. Ex. a+b or a-b.\n\x00"
;end .ASCII strings

         .END                ;end code