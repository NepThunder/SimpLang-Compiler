; Variable declaration for 'a'
ldi r1 10   ;Load inittial value
mov M r1 1    ;Store in Variable 'a'
; Variable declaration for 'b'
ldi r1 20   ;Load inittial value
mov M r1 2    ;Store in Variable 'b'
; Variable declaration for 'c'
mov r1 M 1   ;Load Variable
mov r2 M 2   ;Load Variable
add   ;A=A+B or r1=r1+r2    ;didn't mention any register in instruction
mov M r1 3    ;Store in Variable 'c'
;if Statement
mov r1 M 3    ;Load Variable for comparision
ldi r2 30    ;Load Constant
cmp   ;Compare A and B or r1 and r2
jnz %ESLE0
mov r1 M 3   ;Load Variable
ldi r2 1    ;Load constant
add   ;A=A+B or r1=r1+r2    ;didn't mention any register in instruction
mov M r1 3    ;Store in Variable 'c'
jmp %ENDIF0
ESLE0:  ;ESLE Label
ENDIF0:  ;END Label
