CXXFLAGS  =  
LIBS      = -lSDL2
INCLUDE   = /usr/include/SDL2/
PARAMETER = -std=c++11

SRC  = src/game.cc

main : $(SRC)
	g++ $(SRC) $(PARAMETER) -I $(INCLUDE) $(LIBS) -o pong

