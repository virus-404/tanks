all: 
	gcc board.cpp -o board -lglut -lGLU -lGL -lm
clean:
	rm board
