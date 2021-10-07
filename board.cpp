#include <iostream>
#include <vector>

#include "maze.cpp"
#pragma once

using namespace std;

typedef std::vector<std::vector<char>> Map;
typedef std::vector<char> Row;

class Board {
   public:
    Map map;
    Board(int, int);
    bool isValid(int, int, char);
    void setPositionBoard(int x, int y, char id);

   private:
    int posP[2] = {};
    int posE[2] = {};
    void respawnPointGenerator();
    bool isOccupied(int, int, char);
};

Board::Board(int height, int width) {
    Maze maze;
    Row row = Row(width - 1);

    srand(time(0));
    for (int i = 0; i < height - 2; ++i) map.push_back(row);

    maze.maze(map);
    respawnPointGenerator();
    maze.showMaze(map);
}

void Board::respawnPointGenerator() {
    int i = map.size() - 2;
    int j = 1;
    map[i][j] = 'E';
    bool connected = false;

    while (!connected) {
        if (map[i - 1][j] == ' ' || map[i][j + 1] == ' ')
            connected = true;
        else if (map[i][j] == 'X')
            map[i][j] = ' ';
        i--;
    }

    connected = false;
    i = 1;
    j = map.size() - 2;
    map[i][j] = 'P';

    while (!connected) {
        if (map[i + 1][j] == ' ' || map[i][j - 1] == ' ')
            connected = true;
        else if (map[i][j] == 'X')
            map[i][j] = ' ';
        i++;
    }
}

bool Board::isValid(int x, int y, char id) {
    if ((map[x][y] == ' ' || map[x][y] == 'P' || map[x][y] == 'E') && !isOccupied(x,y,id)) {
        if (id == 'P') cout << "MAP ..> " << map[x][y] << " Coord: " << x << " " << y << endl;
        if ((map[x][y] == 'P' && id == 'E') || (map[x][y] == 'E' && id == 'P')) {  // Winner is Enemy
            cout << "Winner is " << id << endl;
        }
        return true;
    } else {
        return false;
    }
}

void Board::setPositionBoard(int x, int y, char id) {
    if (id == 'P') {
        posP[0] = x;
        posP[1] = y;
    } else if (id == 'E') {
        posE[0] = x;
        posE[1] = y;
    }
}

bool Board::isOccupied(int x, int y, char id) {
    if (id == 'P') 
     return x == this->posE[0] && y == this->posE[1];
    else 
     return x == this->posP[0] && y == this->posP[1];
}
