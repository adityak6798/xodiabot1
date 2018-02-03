This project is a DSA project which involves a C language implementation of Minimax and alpha-beta pruning along with iterative deepening and a PV Search to determine the optimal move in a game of Cryptron. You can play against the UI in 3 different modes(Easy, Medium, Hard) and can also play a 2 player game. This is also an attempt to solve the problem of PICT's Credenz'17's Xodia. URL for game instructions - https://xodia.in/


GAME:
There are two high security data centers (bases) on the opposite ends of the board, with 6 layers of security between them. The goal is to invade the oppo- nents base and steal their data with the help of HackDroids.

The game is played on an arrangement of 8 rows.  The aim of the game is   to place your HackDroids in the opponent’s base (home row) or as near as possible to it.

The game consists of 24 HackDroids.
Each player has 12 HackDroids with 6 in the base and 1 HackDroid in each row till the opponent’s base.

Rows:
The game consists of 6 rows and 2 bases(home rows). Each row can contain up to 6 HackDroids.

Base:
The rows at the two ends of the board where 6 HackDroids of the respective player are initially placed.
White's base is the 1st row and black’s base is the 8th row. The bases can contain any number of HackDroids.

The game is turn based. Each player gets alternate turns and each turn is composed of 2 moves.

Each player gets to play two moves per turn. The types of moves are : 
1.First attack
2.Second attack

1)	First Attack:
•	The player can move any one of their HackDroids ahead by one row only.
•	If the player moves the HackDroid from row i1 to row f1,
f1 − i1  = 1
The total number of hackdroids in the landing row before the first attack will determine the number of rows the player has to move in the second attack.

2)	Second Attack:
The player can move any one of their HackDroids ahead by exactly the number of rows as decided by the first attack.
•	If the player moves the HackDroid from row i2 to row f2,
f2 − i2 = number tokens present in f1 before the first attack.

If the final position of the first move i.e. f1 is in the opponent’s base, the Hack- Droid can move exactly one row ahead in its second attack. f2 − i2 = 1.

The winner is determined based on whose hackdroids are closer to the opponent's base. An internal scoring scheme gives maximum weightage to hackdroids which reach the opponent's base.(50 pts.) Each Row towards home base is subsequently marked as 30, 20, 10,.... and so on.


Code has been based on VICE Chess Engine. Video Series is on YouTube on the Channel BlueFever Software.