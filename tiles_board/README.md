COMPILE INSTRUCTIONS: To compile, simply type "make" in the command prompt, followed by, "./tiles (input file) (output file)". To compile with an included sample input file, simply type "make" in the command prompt, followed by, "./tiles in.txt out.txt". The solution will be posted in out.txt

Given a finite number of rectangular tiles of different sizes, this program attempts to tile them onto a board without overlaps using a backtracing search. Tiles can be rotated if necessary (swap length and height). Each tile has a given length and height. 

The input file is in the format: 

N M X 
ID1 l1 h1
ID2 l2 h2
...
IDX lX hX

The first line of the input file contains three numbers where N is the length of the surface, M is the height of the surface, and X is the number of tiles being placed. 
After that, IDi is the ID of the given tile, li is its length, and hi is its height. 


The data is stored using a Red-Black Tree implementation with the key being an integer value and the value being a class type Rectangle

struct Rectangle {
    int ID;
    int length;
    int height;
};

The solution will be stored in an output file in the format below:

ID1 x1 y1 l1 h1
ID2 x2 y2 l2 h2
...
IDX xX yX lX hX

Where xi, yi (xy coordinate plane) are the bottom left coordinates of tile i, li is the length of tile i, and hi is the height of tile i

In addition, the board will be printed in the output file with each tile in its correct place and each space would either be blank or contain an integer ID number indicating which tile fills that space

If no solution would be found, a "no solution" will appear instead

Please ignore the unused variable warnings. They do not affect the program






