#include "puzzle_solver.h"

typedef std::set<PuzzleMove*, PuzzleMoveBoardComp> PuzzleMoveSet;

PuzzleSolver::PuzzleSolver(const Board &b, PuzzleHeuristic* ph):_b(b) {

    _ph = ph;

    _expansions = 0;

}

PuzzleSolver::~PuzzleSolver() {

}

void PuzzleSolver::run() {

    Board* b1 = new Board(_b);

    PuzzleMove* original = new PuzzleMove(b1); 

    PuzzleMoveScoreComp pmsc; 

    PuzzleMoveBoardComp pmbc;
    
    Heap<PuzzleMove*, PuzzleMoveScoreComp> open_list(2, pmsc); 

    PuzzleMoveSet pms(pmbc); 

    open_list.push(original);

    pms.insert(original);

    set<map<int,Board*> > frees_memory; 

    while (!open_list.empty()) {

        PuzzleMove* current;

        current = open_list.top();

        open_list.pop(); 

        if (current->b->solved()) {

            while (current->prev != NULL) {

                _solution.push_front(current->tileMove); 

                current = current->prev; 

            }

            break;

        }

        else {

            map<int, Board*> neighbors = current->b->potentialMoves(); 

            frees_memory.insert(neighbors); 

            map<int, Board*>::iterator it;

            for (it = neighbors.begin(); it != neighbors.end(); ++it) {

                    PuzzleMove* pm_new = new PuzzleMove(it->first, it->second, current);

                    pm_new->h = _ph->compute(*(pm_new->b)); 

                    PuzzleMoveSet::iterator it2 = pms.find(pm_new); 

                    if (it2 == pms.end()) { 

                        open_list.push(pm_new); 

                        pms.insert(pm_new); 

                        _expansions++;

                    }

                    else {

                        delete pm_new; 

                    }

                }

            }

        }

        while (!open_list.empty()) {

            open_list.pop(); 

        }

        for (set<PuzzleMove*, PuzzleMoveBoardComp>::iterator it = pms.begin(); it != pms.end(); ++it) {

            delete *it; 

        }

        for (set<map<int, Board*> >::iterator it = frees_memory.begin(); it != frees_memory.end(); ++it) {

            for (map<int, Board*>::const_iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2) {

                delete it2->second; 

            }

        }

        delete b1; 

    }

std::deque<int> PuzzleSolver::getSolution() {

    return _solution;

}

int PuzzleSolver::getNumExpansions() {

    return _expansions;

}