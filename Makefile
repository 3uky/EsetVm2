SRC_DIR = src
OBJ_DIR = obj

ELF = esetvm2
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC = g++
INCLUDES = -Iinclude
CFLAGS   = -Wall -g -pthread
LDLIBS   = -lm

$(ELF): $(OBJ) 
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

-include $(OBJ:.o=.d)
