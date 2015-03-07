## Directories to search include and source files
INC_DIR := include
SRC_DIR := src

## Directories to build files into
OBJ_DIR := obj
BIN_DIR := bin

## List of all c++ files to compile
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)

## List of all object files to generate
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(CPP_FILES:$(SRC_DIR)/%.cpp=%.o))

## Compiler, compiler and linker flags and libaries to use
CXX := g++
CXXLIBS := 
LDLIBS := -lSDL
CXXFLAGS := -I $(INC_DIR) -std=c++11 -Wconversion $(CXXLIBS) 
LDFLAGS := --std=c++11 $(LDLIBS)

## Build the application
all: $(BIN_DIR)/SolarEclipse

$(BIN_DIR)/SolarEclipse: $(OBJ_FILES) | $(BIN_DIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)
	
## Clean up everything
clean:
	rm -rf obj
	rm -rf bin

## Include auto-generated dependencies rules
-include $(OBJ_FILES:.o=.d)
