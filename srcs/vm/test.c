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
		//printf("test ld with args T_REG T_REG\n");
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
		printf("test ld with args T_IND T_REG\nexpect reg[3] == 8 stay at 5\n");
		arena[0] = 2;
		arena[1] = 0b11010000;
		arena[2] = 0b00000010;
		arena[3] = 0b00000101; //IND = 517
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 0;
		arena[7] = 0;
		arena[8] = 8;
		arena[9] = 55;
		print_memory(arena, 16);
	}
	else if (op == 3) {
		printf("test st with args T_REG T_IND \nexpect arena[7] changed stay at 5\n");
		arena[0] = 3;
		arena[1] = 0b01110000;
		arena[2] = 3;
		arena[3] = 0;
		arena[4] = 8;
		arena[5] = 8;
		arena[6] = 0;
		arena[7] = 8;
		arena[8] = 0;
		arena[9] = 0;
		arena[10] = 0;
		arena[11] = 7;
		arena[12] = 55;
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
		printf("test ldi with args T_IND T_DIR T_REG\nexpect reg[3] == 7 stay at 7\n");
		arena[0] = 10;
		arena[1] = 0b11100100;
		arena[2] = 0b00000010;
		arena[3] = 0b00001000; //IND = 520 
		arena[4] = 0b00000010;
		arena[5] = 0b00001000;
		arena[6] = 3;
		arena[7] = 2;
		arena[8] = 0;
		arena[9] = 0;
		arena[10] = 0;
		arena[11] = 8;
		arena[16] = 0;
		arena[17] = 0;
		arena[18] = 0;
		arena[19] = 7;
		arena[519] = 0;
		arena[520] = 2;
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
		printf("test ld with args T_IND T_REG\nexpect reg[3] == 8 stay at 5\n");
		arena[0] = 12;
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
		//printf("test ld with args T_REG T_REG\n");
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
		printf("test lld with args T_IND T_REG\nexpect reg[3] == 8 stay at 5\n");
		arena[0] = 13;
		arena[1] = 0b11010000;
		arena[2] = 0b00000010;
		arena[3] = 0b00000101; //IND = 517
		arena[4] = 3;
		arena[5] = 0;
		arena[6] = 9;
		arena[7] = 5;
		arena[8] = 2;
		arena[9] = 55;
		arena[517] = 0;
		arena[518] = 0;
		arena[519] = 0;
		arena[520] = 8;
		print_memory(arena, 16);
	}else if (op == 14) {
		printf("test lldi with args T_IND T_DIR T_REG\nexpect reg[3] == 7 stay at 7\n");
		arena[0] = 14;
		arena[1] = 0b11100100;
		arena[2] = 0b00000010;
		arena[3] = 0b00001000; //IND = 520 (8 после усечения)
		arena[4] = 0b00000010; //DIR = 520
		arena[5] = 0b00001000;
		arena[6] = 3;
		arena[7] = 2;
		arena[8] = 0;
		arena[9] = 0;
		arena[10] = 0;
		arena[11] = 8;
		arena[16] = 0;
		arena[17] = 0;
		arena[18] = 0;
		arena[19] = 5;
		arena[528] = 0;
		arena[529] = 0;
		arena[530] = 0;
		arena[531] = 7;
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