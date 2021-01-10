#OBJS specifies which files to compile as part of the project
OBJS = globals.cpp LTexture.cpp functions.cpp Bird.cpp Birds.cpp Bullet.cpp Gunner.cpp GTimer.cpp Intro.cpp Title.cpp GamePlay.cpp GameOver.cpp main.cpp

#CC specifies which compiler we're using
CXX = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
#-w suppresses all warnings
#-ggdb produce debugging information for use by GDB
CXX_FLAGS = -w -std=c++14 -ggdb

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

#OBJ_NAME specifies the name of our executable
OBJ_NAME = testing_SR

#This is the target that compiles our executable
all : $(OBJS)
	$(CXX) $(OBJS) $(CXX_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
