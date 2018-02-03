#ifndef DEFS_H
#define DEFS_H
#include<stdio.h>
#include<stdlib.h>
typedef unsigned long long U64;
#define BRD_SQ_NUM 96  
#define MAXGAMEMOVES 2048 
#define MAXPOSITIONMOVES 256 
#define MAXDEPTH 64
#define MOVE(f1,t1,f2,t2) ( (f1) | ((t1) << 8) |((f2) << 16) | ((t2) << 24) )

enum { FALSE, TRUE }; 

typedef struct {
	int moves[MAXPOSITIONMOVES];
	int count;
} S_MOVELIST;

typedef struct {
	int move; 
	U64 posKey; 
} S_UNDO;

typedef struct {
	U64 posKey;
	int move;
} S_PVENTRY;

typedef struct {
	S_PVENTRY *pTable;
	int numEntries;
} S_PVTABLE;

typedef struct {
	
	U64 white;
	U64 black;
	
	int side;

	int ply;
	int histPly;
	
	U64 posKey;
	
	S_UNDO history[MAXGAMEMOVES];
	
	S_PVTABLE PvTable[1];
	int PvArray[MAXDEPTH];
	
}S_BOARD;

/* 	Board is represented by 2 integers, white and black, which dtore the number of pieces on each row for the corresponding side
	For Example, the starting condition of the board is represented by white = 0x 0 1 1 1 1 1 1 6 ,black = 0x 6 1 1 1 1 1 1 0
*/

typedef struct {
	
	int starttime;
	int stoptime;
	int depth;
	int depthset;
	int timeset;
	int movestogo;
	int infinite;
	
	long nodes;
	int quit;
	int stopped;
	
}S_SEARCHINFO;

#define FROM1(m)  ((m) & 0xf)
#define TO1(m)  (((m) >> 8) & 0xf)
#define FROM2(m)  (((m) >> 16) & 0xf)
#define TO2(m)  (((m) >> 24) & 0xf)

U64 PieceKeys [2][8][7]; //Side, No. of Rows, No. of pieces possible
U64 SideKey;

//extern char pceChar[] = "-Hh";
//extern char sideChar[] = "wb-";

#define RAND_64 ((U64)rand() | (U64)rand() << 15 | (U64)rand() << 30 | (U64)rand() << 45 | ((U64)rand() & 0xf) << 60)
enum { WHITE, BLACK, BOTH};  

extern void allInit();

extern void InitPvTable(S_PVTABLE *table);
extern void ClearPvTable(S_PVTABLE *table);
extern void StorePvMove(const S_BOARD *pos, const int move);
extern int ProbePvTable(const S_BOARD *pos);
extern void ResetBoard(S_BOARD *pos);
extern void PrintBoard(const S_BOARD *pos);
extern int  GetTimeMs();
extern int IsGameOver(S_BOARD *pos);
extern void GenerateAllMoves(const S_BOARD *pos, S_MOVELIST *list);
extern int MakeMove(S_BOARD *pos, int move);
extern void TakeMove(S_BOARD *pos);
extern char *PrMove(const int move);
extern int MoveExists(S_BOARD *pos, const int move);
extern int GetPvLine(const int depth, S_BOARD *pos);
extern int ParseMove(char *ptrChar, S_BOARD *pos);
extern int SearchPosition(S_BOARD *pos, S_SEARCHINFO *info);
extern int EvalPosition(const S_BOARD *pos);

#endif