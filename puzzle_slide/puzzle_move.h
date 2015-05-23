#ifndef PUZZLEMOVE_H
#define PUZZLEMOVE_H
#include "board.h"
#include "puzzle_heur.h" 

using namespace std;

struct PuzzleMove
{
  int tileMove;  
  Board *b;      
  int g;         
  int h;         
  PuzzleMove *prev;  


  PuzzleMove(Board* board);

  PuzzleMove(int tile, Board* board, PuzzleMove *parent);

  ~PuzzleMove();

};


struct PuzzleMoveScoreComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const {

    int f1 = m1->h + m1->g;
    int f2 = m2->h + m2->g;
    if (f1 == f2) {

      if (m1->h < m2->h) {

        return true;

      }

    }

    else if (f1 < f2) {

      return true;

    }

    else {

      return false;

    }

    return false;

  }
};

struct PuzzleMoveBoardComp
{
  bool operator()(const PuzzleMove *m1, const PuzzleMove *m2) const
  {
    Board* b1 = m1->b;
    Board* b2 = m2->b;

    if (*b1 < *b2) {

      return true;

    }

    else {

      return false;

    }

  }
};

#endif