#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decoder.h"
#include "memory.h"
#include "memory_system.h"
#include "bit_functions.h"
#include "cpu.h"

int main(int argc, char **argv) {
    printf("0x%08x\n", decoder(4));
    printf("0x%08x\n", decoder(1));
    
    printf("bit_find: %d\n", bit_find(8));
    
    memory_fill(0, 0xff, 100);
    
    //memory_store_word(4, 101010);
    memory_store(0x111, 100);
    
    printf("memory_fetch(0x111): 0x%02x\n", memory_fetch(0x111));
    memory_store_word(0x50, 0xaabbccdd);
    printf("memory_fetch_word: 0x%08x\n", memory_fetch_word(0x50));
    //memory_dump();
    
    load_memory("program1.txt");
    printf("memory_fetch_word(12): 0x%08x\n", memory_fetch_word(12));

    memory_dump(270, 20);
    
    memory_store_word(80, 10);          // 10 at address 80
    memory_store_word(84, 20);          // 20 at address 84
    memory_store_word(100, 0x01000050); // LDR R0,80
    printf("memory_store_word: 0x%08x\n", memory_fetch_word(100));
    memory_store_word(104, 0x01010054); // LDR R1,84
    memory_store_word(108, 0x05020001); // ADD R3,R0,R1
    memory_store_word(112, 0x09000102); // CMP R1,R2
    memory_store_word(116, 0x09000202); // CMP R2,R2
    memory_store_word(120, 0x09000201); // CMP R2,R1
    memory_store_word(124, 0x0E000064); // BGT 100    
    memory_dump(80, 16);
    memory_dump(100,16);
    set_reg(PC, 100);
        
    //show_regs();
    step();
    //show_regs();
    //set_reg(R0, 20);
    //set_reg(R1, 47);
    //set_reg(R2, 3);
    printf("R0: %d\n", get_reg(R0));    
    step();
    //show_regs();
    printf("R1: %d\n", get_reg(R1));
    step();
    //show_regs();
    printf("R2: %d\n", get_reg(R2));
    step();
    //show_regs();
    printf("CPSR: 0x%08x\n", get_cpsr());
    step();
    //show_regs();
    printf("CPSR: 0x%08x\n", get_cpsr());
    step();
    //show_regs();
    printf("CPSR: 0x%08x\n", get_cpsr());
    step();
    //show_regs();
    printf("PC: %d\n", get_reg(PC));
    step();
    //show_regs();
    printf("R0: %d\n", get_reg(R0));
    //show_regs();
    
    while (1) {
		char cmd[100], file_name[100];
		int num, num1;
		printf("Enter cmd: ");
		scanf("%s", cmd);
		printf("%s\n", cmd);
		if (strcmp(cmd, "set_reg") == 0) {
			printf("Enter reg: ");
			scanf("%d", &num);
			printf("Ender reg value: ");
			scanf("%d", &num1);
			set_reg(num, num1);
		}
		else if (strcmp(cmd, "dump") == 0) {
			printf("Enter address: ");
			scanf("%x", &num);
			printf("Enter num bytes: ");
			scanf("%d", &num1);
			memory_dump(num, num1); 
		}
		else if (strcmp(cmd, "regs") == 0) {
			show_regs();
		}
		else if (strcmp(cmd, "step") == 0) {
			step();
		}
		else if (strcmp(cmd, "step_n") == 0) {
			printf("Enter num of steps: ");
			scanf("%d", &num);
			step_n(num);
		}
		else if (strcmp(cmd, "load") == 0) {
			printf("Enter file name: ");
			scanf("%s", file_name);
			load_memory(file_name);
		}
		else {
			printf("invalid cmd\n");
		}		
	}

}
