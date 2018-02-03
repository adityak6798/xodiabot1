#include "defs.h"

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
int EvalPosition(const S_BOARD *pos) {
	int wscore = 0, bscore = 0;
	wscore += (getPceNum(pos -> white, 7)*5);
	wscore += (getPceNum(pos -> white, 6)*3);
	wscore += (getPceNum(pos -> white, 5)*2);
	wscore += (getPceNum(pos -> white, 4)*1);
	bscore += (getPceNum(pos -> black, 0)*5);
	bscore += (getPceNum(pos -> black, 1)*3);
	bscore += (getPceNum(pos -> black, 2)*2);
	bscore += (getPceNum(pos -> black, 3)*1);
	if(pos -> side == WHITE)
		return (wscore - bscore);
	else
		return (bscore - wscore);
}

int IsGameOver(S_BOARD *pos) {
	int index, lastWhite, lastBlack;
	for(index = 0; index < 8; index ++) {
		if(getPceNum(pos -> white, 7 - index) != 0) {
			lastWhite = 7 - index;
		}
		if(getPceNum(pos -> black, index) != 0) {
			lastBlack = index;
		}
	}
	if(lastWhite > lastBlack)
		return 1;
	return 0;
}
