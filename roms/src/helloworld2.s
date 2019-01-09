; HELLO WORLD (V2)
; Ben O'Neill

; R0: Hello world length
; R1: Hello world memory point
; R2: Hello world counter
; R3: Hello world character

MOV R1, hello
ADD R1, 1
MOV R0, 13

.loop:
    LW R3, R1
    ADD R1, 1
    HWI R4, R3
    IFE R3, R2
        HLT
    
    MOV PC, loop

.hello:
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
    dw 10
    dw 0