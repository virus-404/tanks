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
    int* getRespawnPlayer();
    int* getRespawnEnemy();
    bool movementIsValid(int*,char*);
    char didIWin(char*);

   private:
    void respawnPointGenerator();
    int playerPosition[2];
    int enemyPosition[2];
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
    map[1][map.size() - 2] = 'P';

    while (!connected) {
        if (map[i + 1][j] == ' ' || map[i][j - 1] == ' ')
            connected = true;
        else if (map[i][j] == 'W')
            map[i][j] = ' ';
        i++;
    }
}

int* Board::getRespawnPlayer() {
    return new int[2]{1, (int)map.size() - 2};
}
int* Board::getRespawnEnemy() {
    return new int[2]{(int)map.size() - 2, 1};
}