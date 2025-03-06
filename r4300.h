#pragma once
#include "common.h"
#include "stdio.h"
#include <stdlib.h>
#include <iostream>
#include "fstream"
#include <sstream>
#include <iomanip>
#include <string>

//opcode

typedef union instruction
{
	U32 all;

	//immediate type
	struct
	{
		union 
		{
			U32 immediate : 16;
			U32 offset : 16;
		};
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






class MEMORY 
{
public:
	U8 raw_data[4096];
	U8 &operator[](U32 addr) 
	{
		//mapping
		if (addr > 0x80000000) 
		{	
			addr -= 0x80000000;
		}
		return this->raw_data[addr];
	}
};

class R4300
{
public:
	//registers
	void run();
	void decode(U32 instruction);

	U32 PC;
	U32 sr; //status register
	U32 cr; //cause register
	U32 GPR[32];
    U32 HI,LO;
	U32 EPC; //exception program counter

	MEMORY memory;


	void read_rom(std::string filename);


	void ADD(INSTRUCTION_PTR inst);
	void ADDI(INSTRUCTION_PTR inst);
	void ADDIU(INSTRUCTION_PTR inst);
	void ADDU(INSTRUCTION_PTR inst);
	void AND(INSTRUCTION_PTR inst);
	void ANDI(INSTRUCTION_PTR inst);
	void DADD(INSTRUCTION_PTR inst);
	void DADDI(INSTRUCTION_PTR inst);
	void DADDIU(INSTRUCTION_PTR inst);
	void DADDU(INSTRUCTION_PTR inst);
	void DDIV(INSTRUCTION_PTR inst);
	void DDIVU(INSTRUCTION_PTR inst);
	void DIV(INSTRUCTION_PTR inst);
	void DIVU(INSTRUCTION_PTR inst);
	void DMULT(INSTRUCTION_PTR inst);
	void DMULTU(INSTRUCTION_PTR inst);
	void DSLL(INSTRUCTION_PTR inst);
	void DSLL32(INSTRUCTION_PTR inst);
	void DSLLV(INSTRUCTION_PTR inst);
	void DSRA(INSTRUCTION_PTR inst);
	void DSRA32(INSTRUCTION_PTR inst);
	void DSRAV(INSTRUCTION_PTR inst);
	void DSRL(INSTRUCTION_PTR inst);
	void DSRL32(INSTRUCTION_PTR inst);
	void DSRLV(INSTRUCTION_PTR inst);
	void DSUB(INSTRUCTION_PTR inst);
	void DSUBU(INSTRUCTION_PTR inst);
	void LUI(INSTRUCTION_PTR inst);
	void MFHI(INSTRUCTION_PTR inst);
	void MFLO(INSTRUCTION_PTR inst);
	void MTHI(INSTRUCTION_PTR inst);
	void MTLO(INSTRUCTION_PTR inst);
	void MULT(INSTRUCTION_PTR inst);
	void MULTU(INSTRUCTION_PTR inst);
	void NOR(INSTRUCTION_PTR inst);
	void OR(INSTRUCTION_PTR inst);
	void ORI(INSTRUCTION_PTR inst);
	void SLL(INSTRUCTION_PTR inst);
	void SLLV(INSTRUCTION_PTR inst);
	void SLT(INSTRUCTION_PTR inst);
	void SLTI(INSTRUCTION_PTR inst);
	void SLTIU(INSTRUCTION_PTR inst);
	void SLTU(INSTRUCTION_PTR inst);
	void SRA(INSTRUCTION_PTR inst);
	void SRAV(INSTRUCTION_PTR inst);
	void SRL(INSTRUCTION_PTR inst);
	void SRLV(INSTRUCTION_PTR inst);
	void SUB(INSTRUCTION_PTR inst);
	void SUBU(INSTRUCTION_PTR inst);
	void XOR(INSTRUCTION_PTR inst);
	void XORI(INSTRUCTION_PTR inst);


	void BEQ(INSTRUCTION_PTR inst);
	void BEQL(INSTRUCTION_PTR inst);
	void BGEZ(INSTRUCTION_PTR inst);
	void BGEZAL(INSTRUCTION_PTR inst);
	void BGEZALL(INSTRUCTION_PTR inst);
	void BGEZL(INSTRUCTION_PTR inst);
	void BGTZ(INSTRUCTION_PTR inst);
	void BGTZL(INSTRUCTION_PTR inst);
	void BLEZ(INSTRUCTION_PTR inst);
	void BLEZL(INSTRUCTION_PTR inst);
	void BLTZ(INSTRUCTION_PTR inst);
	void BLTZAL(INSTRUCTION_PTR inst);
	void BLTZALL(INSTRUCTION_PTR inst);
	void BLTZL(INSTRUCTION_PTR inst);
	void BNE(INSTRUCTION_PTR inst);
	void BNEL(INSTRUCTION_PTR inst);
	void J(INSTRUCTION_PTR inst);
	void JAL(INSTRUCTION_PTR inst);
	void JALR(INSTRUCTION_PTR inst);
	void JR(INSTRUCTION_PTR inst);

	void LB    (INSTRUCTION_PTR inst);
	void LBU   (INSTRUCTION_PTR inst);
	void LD    (INSTRUCTION_PTR inst);
	void LDL   (INSTRUCTION_PTR inst);
	void LDR   (INSTRUCTION_PTR inst);
	void LH    (INSTRUCTION_PTR inst);
	void LHU   (INSTRUCTION_PTR inst);
	void LL    (INSTRUCTION_PTR inst);
	void LLD   (INSTRUCTION_PTR inst);
	void LW    (INSTRUCTION_PTR inst);
	void LWL   (INSTRUCTION_PTR inst);
	void LWR   (INSTRUCTION_PTR inst);
	void LWU   (INSTRUCTION_PTR inst);
	void SB    (INSTRUCTION_PTR inst);
	void SC    (INSTRUCTION_PTR inst);
	void SCD   (INSTRUCTION_PTR inst);
	void SD    (INSTRUCTION_PTR inst);
	void SDL   (INSTRUCTION_PTR inst);
	void SDR   (INSTRUCTION_PTR inst);
	void SH    (INSTRUCTION_PTR inst);
	void SW    (INSTRUCTION_PTR inst);
	void SWL   (INSTRUCTION_PTR inst);
	void SWR   (INSTRUCTION_PTR inst);
	void SYNC  (INSTRUCTION_PTR inst);









	void BREAK(INSTRUCTION_PTR inst);
	void SYSCALL(INSTRUCTION_PTR inst);
};