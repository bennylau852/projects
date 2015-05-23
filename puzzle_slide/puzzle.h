#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H
#include <deque>
#include <set>
#include "heap.h"
#include "board.h"
#include "puzzle_move.h"
#include "puzzle_heur.h"


class PuzzleSolver
{
 public:
  typedef std::set<PuzzleMove*, PuzzleMoveBoardComp> PuzzleMoveSet;

  PuzzleSolver(const Board &b, PuzzleHeuristic* ph);

  ~PuzzleSolver();

  void run();

  std::deque<int> getSolution();

  int getNumExpansions();
 private:
  Board _b;
  std::deque<int> _solution;
  int _expansions;
  PuzzleHeuristic *_ph;
};

#endif