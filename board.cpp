#include <iostream>
#include <vector>
#include "./maze.cpp"

using namespace std;

typedef std::vector<std::vector<char>> Map;
typedef std::vector<char> Row;

class Board
{
    public:
        Map map;
        Board(int, int);
};

Board::Board(int height, int width)
{
    Maze maze;
    Row row = Row(width);
    
    srand(time(0));
    for (int i = 0; i < height; ++i) map.push_back(row);
    
    maze.maze(map);
    maze.showMaze(map);

}

