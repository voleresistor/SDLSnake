# OBJS specifies which files to compile as part of the project
OBJS = SnakeGame.cpp SnakeGame_SDL.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w supresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf#-lSDL2_image

# OBJ_NAME specifies the name of our executable
OBJ_NAME = snake

# This is the target that compiles our executables
all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(OBJ_NAME)
