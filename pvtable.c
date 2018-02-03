#include "defs.h"
const int PvSize = 0x100000 * 2;

void ClearPvTable(S_PVTABLE *table) {
	S_PVENTRY *pvEntry;
		
	for(pvEntry = table -> pTable; pvEntry < ((table -> pTable) + (table -> numEntries)); pvEntry++) {
		pvEntry -> posKey = 0ULL;
		pvEntry -> move = 0;
	}
}

void InitPvTable(S_PVTABLE *table) {
	
	table -> numEntries = PvSize / sizeof(S_PVENTRY);
	table -> numEntries -= 2;
	if(table->pTable != NULL){
		free(table->pTable);
	}
	table -> pTable = (S_PVENTRY *) calloc((table -> numEntries),sizeof(S_PVENTRY));
	ClearPvTable(table);
	
}

void StorePvMove(const S_BOARD *pos, const int move) {
	int index = (pos -> posKey) % (pos -> PvTable -> numEntries);
	pos -> PvTable -> pTable[index].move = move;
	pos -> PvTable -> pTable[index].posKey = pos -> posKey;
}

int ProbePvTable(const S_BOARD *pos) {
	int index = (pos -> posKey) % (pos -> PvTable -> numEntries);
	if(pos -> PvTable -> pTable[index].posKey == pos -> posKey) {
		return pos -> PvTable -> pTable[index].move;
	}
	return 0;
}