#include <stdio.h>
#include "memory.h"
#include "bit_functions.h"

unsigned char mem[32][32];

unsigned char mem_get(unsigned int row, unsigned int col){

	return mem[bit_find(row)][bit_find(col)];

}

void mem_put(unsigned int row, unsigned int col, unsigned char b){

	unsigned int x = bit_find(row);
	unsigned int y = bit_find(col);
	mem[x][y] = b;

}

/**
int main(){

	mem_put(4,5,'r');
	mem_put(10,16,'q');
	mem_put(1,5,'y');
	printf("%c\n", mem_get(1,5));
	printf("%c\n", mem_get(10,16));
	printf("%c\n", mem_get(4,5));


}
*/



