    MACRO
    ADD1 arg1, arg2
    LOAD arg1
    ADD arg2
    STORE arg1
    MEND

LOAD N1
ADD N2
STORE N1
MEND 
 
ADD1 N1, N2 
 
MACRO 
MUL1 &arg3, &arg4 
MOV A, 00 
MOV C, &arg4 
Repeat: ADD &arg3 
JNZ Repeat 
MEND 
 
MUL1 N3 

    MACRO
    MUL1 &arg3, &arg4
    MOV A, 00
    MOV C, &arg4
    Repeat: ADD &arg3
        JNZ Repeat
    MEND

    MUL1 N3, N4