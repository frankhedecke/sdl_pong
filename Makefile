CXXFLAGS  =  
LIBS      = -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDE   = /usr/include/SDL2/
PARAMETER = -std=c++11

SRC = src/ball.cc src/game.cc src/textures.cc

main : $(SRC)
	g++ $(SRC) $(PARAMETER) -I $(INCLUDE) $(LIBS) -o pong

