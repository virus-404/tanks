all: 
	g++ game.cpp -o game.o -lglut -lGLU -lGL -lm
	./game.o
clean:
	rm game.o