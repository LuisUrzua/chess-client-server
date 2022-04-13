SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

EXE := $(patsubst %,$(BIN_DIR)/%.exe,client server)
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(subst $(SRC_DIR),$(OBJ_DIR),$(SRC:.cpp=.o))
DEP := $(OBJ:.o=.d)

CLIENT_OBJ := $(filter-out $(OBJ_DIR)/server.o,$(OBJ))
SERVER_OBJ := $(filter-out $(OBJ_DIR)/client.o,$(OBJ))

.PHONY: clean client server

all: $(EXE)
client: $(BIN_DIR)/client.exe
server: $(BIN_DIR)/server.exe

CXX      := g++
CPPFLAGS := -I$(PWD) -MMD -MP
CXXFLAGS := -std=c++17
LDFLAGS  := -L /usr/lib/x86_64-linux-gnu
CFLAGS   := -Wall


$(BIN_DIR)/client.exe: $(CLIENT_OBJ)
$(BIN_DIR)/server.exe: $(SERVER_OBJ)

$(EXE): | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(DEP)
