#include "defs.h"
void ResetBoard(S_BOARD *pos) {
	
	pos -> white = 0x01111116;
	pos -> black = 0x61111110;
	pos -> side = WHITE;

	pos -> ply = 0;
	pos -> histPly = 0;

	pos -> posKey = 0ULL;
	
	InitPvTable(pos -> PvTable);

}
static int getPceNum(U64 x, int row) {
	switch(row) {
		case 0:
			return (x & 0xf);
		case 1:
			return (((x) >> 4) & 0xf);
		case 2:
			return (((x) >> 8) & 0xf);
		case 3:
			return (((x) >> 12) & 0xf);
		case 4:
			return (((x) >> 16) & 0xf);
		case 5:
			return (((x) >> 20) & 0xf);
		case 6:
			return (((x) >> 24) & 0xf);
		case 7:
			return (((x) >> 28) & 0xf);
		default:
			return 0;
	}
}
void PrintBoard(const S_BOARD *pos) {
	
	printf(">>>>\n");
	int index, index2, wPceNum, bPceNum, spaceNum;
	for(index = 0; index < 8;index++) {
		printf("      %d ", index);
		wPceNum = getPceNum(pos -> white, index);
		bPceNum = getPceNum(pos -> black, index);
		if(index == 0)
			bPceNum = 0;
		else if(index == 7)
			wPceNum = 0;
		spaceNum = 6 - wPceNum - bPceNum;
		for(index2 = 0; index2 < wPceNum; index2++)
			printf(" H ");
		for(index2 = 0; index2 < spaceNum; index2++)
			printf(" - ");
		for(index2 = 0; index2 < bPceNum; index2++)
			printf(" h ");
		printf("\n");
	}
	printf("\n");
	
}
