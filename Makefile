INCLUDE_DIR = include
SRC_DIR = src
EXE_NAME = ga

compile: $(SRC_DIR)/*.c
	g++ $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)

debug: $(SRC_DIR)/*.c
	g++ -g $(SRC_DIR)/*.c -I$(INCLUDE_DIR) -o $(EXE_NAME)
