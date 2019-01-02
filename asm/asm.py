#!/usr/bin/python3

def get_ops(lines):
    ops = []
    for op in lines:
        op_toks = op.split(" ")


        mnem = None
        x   = None
        y   = None
        imm = None
        if op_toks > 0:
            mnem = op_toks[0]
        
        if len(op_toks) > 1:
            if op_toks[1].startswith("R"):
                x = int(op_toks[1].replace("R", "").replace(",", ""))
            else:
                imm = int(op_toks[1])
            
            if len(op_toks) > 2:
                if op_toks[2].startswith("R"):
                    y = int(op_toks[2].replace("R", "").replace(",", ""))
                else:
                    imm = int(op_toks[2])

            if len(op_toks) > 3:
                imm = int(op_toks[3])
        
        ops.append((mnem, x, y, imm))
    
    return ops

def get_bytecode(ops):
    bytecode = []

    for op in ops:
        co = op_map[op[0]]
        xy = 0
        if op[1] != None:
            if op[2] != None:
                xy = (op[1] << 4) | op[2]
            else:
                xy = op[1] << 4

        bytecode.append(co)
        bytecode.append(xy)
    
    return bytecode

def write_output(bytecode, outfile):
    outf = open(outfile, "wb")
    outf.write(bytearray(bytecode))
    outf.close()
    

def assemble(code, outfile):
    ops = get_ops(code.splitlines())

    bytecode = get_bytecode(ops)

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
    "HLT": 0xA0
}

if __name__ == "__main__":
    assemble("INC R0\nADD R1, R0\nHLT", "a.out")