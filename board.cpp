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

   private:
    void respawnPointGenerator();
    bool isOccupied(int, int);
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
        else if (map[i][j] == 'W')
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
        else if (map[i][j] == 'W')
            map[i][j] = ' ';
        i++;
    }
}

bool Board::isValid(int x, int y, char id) {
    if (map[x][y] == ' ' && !isOccupied(x, y))
    {
        if (map[x][y] == 'P' && id == 'E')
        { // Winner is Enemy
            cout << "Winner is " << id << endl;
            return true;
        }
        else if (map[x][y] == 'E' && id == 'P')
        { // Winner is Player
            cout << "Winner is " << id << endl;
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return false;
    }
    
}

bool Board::isOccupied(int x, int y) {
    return false;
}
