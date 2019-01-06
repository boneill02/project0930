MOVI R4, #6560
MOVI R0, #1
MOVI R1, #2

MOVI R7, #64

HWI R0, R0
HWI R0, R1
loop:
    
    INC R9
    IFE R9, R4
        INC R11
    
    IFE R11, R7
        HLT


JSRI loop