# Project 0930 Instruction Set

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

### 0x20xy ADDI Rx, IMM

Add
`Rx = Rx + IMM`

### 0x21xy ADCI Rx, IMM

Add with carry
`Rx = Rx + IMM + R15`

### 0x22xy SUBI Rx, IMM

Subtract
`Rx = Rx - IMM`

### 0x23xy SBCI Rx, IMM

Subtract with carry
`Rx = (Rx - IMM) + R15`

### 0x24xy RSBI Rx, IMM

Reverse subtract
`Rx = IMM - Rx`

### 0x25xy RBCI Rx, IMM

Reverse subtract with carry
`Rx = (IMM - Rx) + R15`

### 0x26xy MULI Rx, IMM

Multiply
`Rx = Rx * IMM`

### 0x27xy MLSI Rx, IMM

Multiply with carry
`Rx = signed Rx * IMM`

### 0x28xy DIVI Rx, IMM

Divide
`Rx = Rx / IMM`

### 0x29xy DVSI Rx, IMM

Divide signed
`Rx = signed Rx / IMM`

### 0x2Axy MODI Rx, IMM

Modulus
`Rx = Rx % IMM`

### 0x2Bxy MDSI Rx, IMM

Modulus signed
`Rx = Rx % IMM`

### 0x2Cxy MOVI Rx, IMM

Move
`Rx = IMM`

### 0x30xy SALI Rx, IMM

Shift arithmetic left
`Rx = Rx << IMM`

### 0x31xy SARI Rx, IMM

Shift arithmetic right
`Rx = Rx >> IMM`

### 0x32xy SLSI Rx, IMM

Shift arithmetic left signed
+1 cycle
`if (Rx >= 0) Rx = Rx << IMM`
`else Rx = Rx >> IMM`

### 0x33xy SRSI Rx, IMM

Shift arithmetic right signed
+1 cycle
`if (Rx >= 0) Rx = Rx >> IMM`
`else Rx = Rx << IMM`

### 0x34xy ANDI Rx, IMM

AND
`Rx = Rx & IMM`

### 0x35xy IORI Rx, IMM

OR
`Rx = Rx | IMM`

### 0x36xy NOTI Rx, IMM

NOT
`Rx = ~IMM`

### 0x37xy XORI Rx, IMM

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

### 0x43xy IFLE Rx, Ry

If less than or equal to execute next instruction
`if (Rx > Ry) R12 += 2`

### 0x44xy IFG Rx, Ry

If greater than execute next instruction
`if (Rx <= Ry) R12 += 2`

### 0x45xy IFGE Rx, Ry

If greater than or equal to execute next instruction
`if (Rx < Ry) R12 += 2`

### 0x46xy IFLS Rx, Ry

If less than signed execute next instruction
`if (Rx >= Ry) R12 += 2`

### 0x47xy IFLES Rx, Ry

If less than or equal to signed execute next instruction
`if (Rx > Ry) R12 += 2`

### 0x48xy IFGS Rx, Ry

If greater than signed execute next instruction
`if (Rx <= Ry) R12 += 2`

### 0x49xy IFGES Rx, Ry

If greater than or equal to signed execute next instruction
`if (Rx < Ry) R12 += 2`

## Memory

### 0x50xy LPH Rx, Ry

Load program byte (high)
`Rx = ([Ry] & 0xFF00) >> 8`

### 0x51xy LPL Rx, Ry

Load program byte (low)
`Rx = [Ry] & 0x00FF`

### 0x52xy LDH Rx, Ry

Load data byte (high)
`Rx = ([Ry + 0x10000] & 0xFF00) >> 8`

### 0x53xy LDL Rx, Ry

Load data byte (low)
`Rx = [Ry + 0x10000] & 0x00FF`

### 0x54xy SPH Rx, Ry

Store program byte (high)
`[Rx] = ([Rx] & 0x00FF) | (Ry & 0xFF00)`

### 0x55xy SPL Rx, Ry

Store program byte (low)
`[Rx] = ([Rx] & 0xFF00) | (Ry & 0x00FF)`


### 0x56xy SDH Rx, Ry

Store data byte (high)
`[Rx + 0x10000] = ([Rx + 0x10000] & 0x00FF) | (Ry & 0xFF00)`

### 0x57xy SDL Rx, Ry

Store data byte (low)
`[Rx + 0x10000] = ([Rx + 0x10000] & 0xFF00) | (Ry & 0x00FF)`

### 0x58x0 CPH Rx

Clear program byte (high)
`[Rx] = [Rx] & 0x00FF`

### 0x59x0 CPL Rx

Clear program byte (low)
`[Rx] = [Rx] & 0xFF00`

### 0x5Ax0 CDH Rx

Clear program byte (high)
`[Rx + 0x10000] = [Rx + 0x10000] & 0x00FF`

### 0x5Bx0 CDL Rx

Clear program byte (low)
`[Rx + 0x10000] = [Rx + 0x10000] & 0xFF00`

### 0x60xy LPW Rx, Ry

Load word
`Rx = [Ry]`

### 0x61xy LDW Rx, Ry

Load data word
`Rx = [Ry + 0x10000]`

### 0x62xy SPW Rx, Ry

Store word
`[Rx] = Ry`

### 0x63xy SDW Rx, Ry

Store data word
`[Rx + 0x10000] = Ry`

### 0x64x0 CPW Rx

Clear word
`[Rx] = 0`

### 0x65x0 CDW Rx

Clear data word
`[Rx + 0x10000] = 0`

### 0x70x0 LPHI Rx, IMM

Load program byte (high)
`Rx = ([IMM] & 0xFF00) >> 8`

### 0x71x0 LPLI Rx, IMM

Load program byte (low)
`Rx = [IMM] & 0x00FF`

### 0x72x0 LDHI Rx, IMM

Load data byte (high)
`Rx = ([IMM + 0x10000] & 0xFF00) >> 8`

### 0x73x0 LDLI Rx, IMM

Load data byte (low)
`Rx = [IMM + 0x10000] & 0x00FF`

### 0x74x0 SPHI Rx, IMM

Store program byte (high)
`[Rx] = ([Rx] & 0x00FF) | (IMM & 0xFF00)`

### 0x75x0 SPLI Rx, IMM

Store program byte (low)
`[Rx] = ([Rx] & 0xFF00) | (IMM & 0x00FF)`


### 0x76xy SDHI Rx, IMM

Store data byte (high)
`[Rx + 0x10000] = ([Rx + 0x10000] & 0x00FF) | (IMM & 0xFF00)`

### 0x77xy SDLI Rx, IMM

Store data byte (low)
`[Rx + 0x10000] = ([Rx + 0x10000] & 0xFF00) | (IMM & 0x00FF)`

### 0x80xy LPWI Rx, IMM

Load word
`Rx = [IMM]`

### 0x81xy LDWI Rx, IMM

Load data word
`Rx = [IMM + 0x10000]`

### 0x82xy SPWI Rx, IMM

Store word
`[Rx] = IMM`

### 0x83xy SDWI Rx, IMM

Store data word
`[Rx + 0x10000] = IMM`

## Branch

### 0x90x0 JMP Rx

Jump
`R12 = R12 + Rx`

### 0x9100 JMPI IMM

Jump
`R12 = R12 + IMM`

### 0x92x0 JSR Rx

Jump to subroutine
`R13 = R13 + 1; R13 = Rx; R12 = Rx`

### 0x9300 JSRI IMM

Jump to subroutine
`R13 = R13 + 1; R12 = IMM; [R13] = R12`

### 0x9400 RET

Return from subroutine
`R13 = R13 - 1; R12 = [R13]`

## I/O

### 0xA0xy HWI Rx, Ry

Hardware interrupt to HWID Rx with argument Ry

### 0xA1x0 HWII Rx, IMM

Hardware interrupt to HWID Rx with argument IMM

## Other

### 0xB000 HLT

Halt CPU processing

### 0xB100 NOP

No operation