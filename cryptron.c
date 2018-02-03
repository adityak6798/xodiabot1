#include "defs.h"

int main() {

	
	allInit();
	S_BOARD board[1];
	board -> PvTable -> pTable = NULL;
	InitPvTable(board -> PvTable);
	ResetBoard(board);
	PrintBoard(board);
	S_SEARCHINFO info[1];
	info -> quit = FALSE;
	info -> timeset = TRUE;
	info -> stoptime = 2000000;
	int move = 0;
	int stop = 0;
	char input[8];
	printf(">>>> Welcome to CRYPTRON!!! This engine has been developed by Aditya Khandelwal. You can play against CRYPTIC CRYPTRON 1.0 , or play a 2 player game.\n");
	while(!stop) {
		printf(">>>> List of options:\n");
		printf("     >>  h  :  Help.\n");
		printf("     >>  r  :  Rules.\n");	
		printf("     >>  1p :  Start a 1 player game against CRYPTIC CRYPTRON 1.0\n");
		printf("     >>  2p :  Start a 2 player game.\n");
		printf("     >>  q  :  Quit Game.\n");
		printf(">>>> Enter an option\n");
		printf(">>>> ");
		scanf("%s", input);
		switch(input[0]) {
			case 'h' : 
				printf(">>>> List of options:\n");
				printf("     >>  h  :  Help.\n");
				printf("     >>  r  :  Rules.\n");	
				printf("     >>  1p :  Start a 1 player game against CRYPTIC CRYPTRON 1.0\n");
				printf("     >>  2p :  Start a 2 player game.\n");
				printf("     >>  q  :  Quit Game.\n");
				break;
			case 'r':
				printf(">>>> White moves from row 1 to row 8. Black Moves from row 8 to row 1\n");
				printf(">>>> Each player turn consists of 2 moves.\n");
				printf(">>>> Move 1: You can move any hackdroid by 1 row, in the forward direction, i.e. White can move from Row i to Row i + 1,\n");
				printf(">>>>         Black can move from Row i to Row i - 1.\n");
				printf(">>>> Move 2: The number of hackdroids in the destination row of Move 1 before Move 1 was made determines the number of \n");
				printf(">>>>         rows that a hackdroid can move in this Move.\n");
				printf(">>>>         For White: If row i + 1 (from above) had j hackdroids, white can move a hackdroid by j rows.\n");
				printf(">>>>                    If row i + 1 was the opponent's base row(Row 7), j = 1\n");
				printf(">>>>         For Black: If row i - 1 (from above) had j hackdroids, white can move a hackdroid by j rows.\n");
				printf(">>>>                    If row i - 1 was the opponent's base row(Row 0), j = 1\n");			
				printf(">>>> Example : A valid Move for the board shown below is:\n");
				printf(">>>>           For White: Move 1: 1 to 2, Move 2: 2 to 4\n");
				printf(">>>>           For White: Move 1: 6 to 7, Move 2: 5 to 6\n");
				printf(">>>>           For Black: Move 1: 7 to 6, Move 2: 7 to 5\n");
				printf(">>>>           For Black: Move 1: 1 to 0, Move 2: 3 to 2\n");
				PrintBoard(board);
				printf(">>>> The Game ends when all of White's hackdroids have crossed all of Black's hackdroids.\n");
				printf(">>>> You should try to get all your hackdroids as close to the opponent base as possible!\n");
				break;
			case '1':
				printf(">>>> You are WHITE(H). CRYPTIC CRYPTRON is BLACK(h). Enter difficulty level: Easy(e), Medium(m) or Hard(h)\n>>>> ");
				char ip[3];
				int flag = 0;
				while(flag == 0) {
					scanf("%s", ip);
					switch(ip[0]) {
						case 'e' :
							info -> depth = 2;
							flag++;
							break;
						case 'm' :
							flag++;
							info -> depth = 4;
							break;
						case 'h':
							flag++;
							info -> depth = 6;
							break;
						default : printf(">>>> Invalid Input. Please enter a valid input (e, m, h)"); 
					}
				}
				printf("Best of Luck. May the best player win!!\n");
				printf("\n>>>> NOTE:: The input format is: <Move1(FromRow)>,<Move1(ToRow)>,<Move2(FromRow)>,<Move2(ToRow)>.\n");
				printf("\n>>>>        Example: 1,2,2,4\n");
				printf("\n>>>>        Example: 6,7,5,6\n");
				printf("\n>>>>        Example: 4,3,3,1\n");
				printf("\n>>>>        Example: 1,0,3,2\n");

				while(!IsGameOver(board)) {
					PrintBoard(board);
					if(board -> side == WHITE) {
						printf(">>>> Please enter a move > ");
						scanf("%s", input);
						if(input[0] == 'q') {
							break;
						}
						move = ParseMove(input, board);
						if(move != 0) {
							MakeMove(board, move);
						}
						else {
							printf(">>>> Enter a valid input\n");
						}
					}
					else {
						SearchPosition(board, info);
					}
				}
				int val = EvalPosition(board);
				printf("Score : %d\n", val);
				if(val > 0 && board -> side == WHITE) {
					printf(">>>> YOU WIN!!");
				}
				if(val < 0 && board -> side == WHITE) {
					printf(">>>> You Lose");
				}
				if(val > 0 && board -> side == BLACK) {
					printf(">>>> You Lose!!");
				}
				if(val < 0 && board -> side == BLACK) {
					printf(">>>> YOU WIN");
				}
				ResetBoard(board);
				
				break;
			case '2':
				printf("Best of Luck. May the best player win!!\n");
				printf("\n>>>> NOTE:: The input format is: <Move1(FromRow)>,<Move1(ToRow)>,<Move2(FromRow)>,<Move2(ToRow)>.\n");
				printf("\n>>>>        Example: 1,2,2,4\n");
				printf("\n>>>>        Example: 6,7,5,6\n");
				printf("\n>>>>        Example: 4,3,3,1\n");
				printf("\n>>>>        Example: 1,0,3,2\n");
				printf("\n>>>> H is White. h is BLACK");
				while(!IsGameOver(board)) {
					PrintBoard(board);
					if(board -> side == WHITE) {
						printf(">>>> Player White: Please enter a move > ");
						scanf("%s",input);
						if(input[0] == 'q') {
							break;
						}
						move = ParseMove(input, board);
						if(move != 0) {
							MakeMove(board, move);
						}
						else {
							printf(">>>> Enter a valid input\n");
						}
					}
					else {
						printf(">>>> Player Black: Please enter a move > ");
						fgets(input, 8, stdin);
						move = ParseMove(input, board);
						if(move != 0) {
							MakeMove(board, move);
						}
						else {
							printf(">>>> Enter a valid input\n");
						}
					}
				}
				int val1 = EvalPosition(board);
				printf(">>>> Score: %d\n", val1);
				if(val1 > 0 && board -> side == WHITE) {
					printf(">>>> WHITE WINS!!");
				}
				if(val1 < 0 && board -> side == WHITE) {
					printf(">>>> BLACK WINS!!");
				}
				if(val1 > 0 && board -> side == BLACK) {
					printf(">>>> BLACK WINS!!");
				}
				if(val1 < 0 && board -> side == BLACK) {
					printf(">>>> WHITE WINS!!");
				}
				ResetBoard(board);
				
				break;
			case 'q':
				printf("Exiting...\n");
				stop = 1;
				free(board -> PvTable -> pTable);
				break;
				default : printf("Please enter a Valid Input\n");
		}
	}
	return 0;
}