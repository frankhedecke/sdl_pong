CXXFLAGS  =  
LIBS      = -lSDL2 -lSDL2_image -lSDL2_ttf
INCLUDE   = /usr/include/SDL2/
PARAMETER = -std=c++11

SRC = src/ball.cc src/cleanup.cc src/game.cc src/textures.cc src/vector_screen.cc src/scene.cc src/scene_pong.cc src/scene_manager.cc

main : $(SRC)
	g++ $(SRC) $(PARAMETER) -I $(INCLUDE) $(LIBS) -o pong

