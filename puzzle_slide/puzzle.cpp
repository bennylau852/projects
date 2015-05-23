#include <iostream>
#include <cstdlib>
#include <deque>
#include <stdlib.h>
#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "puzzle_move.h"

using namespace std;

int main(int argc, char *argv[]) {

    if(argc < 5) {
        cerr << "Usage: ./puzzle size initMoves seed heur" << endl;
        return 1;
    }

    int dimension = atoi(argv[1]);

    int initial_moves = atoi(argv[2]);

    int seed = atoi(argv[3]);

    int heur_type = atoi(argv[4]);

    Board b(dimension,initial_moves,seed);

    PuzzleBFSHeuristic* heur1 = new PuzzleBFSHeuristic();

    PuzzleOutOfPlaceHeuristic* heur2 = new PuzzleOutOfPlaceHeuristic();

    PuzzleManhattanHeuristic* heur3 = new PuzzleManhattanHeuristic();

    bool quit = false;

    cout << b << endl;

    while (quit == false) {

        cout << "Enter tile number to move or -1 for a cheat or 0 to quit: " << endl;

        int user_input;

        cin >> user_input;

        if (user_input > -1 && user_input < b.size() && user_input != 0) {

            b.move(user_input);

            cout << endl;

            if (b.solved()) {

                cout << "Congratulations! You solved it!" << endl;

                cout << endl;

                quit = true;

            }

            cout << b << endl;

        }

        else if (user_input == 0) {

            quit = true;

        }

        else if (user_input == -1) {

            if (heur_type == 0) {

                PuzzleSolver ps1(b, heur1);

                ps1.run();

                cout << "Try this sequence" << endl;

                deque<int> _solution = ps1.getSolution();

                for (unsigned int i = 0; i < _solution.size(); i++) {

                    cout << _solution[i] << " ";

                }

                int expansions = ps1.getNumExpansions();

                cout << "(Expansions = " << expansions << ")" << endl;

            }

            else if (heur_type == 1) {

                PuzzleSolver ps2(b, heur2);

                ps2.run();

                cout << "Try this sequence" << endl;

                deque<int> _solution = ps2.getSolution();

                for (unsigned int i = 0; i < _solution.size(); i++) {

                    cout << _solution[i] << " ";

                }

                int expansions = ps2.getNumExpansions();

                cout << "(Expansions = " << expansions << ")" << endl;

            }

            else {

                PuzzleSolver ps3(b, heur3);

                ps3.run();

                cout << "Try this sequence" << endl;

                deque<int> _solution = ps3.getSolution();

                for (unsigned int i = 0; i < _solution.size(); i++) {

                    cout << _solution[i] << " ";

                }

                int expansions = ps3.getNumExpansions();

                cout << endl;

                cout << "(Expansions = " << expansions << ")" << endl;

            }

            cout << endl;

            cout << b << endl;

        }

        else {

            cout << "Please enter valid input" << endl;

            cout << endl;

            cout << b << endl;

        }

    }

    delete heur1;

    delete heur2;

    delete heur3;

    return 0;

}