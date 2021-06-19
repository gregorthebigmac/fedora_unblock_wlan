# OBJS specifies which files to compile as part of the project
OBJS = keep_bt_down.cpp

# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
#LINKER_FLAGS = ""

# OBJ_NAME specifies the name of our executable
OBJ_NAME = keep_bt_down

# This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)