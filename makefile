compile:
	g++ game.cpp -o game.o -lglut -lGLU -lGL -lm
all: 
	g++ game.cpp -o game.o -lglut -lGLU -lGL -lm
	./game.o
clean:
	rm game.o
mac:
	g++ -std=c++11 -o labyrinth game.cpp -framework OpenGL -framework GLUT -lm
	./labyrinth
cleanmac:
	rm labyrinth