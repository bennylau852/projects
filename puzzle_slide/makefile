CXX=g++
CXXFLAGS=-g -Wall
BIN_DIR  = bin


all: $(BIN_DIR)/puzzle 

$(BIN_DIR)/puzzle: $(BIN_DIR)/.dirstamp $(BIN_DIR)/puzzle.o $(BIN_DIR)/board.o $(BIN_DIR)/puzzle_solver.o $(BIN_DIR)/puzzle_move.o $(BIN_DIR)/puzzle_mh_heur.o $(BIN_DIR)/puzzle_oop_heur.o $(BIN_DIR)/puzzle_bfs_heur.o 
	$(CXX) $(CXXFLAGS) $(BIN_DIR)/puzzle.o $(BIN_DIR)/board.o $(BIN_DIR)/puzzle_solver.o $(BIN_DIR)/puzzle_move.o $(BIN_DIR)/puzzle_mh_heur.o $(BIN_DIR)/puzzle_oop_heur.o $(BIN_DIR)/puzzle_bfs_heur.o -o puzzle

$(BIN_DIR)/puzzle.o: $(BIN_DIR)/.dirstamp puzzle.cpp 
	$(CXX) $(CXXFLAGS) -c puzzle.cpp -o $(BIN_DIR)/puzzle.o

$(BIN_DIR)/puzzle_solver.o: $(BIN_DIR)/.dirstamp puzzle_solver.cpp 
	$(CXX) $(CXXFLAGS) -c puzzle_solver.cpp -o $(BIN_DIR)/puzzle_solver.o

$(BIN_DIR)/puzzle_mh_heur.o: $(BIN_DIR)/.dirstamp puzzle_mh_heur.cpp 
	$(CXX) $(CXXFLAGS) -c puzzle_mh_heur.cpp -o $(BIN_DIR)/puzzle_mh_heur.o

$(BIN_DIR)/puzzle_bfs_heur.o: $(BIN_DIR)/.dirstamp puzzle_bfs_heur.cpp
	$(CXX) $(CXXFLAGS) -c puzzle_bfs_heur.cpp -o $(BIN_DIR)/puzzle_bfs_heur.o

$(BIN_DIR)/puzzle_move.o: $(BIN_DIR)/.dirstamp puzzle_move.cpp
	$(CXX) $(CXXFLAGS) -c puzzle_move.cpp -o $(BIN_DIR)/puzzle_move.o

$(BIN_DIR)/puzzle_oop_heur.o: $(BIN_DIR)/.dirstamp puzzle_oop_heur.cpp 
	$(CXX) $(CXXFLAGS) -c puzzle_oop_heur.cpp -o $(BIN_DIR)/puzzle_oop_heur.o

$(BIN_DIR)/board.o: $(BIN_DIR)/.dirstamp  board.cpp 
	$(CXX) $(CXXFLAGS) -c board.cpp -o $(BIN_DIR)/board.o
	
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $(BIN_DIR)/.dirstamp

clean:
	-@rm -rf $(BIN_DIR)
	-rm puzzle