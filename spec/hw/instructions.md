# Project 0930 Instruction Set

## Arithmetic

### 0x00xy ADD Rx, Ry

Add
`Rx = Rx + Ry`

### 0x01xy ADC Rx, Ry

Add with carry
`Rx = Rx + Ry + C`

### 0x02xy SUB Rx, Ry

Subtract
`Rx = Rx - Ry`

### 0x03xy SBC Rx, Ry

Subtract with carry
`Rx = (Rx - Ry) + C`

### 0x04xy RSB Rx, Ry

Reverse subtract
`Rx = Ry - Rx`

### 0x05xy RBC Rx, Ry

Reverse subtract with carry
`Rx = (Ry - Rx) + C`

### 0x06xy MUL Rx, Ry

Multiply
`Rx = Rx * Ry`

### 0x07xy MLS Rx, Ry

Multiply signed
`Rx = signed Rx * Ry`

### 0x08xy DIV Rx, Ry

Divide
`Rx = Rx / Ry`

### 0x09xy DVS Rx, Ry

Divide signed
`Rx = signed Rx / Ry`

### 0x0Axy MOD Rx, Ry

Modulus
`Rx = Rx % Ry`

### 0x0Bxy MDS Rx, Ry

Modulus signed
`Rx = Rx % Ry`

### 0x0Cxy MOV Rx, Ry

Move
`Rx = Ry`

### 0x10xy SAL Rx, Ry

Shift arithmetic left
`Rx = Rx << Ry`

### 0x11xy SAR Rx, Ry

Shift arithmetic right
`Rx = Rx >> Ry`

### 0x12xy SLS Rx, Ry

Shift arithmetic left signed
+1 cycle
`if (Rx >= 0) Rx = Rx << Ry`
`else Rx = Rx >> Ry`

### 0x13xy SRS Rx, Ry

Shift arithmetic right signed
+1 cycle
`if (Rx >= 0) Rx = Rx >> Ry`
`else Rx = Rx << Ry`

### 0x14xy AND Rx, Ry

AND
`Rx = Rx & Ry`

### 0x15xy OR Rx, Ry

OR
`Rx = Rx | Ry`

### 0x16xy XOR Rx, Ry

XOR
`Rx = Rx ^ Ry`

### 0x20xy IFE Rx, Ry

If equal execute next instruction
`if (Rx != Ry) PC += 2`

### 0x21xy IFN Rx, Ry

If not equal execute next instruction
`if (Rx == Ry) PC += 2`

### 0x22xy IFL Rx, Ry

If less than execute next instruction
`if (Rx >= Ry) PC += 2`

### 0x23xy IFLE Rx, Ry

If less than or equal to execute next instruction
`if (Rx > Ry) PC += 2`

### 0x24xy IFG Rx, Ry

If greater than execute next instruction
`if (Rx <= Ry) PC += 2`

### 0x25xy IFGE Rx, Ry

If greater than or equal to execute next instruction
`if (Rx < Ry) PC += 2`

### 0x26xy IFLS Rx, Ry

If less than signed execute next instruction
`if (Rx >= Ry) PC += 2`

### 0x27xy IFLES Rx, Ry

If less than or equal to signed execute next instruction
`if (Rx > Ry) PC += 2`

### 0x28xy IFGS Rx, Ry

If greater than signed execute next instruction
`if (Rx <= Ry) PC += 2`

### 0x29xy IFGES Rx, Ry

If greater than or equal to signed execute next instruction
`if (Rx < Ry) PC += 2`

## Memory

### 0x30xy LW Rx, Ry

Load word
`Rx = [Ry]`

### 0x31xy SW Rx, Ry

Store word
`[Rx] = Ry`

## I/O

### 0x40xy HWI Rx, Ry

Hardware interrupt to HWID Rx with argument Ry

## Other

### 0x5000 HLT

Halt CPU processing