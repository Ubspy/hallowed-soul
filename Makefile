# Directory vars
SRC_DIR = src
OBJ_DIR = obj

EXE_NAME = Gaming.out

# OBJS specifies which files to compile as part of the project
# The second var tells make to turn all the file extentions into .o
# It takes the pattern %.cpp with % being anything in the src folder
# and turns it into %.o in the obj folder
GAME_SRC = $(wildcard $(SRC_DIR)/*.cpp)
GAME_HEADERS = $(GAME_SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.h)
GAME_OBJS = $(GAME_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Guarding incase there is no directory for the objs directory
dir_guard=@mkdir -p $(@D)

# The compiler we're using
CC = g++

# Specifies the additional compilation options we're using
CXX_FLAGS = -Wall -std=c++11

DEBUG_FLAGS = -g

# Specifies the libraries we're linking against
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 

# This is the target that compiles our executable
# The ^ variable is all the dependencies, and the @ variable is the target
$(EXE_NAME) : $(GAME_OBJS) 
	$(CC) $^ $(CXX_FLAGS) $(LINKER_FLAGS) -o $@

# Target for release, with no additional debug information
# TODO: Maybe package the game in a folder with all the assets needed?
release : $(GAME_OBJS)
	$(CC) $^ $(CXX_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)

# Here we're gonna override the default make rule for turning cpp files into object files
# Because we need to make sure the obj files are compiled using the correct version
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(dir_guard)
	$(CC) $^ $(CXX_FLAGS) $(DEBUG_FLAGS) -c -o $@

clean:
	rm $(EXE_NAME) $(GAME_OBJS) $(COAL_OBJS)
