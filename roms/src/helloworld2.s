; HELLO WORLD (V2)
; Ben O'Neill

; R0: Hello world length
; R1: Hello world memory point
; R2: Hello world counter
; R3: Hello world character

LW R1, hello
ADD R1, #4
MOV R0, #13

loop:
    ADD R1, #1
    LW R3, R1
    HWI R4, R3
    IFE R3, R2
        HLT
    
    MOV R13, loop

hello:
    dw 'H'
    dw 'e'
    dw 'l'
    dw 'l'
    dw 'o'
    dw ','
    dw ' '
    dw 'w'
    dw 'o'
    dw 'r'
    dw 'l'
    dw 'd'
    dw '!'
    dw #10
    dw #0