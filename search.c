#include "defs.h"
#define INFINITE 30000

static void CheckUp(S_SEARCHINFO *info) {
	// Check for time up
	if(info -> timeset == TRUE && GetTimeMs() > info -> stoptime) {
		info -> stopped = TRUE;
	}
}

static void ClearForSearch(S_BOARD *pos, S_SEARCHINFO *info) {

	ClearPvTable(pos -> PvTable);
	pos -> ply = 0;
	
	info -> starttime = GetTimeMs();
	info -> stopped = 0;
	info -> nodes = 0;

}

static int AlphaBeta(int alpha, int beta, int depth, S_BOARD *pos, S_SEARCHINFO *info) {
	
	if(depth == 0) {
		if((info -> nodes & 2047) == 0) {
			CheckUp(info);
		}
		info -> nodes ++;
		return EvalPosition(pos);	
	}
	
	if((info -> nodes & 2047) == 0) {
		CheckUp(info);
	}
	info -> nodes ++;
	
	if(pos -> ply > MAXDEPTH - 1) {
		return EvalPosition(pos);
	}
	
	S_MOVELIST list[1];
	GenerateAllMoves(pos, list);
	int MoveNum = 0;
	int OldAlpha = alpha;
	int BestMove = 0;
	int Score = -INFINITE;
	
	for(MoveNum = 0; MoveNum < list -> count; MoveNum++) {
		
		MakeMove(pos, list -> moves[MoveNum]);	
		Score = -AlphaBeta(-beta, -alpha, depth - 1, pos, info);
		TakeMove(pos);
		if(info -> stopped == TRUE)
			return 0;
		if(Score > alpha) {
			if(Score >= beta) {
				return beta;
			}
			alpha = Score;
			BestMove = list -> moves[MoveNum];
		}
	}
	
	if(alpha != OldAlpha) {
		StorePvMove(pos, BestMove);
	}
	return alpha;

}

int SearchPosition(S_BOARD *pos, S_SEARCHINFO *info) {
	info -> stoptime = GetTimeMs() + 1999;
	int bestMove = 0;
	int currentDepth = 0;
	ClearForSearch(pos, info);
	for(currentDepth = 1;currentDepth <= info -> depth; currentDepth++) {
		AlphaBeta(-INFINITE, INFINITE, currentDepth, pos, info);
		if(info -> stopped == TRUE) {
			break;
		}
		GetPvLine(currentDepth, pos);
		bestMove = pos -> PvArray[0];
		//printf("Depth:%d Move:%d\n", currentDepth, bestMove);
	}
	MakeMove(pos, bestMove);
	printf("Move Made:%s\n", PrMove(bestMove));
	return bestMove;
}
