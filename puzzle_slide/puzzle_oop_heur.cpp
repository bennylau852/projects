#include "puzzle_heur.h" 

using namespace std;

int PuzzleOutOfPlaceHeuristic::compute(const Board& b) {

	int size = b.size();

	int out_of_place = 0;

	for (int i = 0; i < size; i++) {

		if (b[i] != i && b[i] != 0) { 

			out_of_place++;

		}

	}

	return out_of_place;

}