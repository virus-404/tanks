#include <iostream>
#include <vector>
#include "./maze.cpp"

using namespace std;

typedef std::vector<std::vector<char>> Map;
typedef std::vector<char> Row;

class Board {
   public:
    Map map;
    Board(int, int);

   private:
    void respawnPointGenerator();
};

Board::Board(int height, int width) {
    Maze maze;
    Row row = Row(width);

    srand(time(0));
    for (int i = 0; i < height; ++i) map.push_back(row);

    maze.maze(map);
    respawnPointGenerator();
    maze.showMaze(map);
}

void Board::respawnPointGenerator() {
    map[map.size()-2][1] = 'E';
    map[1][map.size() -2] = 'P';

}
