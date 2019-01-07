ADD R0, #1

ADD R1, #1
SAL R1, #8

ADD R2, #2
SAL R2, #8

HWI R0, R1
HWI R0, R2

wait:
    IFE R0, R1
        ADD R3, #1

    IFE R3, #50
        HLT

    ADD R0, #1
    MOV R13, wait