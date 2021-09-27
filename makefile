all: 
	g++ game.cpp -o game.o -lglut -lGLU -lGL -lm
clean:
	rm game.o