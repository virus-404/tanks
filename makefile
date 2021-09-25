all: 
	gcc board.cpp -o board.o -lglut -lGLU -lGL -lm
clean:
	rm board 