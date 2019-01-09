#!/usr/bin/python3

import sys, getopt

helpers = [ "dw", "db", "ds", "def" ]
reserved_chars = [ ".", ",", "'", '"', "%", ":", ";" "=" ]
definitions = {
    "PC": "R13",
    "C": "R14"
}

op_map = {
    "ADD": 0x00,
    "ADDC": 0x01,
    "SUB": 0x02,
    "SUBC": 0x03,
    "RSB": 0x04,
    "RSBC": 0x05,
    "MUL": 0x06,
    "MULS": 0x07,
    "DIV": 0x08,
    "DIVS": 0x09,
    "MOD": 0x0A,
    "MODS": 0x0B,
    "MOV": 0x0C,
    "SHL": 0x10,
    "SHR": 0x11,
    "SHLS": 0x12,
    "SHRS": 0x13,
    "AND": 0x14,
    "OR": 0x15,
    "XOR": 0x16,
    "IFE": 0x20,
    "IFNE": 0x21,
    "IFLT": 0x22,
    "IFLE": 0x23,
    "IFGT": 0x24,
    "IFGE": 0x25,
    "IFLTS": 0x26,
    "IFLES": 0x27,
    "IFGTS": 0x28,
    "IFGES": 0x29,
    "LW": 0x30,
    "SW": 0x31,
    "HWI": 0x40,
    "HLT": 0x50
}

def get_charcodes(line):
    if "'" in line:
        index = line.index("'")
        charcode = ord(line[index + 1])
        line = line[0:index] + str(charcode) + line[index + 2:]
        line = line.replace("'", "")

    return line

def strip_code(lines):

    result = []

    for line in lines:
        line = line.strip()
        line = get_charcodes(line)
        result.append(line.split(";")[0])
    return result

def get_op(line, linenum, labels):
    op = []
    if line == "": 
        return
    if line.split(" ")[0] in op_map.keys():
        op.append(line.split(" ")[0])

        for tok in line.replace(",", "").split(" ")[1:]:
            if tok.startswith("0x"):
                op.append(int(tok.split("0x")[1].replace(",", ""), 16))
            elif tok.startswith("0b"):
                op.append(int(tok.split("0b")[1].replace(",", ""), 2))
            elif tok.startswith("0o"):
                op.append(int(tok.split("0o")[1].replace(",", ""), 8))
            elif tok.startswith("0d"):
                op.append(int(tok.split("0d")[1].replace(",", "")))
            elif tok.startswith("R"):
                op.append(tok.replace(",", ""))
            elif tok == "PC":
                op.append("R13")
            elif tok == "C":
                op.append("R14")
            elif tok.isdigit():
                op.append(int(tok.replace(",", "")))
            elif tok in labels.keys():
                op.append(labels[tok])
            else:
                print("Syntax error on line", linenum)
                print("Line:", line)
                exit()
    elif line[0] == ".":
        return None
    elif line[0] == "%":
        op.append(line[0].replace("%", ""))
        for tok in line.split(" ")[1:]:
            op.append(tok)
    elif line.split(" ")[0] in helpers:
        op.append(line.split(" ")[0])
        op.append(int(line.split(" ")[1]))
    elif line == "":
        pass
    else:
        print("Syntax error on line", linenum)
        exit()
    
    return op

def get_labels(lines, stack):
    index = stack
    labels = {}

    for line in lines:
        line = line.strip()

        if line.startswith("."):
            labels[line.replace(":", "").replace(".", "")] = index - 1
            print(str(index))
        elif line.startswith("%") or line == "":
            pass
        else:
            for tok in line.split(" "):
                if tok.isdigit() and not line.split(" ")[0] == "dw" and not line.split(" ")[0] == "db":
                    index += 1
                elif tok.isalpha():
                    index += 1

    
    return labels

def eval_src(code, stack):
    lines = strip_code(code)
    labels = get_labels(lines, stack)
    ops = []
    num = 1
    for line in lines:
        if get_op(line, num, labels) != None:
            ops.append(get_op(line, num, labels))
        num += 1
    return ops

def get_bytecode(ops, stack):
    bytecode = []

    for i in range(65536):
        bytecode.append(0)

    index = stack * 2
    for op in ops:
        if op[0] not in op_map.keys(): # Special ops
            if op[0] == 'dw':
                bytecode[index] = int((op[1] & 0xFF00) >> 8)
                index += 1
                bytecode[index] = int(op[1] & 0xFF)
                index += 1
            elif op[0] == 'db':
                index += 1
                bytecode[index] = int(op[1] & 0xFF)
                index += 1
            elif op[0] == 'ds':
                pass
        else:
            co = op_map[op[0]]
            xy = 0
            imm = None
            if len(op) > 1:
                if type(op[1]) == str:
                    if op[1].startswith("R"):
                        xy = int(op[1][1:]) << 4
                elif type(op[1]) == int:
                    xy = 0xF << 4
                    imm = op[1]
            if len(op) > 2:
                if type(op[2]) == str:
                    if op[2].startswith("R"):
                        xy |= int(op[2][1:])
                elif type(op[2]) == int:
                    xy |= 0xF
                    imm = op[2]
            bytecode[index] = co
            index += 1
            bytecode[index] = xy
            index += 1
            if imm != None:
                bytecode[index] = (imm & 0xFF00) >> 8
                index += 1
                bytecode[index] = imm & 0x00FF
                index += 1
            
    
    return bytecode
    
def write_output(bytecode, outfile):
    outf = open(outfile, "wb")
    outf.write(bytearray(bytecode))
    outf.close()
    

def assemble(code, outfile, stack):
    ops = eval_src(code, stack)

    bytecode = get_bytecode(ops, stack)

    write_output(bytecode, outfile)

def print_help():
    print("--- PROJECT0930 16 BIT ASSEMBLER --- ")
    print(" OPTIONS:")
    print(" -h, --help: Show this help menu")
    print(" -i, --input: Input file")
    print(" -o, --output: Output file")
    print(" -s, --stack: Stack size")

if __name__ == "__main__":
    opts, args = getopt.getopt(sys.argv[1:], "hi:o:s:", ["help", "input", "output", "stack"])

    inf = 'a.s'
    outf = 'a.out'
    stack = 0

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