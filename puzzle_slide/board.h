#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <algorithm>

class Board
{
 public:

  Board(int dim, int numInitMoves, int seed);

  Board(const Board& rhs);

  ~Board();

  void move(int tile);

  std::map<int, Board*> potentialMoves() const; 

  bool solved() const;

  friend std::ostream& operator<<(std::ostream &os, const Board &b);

  bool operator<(const Board& rhs) const;
  
  int const & operator[](int loc) const;

  int size() const;

  int dim() const;
  
 private:

  void printRowBanner(std::ostream& os) const;

  int *_tiles; 
  int _size; 
};


#endif