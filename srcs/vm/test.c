#include "../../includes/vm.h"

void	test(int op, unsigned char *arena)
{
	if (op == 1) {
		arena[0] = 1;
		arena[1] = 0b11010100;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}
	else if (op == 2) {
		// arena[0] = 2;
		// arena[1] = 0b10010000;
		// arena[2] = 0;
		// arena[3] = 0;
		// arena[4] = 0;
		// arena[5] = 5;
		// arena[6] = 3;
		// arena[7] = 5;
		// arena[8] = 2;
		// arena[9] = 55;
		// print_memory(arena, 16);
		arena[0] = 2;
		arena[1] = 0b11010000;
		arena[2] = 0b00000010;
		arena[3] = 0b00000101; //IND = 517
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}
	else if (op == 3) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 4) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 5) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 6) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 7) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 8) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 9) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 10) {
		arena[0] = 10;
		arena[1] = 0b11100100;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 0;
		arena[5] = 0;
		arena[6] = 0;
		arena[7] = 8;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 11) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 12) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 13) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 14) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 15) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}else if (op == 16) {
		arena[0] = 2;
		arena[1] = 0b11010111;
		arena[2] = 0;
		arena[3] = 5;
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 8;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		print_memory(arena, 16);
	}
}