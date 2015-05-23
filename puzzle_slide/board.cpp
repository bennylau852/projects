#include <iostream>
#include <iomanip>
#include <map>
#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <memory.h>
#include "board.h"
using namespace std;


Board::Board(int dim, int numInitMoves, int seed ) {
    _size = dim*dim;
    _tiles = new int[_size];
    srand(seed);
    for(int i=0; i < _size; i++) {
        _tiles[i] = i;
    }
    int blankLoc = 0;
    while(numInitMoves > 0) {
        int r = rand()%4;
        int randNeighbor = -1;
        if(r == 0) {
            int n = blankLoc - dim;
            if(n >= 0) {
                randNeighbor = n;
            }
        } else if(r == 1) {
            int w = blankLoc - 1;
            if(blankLoc % dim != 0) {
                randNeighbor = w;
            }
        } else if(r == 2) {
            int s = blankLoc + dim;
            if(s  < _size) {
                randNeighbor = s;
            }
        } else {
            int e = blankLoc + 1;
            if(blankLoc % dim != dim-1) {
                randNeighbor = e;
            }
        }
        if(randNeighbor > -1) {
            _tiles[blankLoc] = _tiles[randNeighbor];
            _tiles[randNeighbor] = 0;
            blankLoc = randNeighbor;
            numInitMoves--;
        }
    }
}


Board::Board(const Board& rhs) {

    int size = rhs.size();

    _tiles = new int[size];

    for (int i = 0; i < size; i++) {

        _tiles[i] = rhs[i];

    }

    _size = rhs._size;

}

Board::~Board() {

    delete [] _tiles;

}


void Board::move(int tile) {
    int side_dim = dim();
    int tr, tc, br, bc;


    int i=-1;
    while(_tiles[++i] != tile);

    tr = i / side_dim;
    tc = i % side_dim;


    int j=-1;
    while(_tiles[++j] != 0);

    br = j / side_dim;
    bc = j % side_dim;

    if( abs(static_cast<double>(tr-br)) + abs(static_cast<double>(tc-bc)) != 1) {
        cout << "Invalid move of tile " << tile << " at ";
        cout << tr << "," << tc << " and blank spot at ";
        cout << br << "," << bc << endl;
        return;
    }

    _tiles[j] = tile;
    _tiles[i] = 0;
}

map<int, Board*> Board::potentialMoves() const {

    map<int, Board*> newBoards;

    int blank_tile_loc;

    for (int i = 0; i < size(); i++) {

        if (_tiles[i] == 0) {

            blank_tile_loc = i; 

        }

    }

    int blank_row = blank_tile_loc/dim();

    int blank_col = blank_tile_loc%dim();

    int up_index = -1; 

    int down_index = -1;

    int left_index = -1;

    int right_index = -1;

    int up_tile;

    int down_tile;

    int left_tile;

    int right_tile;

    if (blank_row - 1 > -1) { 

        up_index = ((blank_row - 1) * dim()) + blank_col;

        up_tile = _tiles[up_index];

    }

    if (blank_row + 1 < dim()) { 

        down_index = ((blank_row + 1) * dim()) + blank_col;

        down_tile = _tiles[down_index];

    }

    if (blank_col - 1 > -1) { 

        left_index = (blank_col - 1)  + (blank_row*dim());

        left_tile = _tiles[left_index];

    }

    if (blank_col + 1 < dim()) { 

        right_index = (blank_col + 1)  + (blank_row*dim());

        right_tile = _tiles[right_index];

    }

    if (up_index != -1) { 

        Board* up = new Board(*this);

        up->move(up_tile);

        newBoards.insert(make_pair(up_tile, up) );

    }

    if (down_index != -1) { 

        Board* down = new Board(*this);

        down->move(down_tile);

        newBoards.insert(make_pair(down_tile, down) );

    }


    if (left_index != -1) { 

        Board* left = new Board(*this);

        left->move(left_tile);

        newBoards.insert(make_pair(left_tile, left) );

    }

    if (right_index != -1) { 

        Board* right = new Board(*this);

        right->move(right_tile);

        newBoards.insert(make_pair(right_tile, right) );

    }

    return newBoards;

}

bool Board::solved() const {

    for(int i=0; i < (*this).size(); i++) {

        if (_tiles[i] != i) {

            return false;

        }

    }

    return true;

}

ostream& operator<<(std::ostream &os, const Board &b) {

    int size = b.size();

    int dim = b.dim();

    int temp_array[dim][dim]; 

    memcpy(temp_array, b._tiles, size * sizeof(int)); 

    for (int i = 0; i < dim; i++) { 

        b.printRowBanner(os);

        for (int j = 0; j < dim; j++) {

            //if (temp_array[i][j] != 0) {

                os << "|";

                if (temp_array[i][j] == 0) {

                    os << " " << " ";

                }

                else if (temp_array[i][j] < 10) {

                    os << " " << temp_array[i][j];

                }

                else {

                    os << temp_array[i][j];

                }

        }

        os << "|" << endl;

    }

    b.printRowBanner(os);

    return os;

}

bool Board::operator<(const Board& rhs) const {

    int size = this->size();

    for (int i = 0; i < size; i++) {

        if (_tiles[i] < rhs[i]) {

            return true;

        }

        else if (_tiles[i] == rhs[i]) {


            continue;

        }

        else {

            return false;

        }

    }

    return false;

}

const int& Board::operator[](int loc) const {
    return _tiles[loc];
}

int Board::size() const {
    return _size;
}

int Board::dim() const {
    return static_cast<int>(sqrt(_size));
}

void Board::printRowBanner(ostream& os) const {
    int side_dim = dim();
    if(side_dim == 0) return;
    os << '+';
    for(int i=0; i < side_dim; i++) {
        os << "--+";
    }
    os << endl;
}