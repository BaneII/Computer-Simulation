#include <stdio.h>
#include "memory_system.h"
#include "bit_functions.h"
#include "decoder.h"
#include "memory.h"

void memory_store(int address, unsigned char value){

	int lower_half = address & 0b11111;
	int upper_half = (address >> 5) & 0x1F;
	unsigned int lh = decoder(lower_half);
	unsigned int uh = decoder(upper_half);
	mem_put(lh,uh,value);

}

unsigned char memory_fetch(int address){

	int lower_half = address & 0b11111;
	int upper_half = (address >> 5) & 0x1F;
	unsigned int lh = decoder(lower_half);
	unsigned int uh = decoder(upper_half);
	unsigned char ans = mem_get(lh,uh);
	return ans;

}

void memory_store_word(int address, unsigned int value){

	unsigned char b1 = value & 0xff;
	unsigned char b2 = (value >> 8) & 0xff;
	unsigned char b3 = (value >> 16) & 0xff;
	unsigned char b4 = (value >> 24) & 0xff;

	memory_store(address, b1);
	memory_store(address + 1, b2);
	memory_store(address + 2, b3);
	memory_store(address + 3, b4);

}

unsigned int memory_fetch_word(int address){

	unsigned char b1 = memory_fetch(address);
	unsigned char b2 = memory_fetch(address + 1);
	unsigned char b3 = memory_fetch(address + 2);
	unsigned char b4 = memory_fetch(address + 3);

	return (b4 << 24) | (b3 << 16) | (b2 << 8) | (b1);
		
}

/**
void memory_dump(int start_address, int num_bytes){
	for(int i = 0; i < num_bytes; i++)}
		printf("0x%08x: 0x%08x\n", start_address + i, 
				memory_fetch(start_address + i));
	}
}
*/


void memory_dump(int start_address, int num_bytes) {
    int start_boundary = start_address - (start_address % 8);
    int boundary_bytes = num_bytes + (start_address - start_boundary);
    printf("start_boundary: %d 0x%04x\n", start_boundary, start_boundary);
    for (int i = start_boundary; i < start_boundary+boundary_bytes; i+=8) {
        printf("0x%04x (0d%04d) 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x \n", 
               i, i,
               memory_fetch(i),   memory_fetch(i+1), memory_fetch(i+2), memory_fetch(i+3),
               memory_fetch(i+4), memory_fetch(i+5), memory_fetch(i+6), memory_fetch(i+7));
    }
}

void load_memory(char *filename){
	FILE *fp;
	fp = fopen(filename, "r");
	unsigned int address;
	unsigned int value;
	unsigned int i = 0;
	fscanf(fp, "%x", &address);
	while (fscanf(fp, "%x", &value) != EOF){
		memory_store_word(address + i, value);
		i = i + 4;
	}
}
//do we need this
void memory_fill(int start_address, unsigned char value, int num_bytes){
	for(int i = start_address; i < start_address + num_bytes; i++){
		memory_store(i, value);
	}
}

