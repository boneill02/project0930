# BK-16 Instruction Set

## Arithmetic

### 0x00xy ADD Rx, Ry

Add
`Rx = Rx + Ry`

### 0x01xy ADC Rx, Ry

Add with carry
`Rx = Rx + Ry + R15`

### 0x02xy SUB Rx, Ry

Subtract
`Rx = Rx - Ry`

### 0x03xy SBC Rx, Ry

Subtract with carry
`Rx = (Rx - Ry) + R15`

### 0x04xy RSB Rx, Ry

Reverse subtract
`Rx = Ry - Rx`

### 0x05xy RBC Rx, Ry

Reverse subtract with carry
`Rx = (Ry - Rx) + R15`

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

### 0x0Dx0 INC Rx

Increment
`Rx = Rx + 1`

### 0x0Ex0 DEC Rx

Decrement
`Rx = Rx - 1`

### 0x0Fx0 CLR Rx

Clear
`Rx = 0`

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

### 0x15xy IOR Rx, Ry

OR
`Rx = Rx | Ry`

### 0x16xy NOT Rx, Ry

NOT
`Rx = Rx ~ Ry`

### 0x17xy XOR Rx, Ry

XOR
`Rx = Rx ^ Ry`

### 0x20xy ADD Rx, IMM

Add
`Rx = Rx + IMM`

### 0x21xy ADC Rx, IMM

Add with carry
`Rx = Rx + IMM + R15`

### 0x22xy SUB Rx, IMM

Subtract
`Rx = Rx - IMM`

### 0x23xy SBC Rx, IMM

Subtract with carry
`Rx = (Rx - IMM) + R15`

### 0x24xy RSB Rx, IMM

Reverse subtract
`Rx = IMM - Rx`

### 0x25xy RBC Rx, IMM

Reverse subtract with carry
`Rx = (IMM - Rx) + R15`

### 0x26xy MUL Rx, IMM

Multiply
`Rx = Rx * IMM`

### 0x27xy MLS Rx, IMM

Multiply with carry
`Rx = signed Rx * IMM`

### 0x28xy DIV Rx, IMM

Divide
`Rx = Rx / IMM`

### 0x29xy DIVS Rx, IMM

Divide signed
`Rx = signed Rx / IMM`

### 0x2Axy MOD Rx, IMM

Modulus
`Rx = Rx % IMM`

### 0x2Bxy MDS Rx, IMM

Modulus signed
`Rx = Rx % IMM`

### 0x2Cxy MOV Rx, IMM

Move
`Rx = IMM`

### 0x30xy SAL Rx, IMM

Shift arithmetic left
`Rx = Rx << IMM`

### 0x31xy SAR Rx, IMM

Shift arithmetic right
`Rx = Rx >> IMM`

### 0x32xy SLS Rx, IMM

Shift arithmetic left signed
+1 cycle
`if (Rx >= 0) Rx = Rx << IMM`
`else Rx = Rx >> IMM`

### 0x33xy SRS Rx, IMM

Shift arithmetic right signed
+1 cycle
`if (Rx >= 0) Rx = Rx >> IMM`
`else Rx = Rx << IMM`

### 0x34xy AND Rx, IMM

AND
`Rx = Rx & IMM`

### 0x35xy IOR Rx, IMM

OR
`Rx = Rx | IMM`

### 0x36xy NOT Rx, IMM

NOT
`Rx = Rx ~ IMM`

### 0x37xy XOR Rx, IMM

XOR
`Rx = Rx ^ IMM`

### 0x40xy IFE Rx, Ry

If equal execute next instruction
`if (Rx != Ry) R12 += 2`

### 0x41xy IFN Rx, Ry

If not equal execute next instruction
`if (Rx == Ry) R12 += 2`

### 0x42xy IFL Rx, Ry

If less than execute next instruction
`if (Rx >= Ry) R12 += 2`

### 0x43xy IFS Rx, Ry

If less than or equal to execute next instruction
`if (Rx > Ry) R12 += 2`

### 0x44xy IFG Rx, Ry

If greater than execute next instruction
`if (Rx <= Ry) R12 += 2`

### 0x45xy IFH Rx, Ry

If greater than or equal to execute next instruction
`if (Rx < Ry) R12 += 2`

### 0x46xy ILS Rx, Ry

If less than signed execute next instruction
`if (Rx >= Ry) R12 += 2`

### 0x47xy ISS Rx, Ry

If less than or equal to signed execute next instruction
`if (Rx > Ry) R12 += 2`

### 0x48xy IGS Rx, Ry

If greater than signed execute next instruction
`if (Rx <= Ry) R12 += 2`

### 0x49xy IHS Rx, Ry

If greater than or equal to signed execute next instruction
`if (Rx < Ry) R12 += 2`

## Memory

### 0x50xy LPW Rx, Ry

Load word
`Rx = [Ry]`

### 0x51xy LDW Rx, Ry

Load data word
`Rx = [Ry + 0x10000]`

### 0x52xy LPB Rx, Ry

Load byte
`Rx = [Ry]`

### 0x53xy LDB Rx, Ry

Load data byte
`Rx = [Ry + 0x10000]`

### 0x54xy SPW Rx, Ry

Store word
`[Rx] = Ry`

### 0x55xy SDW Rx, Ry

Store data word
`[Rx + 0x10000] = Ry`

### 0x56xy SPB Rx, Ry

Store byte
`[Rx] = Ry`

### 0x57xy SDB Rx, Ry

Store data byte
`[Rx + 0x10000] = Ry`

### 0x58x0 CPB Rx

Clear byte
`[Rx] = 0`

### 0x59x0 CDB Rx

Clear data byte
`[Rx + 0x10000] = 0`

### 0x5Ax0 CPW Rx

Clear word
`[Rx] = 0; [Rx + 1] = 0`

### 0x5Bx0 CDW Rx

Clear data word
`[Rx + 0x10000] = 0; [Rx + 0x10001] = 0`

### 0x60xy LPW Rx, IMM

Load word
`Rx = [IMM]`

### 0x61xy LDW Rx, IMM

Load data word
`Rx = [IMM + 0x10000]`

### 0x62xy LPB Rx, IMM

Load byte
`Rx = [IMM]`

### 0x63xy LDB Rx, IMM

Load data byte
`Rx = [IMM + 0x10000]`

### 0x64xy SPW Rx, IMM

Store word
`[Rx] = IMM`

### 0x65xy SDW Rx, IMM

Store data word
`[Rx + 0x10000] = IMM`

### 0x56xy SPB Rx, IMM

Store byte
`[Rx] = IMM`

### 0x57xy SDB Rx, IMM

Store data byte
`[Rx + 0x10000] = IMM`

## Branch

### 0x70x0 JMP Rx

Jump
`R12 = R12 + Rx`

### 0x7100 JMP IMM

Jump
`R12 = R12 + IMM`

### 0x72x0 JSR Rx

Jump to subroutine
+1 cycle
`R13 = R13 + 1; R12 = Rx`

### 0x7300 JSR IMM

Jump to subroutine
+2 cycles
`R13 = R13 + 2; R12 = IMM; [R13] = R12`

### 0x7400 RET

Return from subroutine
+1 cycle
`R13 = R13 - 2; R12 = [R13];`

## I/O

### 0x80x0 HWI Rx

Hardware interrupt with argument Rx

### 0x8001 HWI IMM

Hardware interrupt with argument IMM

### 0x81x0 HWN Rx

Rx = number of connected hardware devices (CPU included)

## Other

### 0x9000 HLT

Halt CPU processing
