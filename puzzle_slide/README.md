The program needs 4 arguments from the command line. To compile, type "make" in the command prompt, followed by, "./puzzle (n or size of board) (initMoves) (seed) (heur)"

This program uses an A* algorithm and a user-defined Heap (priority queue) class to solve a sliding tiles puzzle game. The game is finished when the tiles are put in numerial order. The user attempts to achieve this but the user also has the abillity (with the help of the A* algorithm) to ask for a cheat or hint from the program as to what the next best step is (towards finding a given random solution). Dimensions of the board is a square with size n. For every turn, you pick a tile surrounding the blank space and that is the tile that'll swap places with the blank space. 

n is the dimension of the board (n = 3 for a 3 by 3 board) - integer

initMoves is the number of moves used to scramble the original board in order to create a random board (initMoves = 5 means that 5 moves are made on a solved state board to scatter the tiles or render it unsolved) - integer

seed is a random number that'll seed the random number generator which in turn determines which initial moves to choose to randomize the board - integer

heur is an integer ranging from 0 to 2 inclusive that'll determine which heuristic to use (0 = BFS, 1 = TilesOutOfPlace, 2 = Manhattan Distance)

The A* algorithm uses 3 heuristics: BFS (breadth first search), Manhattan distance (sums the x/y or horizontal/vertical distance the current state of the puzzle board is from the solved state), and Out of place (number of tiles that aren't in their correct places)

Solved states for a 3 by 3 board and a 4 by 4 board: (View raw for better presentation of board)

+--+--+--+ <br />
|  | 1| 2| <br />
+--+--+--+ <br />
| 3| 4| 5| <br />
+--+--+--+ <br />
| 6| 7| 8| <br />
+--+--+--+ <br />

+--+--+--+--+ <br />
|  | 1| 2| 3| <br />
+--+--+--+--+ <br />
| 4| 5| 6| 7| <br />
+--+--+--+--+ <br />
| 8| 9|10|11| <br />
+--+--+--+--+ <br />
|12|13|14|15| <br />
+--+--+--+--+ <br />

A sample argument line would be "./puzzle 4 30 1537 2" where n = 4, initMoves = 30, seed = 1573, heur = Manhattan Distance. You would get the following board

+--+--+--+--+ <br />
| 4| 1| 2| 3| <br />
+--+--+--+--+ <br /> 
| 8| 5| 7|10| <br />
+--+--+--+--+ <br />
| 9|13| 6|11| <br />
+--+--+--+--+ <br />
|12|14|15|  | <br />
+--+--+--+--+ <br />

Enter tile number to move or -1 for a cheat: -1

If you ask for a cheat (type "-1" in terminal), you would get a sequence of numbers that'll help you reach the solved state (with the sequence being generated using the given heuristic) as shown below: 

Enter tile number to move or -1 for a cheat: -1

Try this sequence:
11 10 7 6 10 11 15 14 13 9 8 4
(Expansions = 54)

+--+--+--+--+ <br />
| 4| 1| 2| 3| <br />
+--+--+--+--+ <br />
| 8| 5| 7|10| <br />
+--+--+--+--+ <br />
| 9|13| 6|11| <br />
+--+--+--+--+ <br />
|12|14|15|  | <br />
+--+--+--+--+ <br />





