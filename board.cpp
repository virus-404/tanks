#include <iostream>
#include <vector>
#include "./maze.cpp"

using namespace std;

typedef std::vector<std::vector<char>> Map;
typedef std::vector<char> Row;

class Board
{
    private:
        Map map;
    public:
        Board(int, int);
        void printBoard();
};

Board::Board(int height, int width)
{
    Maze maze;
    srand(time(0));
    Row row = Row(width);
    Map tmp;
    for (int i = 0; i < height; ++i) tmp.push_back(row);
    maze.maze(tmp);
    maze.showMaze(tmp);

}
void Board::printBoard()
{
}


