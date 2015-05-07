CXX=g++
CXXFLAGS=-g -Wall
BIN_DIR  = bin


all: $(BIN_DIR)/tiles 

$(BIN_DIR)/tiles: $(BIN_DIR)/.dirstamp $(BIN_DIR)/tiles.o 
	$(CXX) $(CXXFLAGS) $(BIN_DIR)/tiles.o -o tiles

$(BIN_DIR)/tiles.o: $(BIN_DIR)/.dirstamp tiles.cpp 
	$(CXX) $(CXXFLAGS) -c tiles.cpp -o $(BIN_DIR)/tiles.o
	
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $(BIN_DIR)/.dirstamp

clean:
	-@rm -rf $(BIN_DIR)
	-rm tiles