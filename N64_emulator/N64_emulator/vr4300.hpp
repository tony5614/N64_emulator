#pragma once

//general
typedef unsigned char       U8;
typedef unsigned short      U16;
typedef unsigned int        U32;
typedef unsigned long long  U64;

#define BIT(x)                       (0x1 << (x))



typedef union instruction
{
    U32 all;

    //immediate type
    struct 
    {
        U32 immediate : 16;
        U32 rt : 5;
        U32 rs : 5;
        U32 op : 6;
    }i_type;

    //jump type
    struct 
    {
        U32 target : 26;
        U32 op : 6;
    }j_type;

    //register type
    struct 
    {
        U32 funct : 6;
        U32 sa : 5;
        U32 rd : 5;
        U32 rt : 5;
        U32 rs : 5;
        U32 op : 6;
    }r_type;
    
}INSTRUCTION, *INSTRUCTION_PTR;




class CPU 
{
public:
    void main_loop() 
    {

        INSTRUCTION_PTR instruct;
        switch (instruct->i_type.op)
        {
            case 0x0:     //register type
                switch (instruct->r_type.funct)
                {
                case 0x20:     //ADD
                    break;
                case 0x21:     //ADDU
                    break;
                case 0x24:     //AND
                    break;
                case 0x27:     //NOR
                    break;
                case 0x25:     //OR
                    break;
                case 0x2A:     //SLT
                    break;
                case 0x2B:     //SLTU
                    break;
                case 0x22:     //SUB
                    break;
                case 0x23:     //SUBU
                    break;
                case 0x26:     //XOR
                    break;
                case 0x00:     //SLL
                    break;
                case 0x04:     //SLLV 
                    break;
                case 0x03:     //SRA
                    break;
                case 0x07:     //SRAV
                    break;
                case 0x02:     //SRL 
                    break;
                case 0x06:     //SRLV 
                    break;
                case 0x1A:     //DIV
                    break;
                case 0x1B:     //DIVU
                    break;
                case 0x10:     //MFHI
                    break;
                case 0x12:     //MFLO
                    break;
                case 0x11:     //MTHI 
                    break;
                case 0x13:     //MTLO
                    break;
                case 0x18:     //MULT 
                    break;
                case 0x19:     //MULTU
                    break;
                case 0x0D:     //BREAK
                    break;
                case 0x09:     //JALR
                    break;
                case 0x08:     //JR
                    break;
                case 0x0C:     //SYSCALL
                    break;
                }
            break;
        }
    }
    //load and store instruction
    void LBU();
    void LH();
    void LHU();
    void LW();
    void LWL();
    void LWR();
    void SB();
    void SH();
    void SW();
    void SWL();
    void SWR();
    void LD();
    void LDL();
    void LDR();
    void LL();
    void LLD();
    void LWU();
    void SC();
    void SCD();
    void SD();
    void SDL();
    void SDR();
    void SYNC();

    //arithmetic instruction
    void ADD();
    void ADDI();
    void ADDIU();
    void ADDU();
    void AND();
    void ANDI();
    void DADD();
    void DADDI();
    void DADDIU();
    void DADDU();
    void DDIV();
    void DDIVU();
    void DIV();
    void DIVU();
    void DMULT();
    void DMULTU();
    void DSLL();
    void DSLL32();
    void DSLLV();
    void DSRA();
    void DSRA32();
    void DSRAV();
    void DSRL();
    void DSRL32();
    void DSRLV();
    void DSUB();
    void DSUBU();
    void LUI();
    void MFHI();
    void MFLO();
    void MTHI();
    void MTLO();
    void MULT();
    void MULTU();
    void NOR();
    void OR();
    void ORI();
    void SLL();
    void SLLV();
    void SLT();
    void SLTI();
    void SLTIU();
    void SLTU();
    void SRA();
    void SRAV();
    void SRL();
    void SRLV();
    void SUB();
    void SUBU();
    void XOR();
    void XORI();


    //Jump and Branch Instructions
    void BEQ();
    void BEQL();
    void BGEZ();
    void BGEZAL();
    void BGEZALL();
    void BGEZL();
    void BGTZ();
    void BGTZL();
    void BLEZ();
    void BLEZL();
    void BLTZ();
    void BLTZAL();
    void BLTZALL();
    void BLTZL();
    void BNE();
    void BNEL();
    void J();
    void JAL();
    void JALR();
    void JR();


    //Special Instructions
    void BREAK();
    void SYSCALL();


    //Exception Instructions
    void TEQ();
    void TEQI();
    void TGE();
    void TGEI();
    void TGEIU();
    void TGEU();
    void TLT();
    void TLTI();
    void TLTIU();
    void TLTU();
    void TNE();
    void TNEI();

};

