SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(BIN_DIR)/client.exe
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:.cpp=.o))
DEP := $(OBJ:.o=.d)

.PHONY: clean

all: $(EXE)

CXX      := g++
CPPFLAGS := -I$(PWD) -MMD -MP
CXXFLAGS := -std=c++17
LDFLAGS  := -L /usr/lib/x86_64-linux-gnu
CFLAGS   := -Wall

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(DEP)
