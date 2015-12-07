CXXFLAGS  =  
LIBS      = -lSDL2 -lSDL2_image
INCLUDE   = /usr/include/SDL2/
PARAMETER = -std=c++11

SRC  = src/game.cc src/textures.cc

main : $(SRC)
	g++ $(SRC) $(PARAMETER) -I $(INCLUDE) $(LIBS) -o pong

