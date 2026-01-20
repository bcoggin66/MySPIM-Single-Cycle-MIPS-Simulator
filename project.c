#include "spimcore.h"

// Brayden Coggin and Daniel Henriquez

/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch(ALUControl){
        // Z = A + B
        case 0:
            *ALUresult = A + B;
            break;
        // Z = A - B
        case 1:
            *ALUresult = A - B;
            break;
        // if A < B, Z = 1; otherwise, Z = 0
        case 2:
            *ALUresult = ((int)A < (int)B) ? 1 : 0;
            break;
        // if A < B, Z = 1; otherwise, Z = 0 (A and B are unsigned integers)
        case 3:
            *ALUresult = (A < B) ? 1 : 0;
            break;
        // Z = A AND B
        case 4:
            *ALUresult = A & B;
            break;
        // Z = A OR B
        case 5:
            *ALUresult = A | B;
            break;
        // Z = Shift B left by 16 bits
        case 6:
            *ALUresult = (B << 16);
            break;
        // Z = NOT A
        case 7:
            *ALUresult = ~A;
            break;
    }
    *Zero = (*ALUresult == 0);
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
    // Makes sure the PC is word aligned (mulitples of 4)
    if((PC % 4) != 0) {
        return 1;
    }

    // Convert PC from a byte address to a word index
    unsigned mem_index = PC >> 2;

    // Check that the index is inside the memory range
    if (mem_index >= 16384) {
        return 1;
    }

    // rfetch instructions
    *instruction = Mem[mem_index];

    return 0;
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    // first 6 bits [31-26] opcode
    *op = (instruction >> 26) & 0x3F;

    // instruction [25-21]  register rs
    *r1 = (instruction >> 21) & 0x1F;

    // instruction [20-16] register rt
    *r2 = (instruction >> 16) & 0x1F;

    // instruction [15-11] register rd
    *r3 = (instruction >> 11) & 0x1F;

    // bottom 6 bits [5-0] function code
    *funct = instruction & 0x3F;

    // bottom 16 bits [15-0] offset
    *offset = instruction & 0xFFFF;

    // bottom 26 bits [25-0] jump target
    *jsec = instruction & 0x3FFFFFF;

}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    // Set the vakues of all control signals to 0
    controls->RegDst   = 0;
    controls->Jump     = 0;
    controls->Branch   = 0;
    controls->MemRead  = 0;
    controls->MemtoReg = 0;
    controls->ALUOp    = 0;
    controls->MemWrite = 0;
    controls->ALUSrc   = 0;
    controls->RegWrite = 0;

    switch(op){
        // R type instructions opcode = 0
        case 0:
            controls->RegDst = 1;
            controls->RegWrite = 1;
            controls->ALUOp = 7;
            return 0;
        // load word opcode = 35
        case 35:
            controls->ALUSrc = 1;
            controls->MemRead = 1;
            controls->MemtoReg = 1;
            controls->RegWrite = 1;
            return 0;
        // store word opcode = 43
        case 43:
            controls->ALUSrc = 1;
            controls->MemWrite = 1;
            return 0;
        // beq opcode = 4
        case 4:
            controls->Branch = 1;
            controls->ALUOp = 1;
            return 0;
        // addi opcode = 8
        case 8:
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
            return 0;
        // slti opcode = 10
        case 10:
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
            controls->ALUOp = 2;
            return 0;
        //sltiu opcode = 11
        case 11:
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
            controls->ALUOp = 3;
            return 0;
        // lui opcode = 15
        case 15:
            controls->ALUSrc = 1;
            controls->RegWrite = 1;
            controls->ALUOp = 6;
            return 0;
        // jump opcode = 2
        case 2:
            controls->Jump = 1;
            return 0;
        default:
            return 1;
    }
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    // reads value stored in register r1
    *data1 = Reg[r1];

    // reads value stored in register r2
    *data2 = Reg[r2];
}

/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // check if the 16 bit value is negative (bit 15 = 1)
    if(offset & 0x8000){
        // Extend with 1's
        *extended_value = offset | 0xFFFF0000;
    }
    else{
        // Extend with 0's
        *extended_value = offset & 0xFFFF;
    }
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    unsigned B = (ALUSrc) ? extended_value : data2;
    unsigned ALUcontrol;

    switch(ALUOp){
        // add
        case 0:
            ALUcontrol = 0;
            break;
        // subtraction
        case 1:
            ALUcontrol = 1;
            break;
        // slt
        case 2:
            ALUcontrol = 2;
            break;
        // sltu
        case 3:
            ALUcontrol = 3;
            break;
        // and
        case 4:
            ALUcontrol = 4;
            break;
        // or
        case 5:
            ALUcontrol = 5;
            break;
        // lui
        case 6:
            ALUcontrol = 6;
            break;
        // R-type funct
        case 7:
            switch(funct){
                case 32:
                    ALUcontrol = 0;
                    break;
                case 34:
                    ALUcontrol = 1;
                    break;
                case 36:
                    ALUcontrol = 4;
                    break;
                case 37:
                    ALUcontrol = 5;
                    break;
                case 42:
                    ALUcontrol = 2;
                    break;
                case 43:
                    ALUcontrol = 3;
                    break;
                case 0:
                    ALUcontrol = 6;
                    break;
                default:
                    return 0;
            }
            break;
        default:
            return 0;
    }

    // Call the ALU
    ALU(data1, B, ALUcontrol, ALUresult, Zero);

    return 0;
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    // Memory address must be word aligned
    if ((MemRead || MemWrite) && (ALUresult % 4 != 0)) {
        return 1;
    }
    // Load word
    if (MemRead) {
        *memdata = Mem[ALUresult >> 2];
    }

    // Store word
    if (MemWrite) {
        Mem[ALUresult >> 2] = data2;
    }

    return 0;

}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    // Only write if RegWrite = 1
    if (!RegWrite) {
        return;
    }
    
    // chooses destination register r3 for Rtype r2 for Itype
    unsigned dest = (RegDst) ? r3 : r2;

    if (dest == 0 || dest >= 32) {
        return;
    }

    // choose value to write memory data for load word otherwise alu
    unsigned value = (MemtoReg) ? memdata : ALUresult;
    
    // stores the valye into register file
    Reg[dest] = value;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    // Go to next instruction
    *PC += 4;

    // Branch (beq)
    if (Branch && Zero) {
        *PC += (extended_value << 2);
    }

    // Jump
    if (Jump) {
        *PC = (*PC & 0xF0000000) | (jsec << 2);
    }
}

