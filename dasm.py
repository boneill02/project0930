#!/usr/bin/python3

import sys, getopt

def write_output(code, outfile):
    outf = open(outfile, "w")
    outf.write(code)
    outf.close()

def has_immediate(op):
    op = op_map[(op & 0xFF00) >> 8]
    if op.endswith("I") and op != "HWI":
        return True
    return False

def parse_op(op, imm):
    out = op_map[(op & 0xFF00) >> 8]
    if out == "HLT":
        return out + "\n"
    elif out == "NOP":
        return ""
    else:
        out += " R" + str((op & 0x00F0) >> 4) + ","
        out += " R" + str(op & 0x000F)
        if has_immediate(op):
            out += ", #" + str(imm)
    return out + "\n"

def disassemble(bytecode, outfile):
    op = 0
    imm = 0
    output = ""
    i = 0
    while i < len(bytecode) - 4:
        op = int(bytecode[i])
        i += 1
        op = (op << 8) | int(bytecode[i])
        i += 1
        if has_immediate(op):
            imm = int(bytecode[i])
            i += 1
            imm = (imm << 8) | int(bytecode[i])
            i += 1
        if op != 0:
            output += parse_op(op, imm)

    write_output(output, outfile)

op_map = {
    0x00: "ADD",
    0x01: "ADC",
    0x02: "SUB",
    0x03: "SBC",
    0x04: "RSB",
    0x05: "RBC",
    0x06: "MUL",
    0x07: "MLS",
    0x08: "DIV",
    0x09: "DVS",
    0x0A: "MOD",
    0x0B: "MDS",
    0x0C: "MOV",
    0x0D: "INC",
    0x0E: "DEC",
    0x0F: "CLR",
    0x10: "SAL",
    0x11: "SAR",
    0x12: "SLS",
    0x13: "SRS",
    0x14: "AND",
    0x15: "IOR",
    0x16: "NOT",
    0x17: "XOR",
    0x20: "ADDI",
    0x21: "ADCI",
    0x22: "SUBI",
    0x23: "SBCI",
    0x24: "RSBI",
    0x25: "RBCI",
    0x26: "MULI",
    0x27: "MLSI",
    0x28: "DIVI",
    0x29: "DVSI",
    0x2A: "MODI",
    0x2B: "MDSI",
    0x2C: "MOVI",
    0x30: "SALI",
    0x31: "SARI",
    0x32: "SLSI",
    0x33: "SRSI",
    0x34: "ANDI",
    0x35: "IORI",
    0x36: "NOTI",
    0x37: "XORI",
    0x40: "IFE",
    0x41: "IFN",
    0x42: "IFL",
    0x43: "IFLE",
    0x44: "IFG",
    0x45: "IFGE",
    0x46: "IFLS",
    0x47: "IFLES",
    0x48: "IFGS",
    0x49: "IFGES",
    0x50: "LPH",
    0x51: "LPL",
    0x52: "LDH",
    0x53: "LDL",
    0x54: "SPH",
    0x55: "SPL",
    0x56: "SDH",
    0x57: "SDL",
    0x58: "CPH",
    0x59: "CPL",
    0x5A: "CDH",
    0x5B: "CDL",
    0x60: "LPW",
    0x61: "LDW",
    0x62: "SPW",
    0x63: "SDW",
    0x64: "CPW",
    0x65: "CDW",
    0x70: "LPHI",
    0x71: "LPLI",
    0x72: "LDHI",
    0x73: "LDLI",
    0x74: "SPHI",
    0x75: "SPLI",
    0x76: "SDHI",
    0x77: "SDLI",
    0x78: "CPHI",
    0x79: "CPLI",
    0x7A: "CDHI",
    0x7B: "CDLI",
    0x80: "LPWI",
    0x81: "LDWI",
    0x82: "SPWI",
    0x83: "SDWI",
    0x90: "JMP",
    0x91: "JMPI",
    0x92: "JSR",
    0x93: "JSRI",
    0x94: "RET",
    0xA0: "HWI",
    0xA1: "HWII",
    0xB0: "HLT",
    0xB1: "NOP"
}

def print_help():
    print("--- PROJECT0930 16 BIT DISASSEMBLER --- ")
    print(" OPTIONS:")
    print(" -h, --help: Show this help menu")
    print(" -i, --input: Input file")
    print(" -o, --output: Output file")

if __name__ == "__main__":
    opts, args = getopt.getopt(sys.argv[1:], "hi:o:", ["help", "input", "output"])

    inf = 'a.out'
    outf = 'a.s'

    for o, a in opts:
        if o in ("-i", "--input"):
            inf = a
        elif o in ("-o", "--output"):
            outf = a
        elif o in ("-h", "--help"):
            print_help()
            exit(0)

    infile = open(inf, "rb")

    disassemble(infile.read(), outf)
    infile.close()