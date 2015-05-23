#include "puzzle_heur.h"
#include <stdlib.h>

using namespace std;

int PuzzleManhattanHeuristic::compute(const Board& b) {

    int size = b.size();

    int manhattan_distance = 0;

    for (int i = 0; i < size; i++) {

        if (b[i] != 0) {

            int current_row = i/b.dim();

            int current_col = i%b.dim();

            int away_row = b[i]/b.dim();

            int away_col = b[i]%b.dim();

            /*

            Finds absolute distance from where tile is to where tile is supposed to be
            by finding sum of x and y (row and col)


            */

            int distance_row = abs(current_row - away_row); 

            int distance_col = abs(current_col - away_col);

            manhattan_distance += distance_col + distance_row;

        }

    }

    return manhattan_distance;

}
