#include "defs.h"
void allInit() {
	int i, j, k;
	for(i = 0;  i < 2; i++) {
		for(j = 0; j < 8; j++) {
			for(k = 0; k < 7; k++) {
				PieceKeys[i][j][k] = RAND_64;
			}
		}
	}
	SideKey = RAND_64;
}
