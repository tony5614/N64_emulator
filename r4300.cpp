#include "r4300.h"

void R4300::run()
{
	INSTRUCTION inst = (INSTRUCTION)this->memory(this->PC);
	while (true) 
	{
		this->decode(&inst);
		
	}
}
void R4300::decode(INSTRUCTION *inst)
{
	switch (inst->i_type.op)
	{
	case 0x0:     //register type special
		(this->*r_type_special_fp[inst->r_type.funct])(inst);
		break;
	case 0x1:     //REGIMM  
		switch (inst->i_type.rt)
		{
		case 0x00:
			this->BGEZ(inst);
			break;
		case 0x01:
			this->BGEZAL(inst);
			break;
		case 0x10:
			this->BLTZ(inst);
			break;
		case 0x11:
			this->BLTZAL(inst);
			break;
		}
		break;
		defualt:
		(this->*r_type_special_fp[inst->r_type.funct])(inst);
		break;
	}

}


R4300::R4300() 
{
	this->PC = 0x80246000;

	this->r_type_special_fp[0] = &R4300::SLL;
	this->r_type_special_fp[2] = &R4300::SRL;
	this->r_type_special_fp[3] = &R4300::SRA;
	this->r_type_special_fp[4] = &R4300::SLLV;
	this->r_type_special_fp[6] = &R4300::SRLV;
	this->r_type_special_fp[7] = &R4300::SRAV;
	this->r_type_special_fp[8] = &R4300::JR;
	this->r_type_special_fp[9] = &R4300::JALR;
	this->r_type_special_fp[13] = &R4300::BREAK;
	this->r_type_special_fp[32] = &R4300::ADD;
	this->r_type_special_fp[33] = &R4300::ADDU;
	this->r_type_special_fp[34] = &R4300::SUB;
	this->r_type_special_fp[35] = &R4300::SUBU;
	this->r_type_special_fp[36] = &R4300::AND;
	this->r_type_special_fp[37] = &R4300::OR;
	this->r_type_special_fp[38] = &R4300::XOR;
	this->r_type_special_fp[39] = &R4300::NOR;
	this->r_type_special_fp[42] = &R4300::SLT;
	this->r_type_special_fp[43] = &R4300::SLTU;

	this->r_type_special_fp[2] = &R4300::J;
	this->r_type_special_fp[3] = &R4300::JAL;
	this->r_type_special_fp[4] = &R4300::BEQ;
	this->r_type_special_fp[5] = &R4300::BNE;
	this->r_type_special_fp[6] = &R4300::BLEZ;
	this->r_type_special_fp[7] = &R4300::BGTZ;
	this->r_type_special_fp[8] = &R4300::ADDI;
	this->r_type_special_fp[9] = &R4300::ADDIU;
	this->r_type_special_fp[10] = &R4300::SLTI;
	this->r_type_special_fp[11] = &R4300::SLTIU;
	this->r_type_special_fp[12] = &R4300::ANDI;
	this->r_type_special_fp[13] = &R4300::ORI;
	this->r_type_special_fp[14] = &R4300::XORI;
	this->r_type_special_fp[15] = &R4300::LUI;
	this->r_type_special_fp[32] = &R4300::LB;
	this->r_type_special_fp[33] = &R4300::LH;
	this->r_type_special_fp[35] = &R4300::LW;
	this->r_type_special_fp[36] = &R4300::LBU;
	this->r_type_special_fp[37] = &R4300::LHU;
	this->r_type_special_fp[40] = &R4300::SB;
	this->r_type_special_fp[41] = &R4300::SH;
	this->r_type_special_fp[43] = &R4300::SW;
}

void R4300::read_rom(std::string filename)
{
	std::ifstream fin;
	fin.open(filename.c_str(), std::ios::in | std::ios::binary);
	if (!fin.is_open()) {
		printf("Failed to open file: %s\n", filename.c_str());
		return;
	}

	printf("Opened\n");

	fin.read(reinterpret_cast<char*>(this->memory.raw_data), 4096);

	std::streamsize bytesRead = fin.gcount();

	printf("%02X %02X %02X %02X\n", this->memory.raw_data[0], this->memory.raw_data[1], this->memory.raw_data[2], this->memory.raw_data[3]);


	fin.close();
}

void R4300::ADD(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] + this->GPR[inst->r_type.rt];
}

void R4300::ADDI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] + this->GPR[inst->i_type.immediate];
}

void R4300::ADDIU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] + this->GPR[inst->i_type.immediate];
}

void R4300::ADDU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] + this->GPR[inst->r_type.rt];
}

void R4300::AND(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] & this->GPR[inst->r_type.rt];
}

void R4300::ANDI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] & inst->i_type.immediate;
}

void R4300::DADD(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DADDI(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DADDIU(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DADDU(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DDIV(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::NOR(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = ~(this->GPR[inst->r_type.rs] | this->GPR[inst->r_type.rt]);
}

void R4300::OR(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] | this->GPR[inst->r_type.rt];
}

void R4300::ORI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] | inst->i_type.immediate;
}

void R4300::SLT(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] < this->GPR[inst->r_type.rt];
}

void R4300::SLTI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] < inst->i_type.immediate;
}

void R4300::SLTIU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] < inst->i_type.immediate;
}

void R4300::SLTU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] < this->GPR[inst->r_type.rt];
}

void R4300::SUB(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] - this->GPR[inst->r_type.rt];
}

void R4300::SUBU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] - this->GPR[inst->r_type.rt];
}

void R4300::XOR(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] ^ this->GPR[inst->r_type.rt];
}

void R4300::XORI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->GPR[inst->i_type.rs] ^ inst->i_type.immediate;
}

void R4300::SLL(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] << inst->r_type.sa;
}

void R4300::SLLV(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] << this->GPR[inst->r_type.rt];
}

void R4300::SRA(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] >> inst->r_type.sa;
}

void R4300::SRAV(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] >> this->GPR[inst->r_type.rt];
}

void R4300::SRL(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] >> inst->r_type.sa;
}

void R4300::SRLV(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->GPR[inst->r_type.rs] >> this->GPR[inst->r_type.rt];
}

void R4300::DDIVU(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DIV(INSTRUCTION_PTR inst)
{
	this->HI = this->GPR[inst->r_type.rs] % this->GPR[inst->r_type.rt];
	this->LO = this->GPR[inst->r_type.rs] / this->GPR[inst->r_type.rt];
}

void R4300::DIVU(INSTRUCTION_PTR inst)
{
	this->HI = this->GPR[inst->r_type.rs] % this->GPR[inst->r_type.rt];
	this->LO = this->GPR[inst->r_type.rs] / this->GPR[inst->r_type.rt];
}

void R4300::DMULT(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DMULTU(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSLL(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSLL32(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSLLV(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRA(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRA32(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRAV(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRL(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRL32(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSRLV(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSUB(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::DSUBU(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::LUI(INSTRUCTION_PTR inst)
{
this->GPR[inst->i_type.rt] =  inst->i_type.immediate << 16;
}

void R4300::MFHI(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->HI;
}

void R4300::MFLO(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->HI;
}

void R4300::MTHI(INSTRUCTION_PTR inst)
{
	this->HI = this->GPR[inst->r_type.rs];
}

void R4300::MTLO(INSTRUCTION_PTR inst)
{
	this->LO = this->GPR[inst->r_type.rs];
}

void R4300::MULT(INSTRUCTION_PTR inst)
{
	U64 product = (U64)this->GPR[inst->r_type.rs] * (U64)this->GPR[inst->r_type.rt];
    this->HI = product >> 32;
    this->LO = (U32)product;
}

void R4300::MULTU(INSTRUCTION_PTR inst)
{
	U64 product = (U64)this->GPR[inst->r_type.rs] * (U64)this->GPR[inst->r_type.rt];
    this->HI = product >> 32;
    this->LO = (U32)product;
}

void R4300::BREAK(INSTRUCTION_PTR inst)
{
	this->EPC = this->PC;
	this->PC = 0x3C;
}

void R4300::BEQ(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] == this->GPR[inst->i_type.rt]) 
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BEQL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] == this->GPR[inst->i_type.rt])
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGEZ(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] >= 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGEZAL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] >= 0)
	{
		this->GPR[31] = this->PC;
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGEZALL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] >= 0)
	{
		this->GPR[31] = this->PC;
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGEZL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] >= 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGTZ(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] > 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BGTZL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] > 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLEZ(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] <= 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLEZL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] <= 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLTZ(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] < 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLTZAL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] < 0)
	{
		this->GPR[31] = this->PC;
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLTZALL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] < 0)
	{
		this->GPR[31] = this->PC;
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BLTZL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] < 0)
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BNE(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs]!= this->GPR[inst->i_type.rt])
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::BNEL(INSTRUCTION_PTR inst)
{
	if (this->GPR[inst->i_type.rs] != this->GPR[inst->i_type.rt])
	{
		this->PC += inst->i_type.immediate * 4;
	}
}

void R4300::J(INSTRUCTION_PTR inst)
{
	this->PC &= 0xF0000000;
	this->PC |= this->GPR[inst->j_type.target] << 2;
}

void R4300::JAL(INSTRUCTION_PTR inst)
{
	this->GPR[31] = this->PC;
	this->PC &= 0xF0000000;
	this->PC |= this->GPR[inst->j_type.target] << 2;
}

void R4300::JALR(INSTRUCTION_PTR inst)
{
	this->GPR[inst->r_type.rd] = this->PC;
	this->PC = this->GPR[inst->r_type.rs];
}

void R4300::JR(INSTRUCTION_PTR inst)
{
	this->PC = this->GPR[inst->r_type.rs];
}

void R4300::LB(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = (U8)(this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset]);
}

void R4300::LBU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = (U8)(this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset]);
}

void R4300::LD(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::LDL(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::LDR(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::LH(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = (U16)(this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset]);
}

void R4300::LHU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = (U16)(this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset]);
}

void R4300::LL(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset];
}

void R4300::LLD(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::LW(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset];
}

void R4300::LWL(INSTRUCTION_PTR inst)
{
	U32 addr = this->GPR[inst->i_type.rs] + inst->i_type.offset;
	U32 word_addr = addr & ~0x3;  // 計算對齊的 4-byte 地址
	U32 word = this->memory[word_addr]; // 讀取 32-bit 數據

	int shift = (3 - (addr & 0x3)) * 8;  // 計算左移位數（大端序）
	U32 mask = 0xFFFFFFFF << shift; // 產生覆蓋高位的掩碼

									// 只修改高位，低位保持原值
	this->GPR[inst->i_type.rt] = (word << shift) | (this->GPR[inst->i_type.rt] & ~mask);
}

void R4300::LWR(INSTRUCTION_PTR inst) 
{
	U32 addr = this->GPR[inst->i_type.rs] + inst->i_type.offset;
	U32 word_addr = addr & ~0x3;  // 取得 4-byte 對齊的地址
	U32 word = this->memory[word_addr]; // 讀取 32-bit 數據

	int shift = (addr & 0x3) * 8;  // 計算右移位數（大端序）
	U32 mask = 0xFFFFFFFF >> shift; // 產生覆蓋低位的掩碼

									// 只修改低位，高位保持原值
	this->GPR[inst->i_type.rt] = (word >> shift) | (this->GPR[inst->i_type.rt] & ~mask);
}

void R4300::LWU(INSTRUCTION_PTR inst)
{
	this->GPR[inst->i_type.rt] = this->memory[this->GPR[inst->i_type.immediate] + inst->i_type.offset];
}

void R4300::SB(INSTRUCTION_PTR inst)
{
	this->memory[this->GPR[inst->i_type.immediate] +inst->i_type.offset]  &= 0xFFFFFF00;
	this->memory[this->GPR[inst->i_type.immediate] +inst->i_type.offset] |= (U8)this->GPR[inst->i_type.rt];
}

void R4300::SC(INSTRUCTION_PTR inst)
{
	this->memory[this->GPR[inst->i_type.rs] +inst->i_type.offset] = this->GPR[inst->i_type.rt];
	this->GPR[inst->i_type.rt] = 1;
}

void R4300::SCD(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
	this->memory[this->GPR[inst->i_type.rs] +inst->i_type.offset] = this->GPR[inst->i_type.rt];
	this->GPR[inst->i_type.rt] = 1;
}

void R4300::SD(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::SDL(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::SDR(INSTRUCTION_PTR inst)
{
	ASSERT(__FUNCTION__, 0);
}

void R4300::SH(INSTRUCTION_PTR inst)
{
	this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset] &= 0xFFFF0000;
	this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset] |= (U16)this->GPR[inst->i_type.rt];
}

void R4300::SW(INSTRUCTION_PTR inst)
{
	this->memory[this->GPR[inst->i_type.rs] + inst->i_type.offset] = this->GPR[inst->i_type.rt];
}

void R4300::SWL(INSTRUCTION_PTR inst)
{
	U32 addr = this->GPR[inst->i_type.rs] + inst->i_type.offset;  // 計算目標地址
	U32 word_addr = addr & ~0x3;  // 計算對齊的4-byte地址
								  // 從寄存器中取得要儲存的32-bit數據
	U32 value_to_store = this->GPR[inst->i_type.rt];	
	int shift = (addr & 0x3) * 8;// 計算右移位數（大端序）	
	U32 current_word = this->memory[word_addr];// 從記憶體中讀取當前對齊的32-bit數據	
	this->memory[word_addr] = (current_word & (0xFFFFFFFF >> (32 - shift))) |		(value_to_store >> shift);// 更新記憶體值：只修改高位部分，低位保持原值
}

void R4300::SWR(INSTRUCTION_PTR inst)
{
	U32 addr = this->GPR[inst->i_type.rs] + inst->i_type.offset;  // 計算目標地址
	U32 word_addr = addr & ~0x3;  // 計算對齊的4-byte地址

								  // 從寄存器中取得要儲存的32-bit數據
	U32 value_to_store = this->GPR[inst->i_type.rt];

	// 從記憶體中讀取當前對齊的32-bit數據
	U32 current_word = this->memory[word_addr];

	// 計算左移位數（大端序）
	int shift = (addr & 0x3) * 8;

	// 更新記憶體值：只修改低位部分，高位保持原值
	this->memory[word_addr] = (current_word & (0xFFFFFFFF << shift)) |
		(value_to_store << shift);
}

void R4300::SYNC(INSTRUCTION_PTR inst)
{
}



void R4300::SYSCALL(INSTRUCTION_PTR inst)
{
	this->EPC = this->PC;
	this->PC = 0x3C;
}
