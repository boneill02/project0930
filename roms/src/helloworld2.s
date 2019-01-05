; HELLO WORLD (V2)
; Ben O'Neill

; R0: Hello world length
; R1: Hello world memory point
; R2: Hello world counter
; R3: Hello world character

LPWI R1, hello
MOVI R0, #13

loop:
    INC R2
    INC R1
    LPW R3, R1
    HWI R4, R3
    IFE R2, R0
        HLT

JSRI loop


hello:
    dw hello
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