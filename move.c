#include"defs.h"
static int getPieceNum(U64 x, int row) {
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

static U64 movePiece(U64 x, int fromRow, int toRow) {
	int count, i;
	switch(fromRow) {
		case 0:
			count = getPieceNum(x,0);
			count--;
			x = x & 0xfffffff0;
			x = x | (count);
			break;
		case 1:
			count = getPieceNum(x,1);
			count--;
			x = x & 0xffffff0f;
			x = x | (count << 4);
			break;
		case 2:
			count = getPieceNum(x,2);
			count--;
			x = x & 0xfffff0ff;
			x = x | (count << 8);
			break;
		case 3:
			count = getPieceNum(x,3);
			count--;
			x = x & 0xffff0fff;
			x = x | (count << 12);
			break;
			
		case 4:
			count = getPieceNum(x,4);
			count--;
			x = x & 0xfff0ffff;
			x = x | (count << 16);
			break;
			
		case 5:
			count = getPieceNum(x,5);
			count--;
			x = x & 0xff0fffff;
			x = x | (count << 20);
			break;
			
		case 6:
			count = getPieceNum(x,6);
			count--;
			x = x & 0xf0ffffff;
			x = x | (count << 24);
			break;
			
		case 7:
			count = getPieceNum(x,7);
			count--;
			x = x & 0x0fffffff;
			x = x | (count << 28);
			break;
			
		default:
			;
	}
	switch(toRow) {
		case 0:
			count = getPieceNum(x,0);
			count++;
			x = x & 0xfffffff0;
			x = x | (count);
			break;
			
		case 1:
			count = getPieceNum(x,1);
			count++;
			x = x & 0xffffff0f;
			x = x | (count << 4);
			break;
			
		case 2:
			count = getPieceNum(x,2);
			count++;
			x = x & 0xfffff0ff;
			x = x | (count << 8);
			break;
			
		case 3:
			count = getPieceNum(x,3);
			count++;
			x = x & 0xffff0fff;
			x = x | (count << 12);
			break;
			
		case 4:
			count = getPieceNum(x,4);
			count++;
			x = x & 0xfff0ffff;
			x = x | (count << 16);
			break;
			
		case 5:
			count = getPieceNum(x,5);
			count++;
			x = x & 0xff0fffff;
			x = x | (count << 20);
			break;
			
		case 6:
			count = getPieceNum(x,6);
			count++;
			x = x & 0xf0ffffff;
			x = x | (count << 24);
			break;
			
		case 7:
			count = getPieceNum(x,7);
			count++;
			x = x & 0x0fffffff;
			x = x | (count << 28);
			break;
			
		default:
			;
	}
	return x;
}

void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list) {
	
	list -> count = 0;
	int pceNum = 0, pceNum2 = 0, pceNum3 = 0;
	int i = 0, j = 0 ,numMove;
	int side = pos -> side;
	int f1, f2, t1, t2;
	if(side == WHITE) {
		for(i = 0; i < 7; i++) {
			if(getPieceNum(pos -> white, i) != 0) {
				f1 = i;
				if(i == 6)
					numMove = 1;
				else
					numMove = getPieceNum(pos -> white, (i + 1)) + getPieceNum(pos -> black, (i+1));
				if(numMove <= 5) {
					t1 = i + 1;
					for(j = 0;j < 7;j++) {
						if(j + numMove <= 7) {
							pceNum = getPieceNum(pos -> white, j);
							pceNum2 = getPieceNum(pos -> white,(j + numMove));
							pceNum3 = getPieceNum(pos -> black,(j + numMove));
							if(j == f1)
								pceNum--;
							if(j == t1)
								pceNum++;
							if((j + numMove) == f1)
								pceNum2--;
							if((j + numMove) == t1)
								pceNum2++;
							if(pceNum != 0) {
								if((pceNum2 + pceNum3 <= 5) || (j + numMove == 7)) {
									f2 = j;
									t2 = j + numMove;
									list -> moves[list -> count] = MOVE(f1,t1,f2,t2);
									list -> count ++;
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		for(i = 7; i > 0; i--) {
			if(getPieceNum(pos -> black, i) != 0) {
				f1 = i;
				if(i == 1)
					numMove = 1;
				else
					numMove = getPieceNum(pos -> white, (i - 1)) + getPieceNum(pos -> black, (i - 1));	
				if(numMove <= 5) {
					t1 = i - 1;
					for(j = 7;j > 0;j--) {
						if(j - numMove >= 0) {
							pceNum = getPieceNum(pos -> black, j);
							pceNum2 = getPieceNum(pos -> black,(j - numMove));
							pceNum3 = getPieceNum(pos -> white,(j - numMove));
							if(j == f1)
								pceNum--;
							if(j == t1)
								pceNum++;
							if((j - numMove) == f1)
								pceNum2--;
							if((j - numMove) == t1)
								pceNum2++;
							if(pceNum != 0) {
								if((pceNum2 + pceNum3 <= 5) || (j - numMove == 0)) {
									f2 = j;
									t2 = j - numMove;
									list -> moves[list -> count] = MOVE(f1,t1,f2,t2);
									list -> count ++;
								}
							}
						}
					}
				}
			}
		}
	}
}

static void MovePiece(const int from, const int to, S_BOARD *pos) {
	
	if(from == to)
		return;
	
	if(pos -> side == WHITE) {
		pos -> white = movePiece(pos -> white, from, to);
		pos -> posKey ^= PieceKeys[0][from][getPieceNum(pos -> white, from)];
		pos -> posKey ^= PieceKeys[0][to][getPieceNum(pos -> white, to)];
	}
	else {
		pos -> black = movePiece(pos -> black, from, to);
		pos -> posKey ^= PieceKeys[1][from][getPieceNum(pos -> black, from)];
		pos -> posKey ^= PieceKeys[1][to][getPieceNum(pos -> black, to)];		
	}
}

int MakeMove(S_BOARD *pos, int move) {
	
	int i =0;
	int from1 = FROM1(move);
	int to1 = TO1(move);
	int from2 = FROM2(move);
	int to2 = TO2(move);
	//printf("Move: %d, %d, %d, %d\n",from1, to1, from2, to2);
	pos -> history[pos -> histPly].posKey = pos -> posKey;
	MovePiece(from1, to1, pos);
	MovePiece(from2, to2, pos);
	pos -> history[pos -> histPly].move = move;
	pos -> histPly++;
	pos -> ply++; 
	pos -> side ^= 1;
	pos -> posKey ^= SideKey;
	return 1;
}


void TakeMove(S_BOARD *pos) {
	
	int i;
	pos -> histPly --;
	pos -> ply --;
	int move = pos -> history[pos -> histPly].move;
	int from1 = FROM1(move);
	int to1 = TO1(move);
	int from2 = FROM2(move);
	int to2 = TO2(move);
	//printf("%d\n",getPieceNum(pos -> black, 1));
	//printf("%d\n",getPieceNum(pos -> black, 0));
	pos -> side ^= 1;
	MovePiece(to2, from2, pos);
	MovePiece(to1, from1, pos);
	pos -> posKey ^= SideKey;

}

char *PrMove(const int move) {
	static char MvStr[6];
	int f1 = FROM1(move);
	int t1, t2;
	t1 = TO1(move);
	int f2 = FROM2(move);
	t2 = TO2(move);
	sprintf(MvStr, "%d,%d,%d,%d", f1,t1,f2,t2);
	return MvStr;
}
int MoveExists(S_BOARD *pos, const int move) {

	int index;
	S_MOVELIST list[1];
	GenerateAllMoves(pos, list);
	for(index = 0; index < list -> count; index++) {
		if(list -> moves[index] == move)
			return TRUE;
	}
	return FALSE;
}
int GetPvLine(const int depth, S_BOARD *pos) {
	
	int move = ProbePvTable(pos);
	int count = 0;
	
	while(move != 0 && count < depth) {
		if(MoveExists(pos, move)) {
			MakeMove(pos, move);
			pos -> PvArray[count++] = move;
			move = ProbePvTable(pos);
		}
		else {
			break;
		}
	}
	while(pos -> ply > 0) {
		TakeMove(pos);
	}
	return count;
}
int ParseMove(char *ptrChar, S_BOARD *pos) {
	
	int move;
	int f1, t1, f2, t2;
	f1 = ptrChar[0] - '0';
	f2 = ptrChar[4] - '0';
	t1 = ptrChar[2] - '0';
	t2 = ptrChar[6] - '0';
	move = MOVE(f1, t1, f2, t2);
	if(MoveExists(pos, move))
		return move;
	return 0;

}
