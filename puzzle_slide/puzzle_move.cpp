#include "puzzle_move.h"

using namespace std;

  PuzzleMove::PuzzleMove(Board* board) {

  	b = board;

  	prev = NULL;

  	g = 0; 

    h = 0; 

  }

  PuzzleMove::PuzzleMove(int tile, Board* board, PuzzleMove *parent) {

  	b = board;

  	tileMove = tile; 

  	prev = parent;

  	g = parent->g+1; 

    h = 0; 

  }

  PuzzleMove::~PuzzleMove() {


  }