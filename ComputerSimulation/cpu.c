#include <stdio.h>
#include "cpu.h"
#include "memory_system.h"
#include <stdlib.h>
#include "bit_functions.h"

int registers[16];
int cpsr;

void set_reg(int reg, int value){
	registers[reg] = value;
}

int get_reg(int reg){
	return registers[reg];
}

int get_cpsr(){
	return cpsr;
}
//wth is this for
void show_regs(){
	printf("reg0: 0x%08x, reg1: 0x%08x, reg2: 0x%08x, reg3: 0x%08x\n", registers[0], registers[1], registers[2], registers[3]);
	printf("reg4: 0x%08x, reg5: 0x%08x, reg6: 0x%08x, reg7: 0x%08x\n", registers[4], registers[5], registers[6], registers[7]);
	printf("reg8: 0x%08x, reg9: 0x%08x, reg10: 0x%08x, reg11: 0x%08x\n", registers[8], registers[9], registers[10], registers[11]);
	printf("reg12: 0x%08x, reg13: 0x%08x, reg14: 0x%08x, reg15: 0x%08x\n", registers[12], registers[13], registers[14], registers[15]);
}

void step(){

int reg1,reg2,reg3,reg0,reg,inst,address,immediate, eq, lt, gt;
int pc = registers[15];

inst = memory_fetch_word(registers[PC]);
int opcode = inst >> 24;
//printf("PC: %x, Opcode: %x, Instruction: %x\n", pc, opcode, inst);
switch (opcode) {
    case LDI:
	reg = inst >> 16 & 0xff;
	immediate = inst & 0xffff;
	registers[reg] = immediate;
	pc += 4;
	break;
	//check this one

    case LDX:
	reg0  = inst & 0xff;
	address = inst >> 16 & 0xff;
	reg1 = inst >> 8 & 0xff;
	registers[address] = memory_fetch_word(registers[reg0] + reg1);
	pc += 4;
	//finish nvm
	break;
    case LDR:
        reg = inst >> 16 & 0xff;
        address = inst & 0xffff;
        if (address > 1023 || reg > 15) {
            printf("Address/Register out of bounds.\n");
            exit(1);
        }
        registers[reg] = memory_fetch_word(address);
        
        pc += 4;
        break;
    case STR:
	reg = inst >> 16 & 0xff;
	address = inst & 0xffff;
	registers[reg] = address;
	pc += 4;
	break;

    case ADD:
	reg1 = inst >> 8 & 0xff;
	reg2 = inst & 0xff;
	reg = inst >> 16 & 0xff;
	registers[reg] = registers[reg1] + registers[reg2];
	pc += 4;
	break;
    case SUB:
	reg0 = inst >> 8 & 0xff;
	reg1 = inst & 0xff;
	address = inst >> 16 & 0xff;
	registers[address] = registers[reg0] - registers[reg1];
	pc += 4;
	break;
    case MUL:
	reg0 = inst >> 8 & 0xff;
	reg1 = inst & 0xff;
	address = inst >> 16 & 0xff;
	registers[address] = registers[reg0] * registers[reg1];
	pc += 4;
	break;
    case DIV:
	reg0 = inst >> 8 & 0xff;
	reg1 = inst & 0xff;
	address = inst >> 16 & 0xff;
	registers[address] = registers[reg1] / registers[reg0];
	pc += 4;
	break;	
    case CMP:
	
	reg1 = inst >> 8 & 0xff;
	reg2 = inst & 0xff;
	eq = registers[reg1] == registers[reg2];
	lt = registers[reg1] < registers[reg2];
	gt = registers[reg1] > registers[reg2];
	if(eq){
	    bit_set(&cpsr, Z);
	    bit_clear(&cpsr, LT);
	    bit_clear(&cpsr, GT);
	}
	else if(lt){
	    bit_set(&cpsr, LT);
	    bit_clear(&cpsr, Z);
	    bit_clear(&cpsr, GT);
	}
	else if(gt){
	    bit_set(&cpsr, GT);
	    bit_clear(&cpsr, LT);
	    bit_clear(&cpsr, Z);
	}
	pc += 4;
	break;
    case B:
	address = inst & 0xffff;
	pc = address;
	break;
    case BL:
	address = inst & 0xffff;
	registers[LR] = pc + 4;
	pc = address;
	break;
    case BEQ:
	address = inst & 0xffff;
	if(bit_test(cpsr, Z)){
	    pc = address;
	}
	else{
	    pc += 4;
	}
	break;
    case BNE:
	address = inst & 0xffff;
	if(bit_test(cpsr, Z)){
		pc += 4;
	}
	else{
		pc = address;
	}
	break;
    case BLT:
	address = inst & 0xffff;
	if(bit_test(cpsr, LT)){
	    pc = address;
	}
	else{
	    pc += 4;
	}
	break;
    case BGT:
	address = inst & 0xffff;
	if(bit_test(cpsr, GT)){
	    pc = address;
	}
	else{
	    pc += 4;
	}
	break;
    case MOV:
	reg = inst & 0xff;
	address = inst << 16 & 0xff;
	registers[address] = registers[reg];
	pc += 4;
	break;
}
registers[15] = pc;
}


void step_n(int n){
	for(int i=0; i < n; i++){
		step();
	}
}

