MOV R0, 2

MOV R3, 2
SHL R3, 8
OR R3, 2


.loop:
    HWI R0, R3

    IFE R2, 0
        MOV PC, loop
    
    IFE R2, 27
        HLT

    HWI R4, R2

    MOV PC, wait

.wait:
    MOV R5, R2
    HWI R0, R3
    IFNE R5, R2
        MOV PC, loop

    MOV PC, wait