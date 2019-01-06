#!/usr/bin/python3

import sys, getopt

def get_labels(lines, stack):
    index = stack
    labels = {}

    for line in lines:
        line = line.strip()

        if not line.startswith(";") and not line == "":

            if ";" in line:
                op_toks = line.split(";")[0].replace(";", "")

            if line.split(" ")[0][len(line.split(" ")[0]) - 1] == "I" and not line.split(" ")[0] == "HWI":
                index += 1

            if line.endswith(":"):
                labels[line.replace(":", "")] = index
            else:
                index += 1

    
    return labels

def get_ops(lines, labels):
    ops = []
    for line in lines:
        line = line.strip()

        if not line.startswith(";") and not line == "":

            if ";" in line:
                op_toks = line.split(";")[0].replace(";", "")

            op_toks = line.split(" ")

            caught = False

            mnem = None
            x   = None
            y   = None
            mem = None
            imm = None

            tok0 = 0
            tok1 = 1
            tok2 = 2
            tok3 = 3

            if len(op_toks) > tok0:
                mnem = op_toks[0]
            
            if len(op_toks) > tok1:
                if op_toks[1].startswith("R"):
                    x = int(op_toks[1].replace("R", "").replace(",", ""))
                elif op_toks[1].startswith("#"):
                    imm = int(op_toks[1].replace("#", "").replace(",", ""))
                elif op_toks[1].startswith("$"):
                    imm = int(op_toks[1].replace("$", "").replace(",", ""))
                elif op_toks[1].startswith('\'') and op_toks[1].endswith('\''):
                    if op_toks[1] == "'":
                        imm = ord(' ')
                        tok2 += 1
                    else:
                        imm = ord(op_toks[1][1])
                elif op_toks[1] in labels:
                    imm = labels[op_toks[1].replace(":", "")]
                
                if len(op_toks) > tok2:
                    if op_toks[2].startswith("R"):
                        y = int(op_toks[2].replace("R", "").replace(",", ""))
                    elif op_toks[2].startswith("#"):
                        imm = int(op_toks[2].replace("#", "").replace(",", ""))
                    elif op_toks[2].startswith('\'') and op_toks[2].endswith('\''):
                        if op_toks[2] == "'":
                            imm = ord(' ')
                            tok3 += 1
                        else:
                            imm = ord(op_toks[2][1])

                    elif op_toks[2] in labels:
                        imm = labels[op_toks[2].replace(":", "")]
                if len(op_toks) > tok3:
                    if op_toks[3].startswith("#"):
                        imm = int(op_toks[3].replace("#", "").replace(",", ""))
                    elif op_toks[3].startswith("$"):
                        imm = int(op_toks[3].replace("$", "").replace(",", ""))
                    elif op_toks[3].startswith('\'') and op_toks[3].endswith('\''):
                        if op_toks[3] == "'":
                            imm = ord(' ')
                        else:
                            imm = ord(op_toks[3][1])
            
            ops.append((mnem, x, y, imm))
    
    return ops

def get_bytecode(ops, stack):
    bytecode = []

    for i in range(65536 * 2):
        bytecode.append(op_map["NOP"])
        bytecode.append(0)

    index = stack * 2
    for op in ops:
        if op[0] not in op_map: # Special ops
            if op[0] == 'dw':
                bytecode[index] = int((op[3] & 0xFF00) >> 8)
                index += 1
                bytecode[index] = int(op[3] & 0x00FF)
                index += 1
        else:
            co = op_map[op[0]]
            xy = 0
            imm = op[3]
            if op[1] != None:
                if op[2] != None:
                    xy = (op[1] << 4) | op[2]
                else:
                    xy = op[1] << 4

            bytecode[index] = co
            index += 1
            bytecode[index] = xy
            index += 1
            if imm != None:
                bytecode[index] = ((imm & 0xFF00) >> 8)
                index += 1
                bytecode[index] = (imm & 0x00FF)
                index += 1
            
    
    return bytecode

def write_output(bytecode, outfile):
    outf = open(outfile, "wb")
    outf.write(bytearray(bytecode))
    outf.close()
    

def assemble(code, outfile, stack):
    labels = get_labels(code, stack)
    ops = get_ops(code, labels)

    bytecode = get_bytecode(ops, stack)

    write_output(bytecode, outfile)

op_map = {
    "ADD": 0x00,
    "ADC": 0x01,
    "SUB": 0x02,
    "SBC": 0x03,
    "RSB": 0x04,
    "RBC": 0x05,
    "MUL": 0x06,
    "MLS": 0x07,
    "DIV": 0x08,
    "DVS": 0x09,
    "MOD": 0x0A,
    "MDS": 0x0B,
    "MOV": 0x0C,
    "INC": 0x0D,
    "DEC": 0x0E,
    "CLR": 0x0F,
    "SAL": 0x10,
    "SAR": 0x11,
    "SLS": 0x12,
    "SRS": 0x13,
    "AND": 0x14,
    "IOR": 0x15,
    "NOT": 0x16,
    "XOR": 0x17,
    "ADDI": 0x20,
    "ADCI": 0x21,
    "SUBI": 0x22,
    "SBCI": 0x23,
    "RSBI": 0x24,
    "RBCI": 0x25,
    "MULI": 0x26,
    "MLSI": 0x27,
    "DIVI": 0x28,
    "DVSI": 0x29,
    "MODI": 0x2A,
    "MDSI": 0x2B,
    "MOVI": 0x2C,
    "SALI": 0x30,
    "SARI": 0x31,
    "SLSI": 0x32,
    "SRSI": 0x33,
    "ANDI": 0x34,
    "IORI": 0x35,
    "NOTI": 0x36,
    "XORI": 0x37,
    "IFE": 0x40,
    "IFN": 0x41,
    "IFL": 0x42,
    "IFLE": 0x43,
    "IFG": 0x44,
    "IFGE": 0x45,
    "IFLS": 0x46,
    "IFLES": 0x47,
    "IFGS": 0x48,
    "IFGES": 0x49,
    "LPH": 0x50,
    "LPL": 0x51,
    "LDH": 0x52,
    "LDL": 0x53,
    "SPH": 0x54,
    "SPL": 0x55,
    "SDH": 0x56,
    "SDL": 0x57,
    "CPH": 0x58,
    "CPL": 0x59,
    "CDH": 0x5A,
    "CDL": 0x5B,
    "LPW": 0x60,
    "LDW": 0x61,
    "SPW": 0x62,
    "SDW": 0x63,
    "CPW": 0x64,
    "CDW": 0x65,
    "LPHI": 0x70,
    "LPLI": 0x71,
    "LDHI": 0x72,
    "LDLI": 0x73,
    "SPHI": 0x74,
    "SPLI": 0x75,
    "SDHI": 0x76,
    "SDLI": 0x77,
    "CPHI": 0x78,
    "CPLI": 0x79,
    "CDHI": 0x7A,
    "CDLI": 0x7B,
    "LPWI": 0x80,
    "LDWI": 0x81,
    "SPWI": 0x82,
    "SDWI": 0x83,
    "JMP": 0x90,
    "JMPI": 0x91,
    "JSR": 0x92,
    "JSRI": 0x93,
    "RET": 0x94,
    "HWI": 0xA0,
    "HWII": 0xA1,
    "HLT": 0xB0,
    "NOP": 0xB1
}

def print_help():
    print("--- PROJECT0930 16 BIT ASSEMBLER --- ")
    print(" OPTIONS:")
    print(" -h, --help: Show this help menu")
    print(" -i, --input: Input file")
    print(" -o, --output: Output file")
    print(" -s, --stack: Stack size")

if __name__ == "__main__":
    opts, args = getopt.getopt(sys.argv[1:], "hi:o:s:", ["help", "input", "output", "stack"])

    inf = 't'
    outf = 'a.out'
    stack = 64

    for o, a in opts:
        if o in ("-i", "--input"):
            inf = a
        elif o in ("-o", "--output"):
            outf = a
        elif o in ("-s", "--stack"):
            stack = int(a)
        elif o in ("-h", "--help"):
            print_help()
            exit(0)

    infile = open(inf)

    assemble(infile.readlines(), outf, stack)