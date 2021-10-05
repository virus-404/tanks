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
    int getPlayerRespawnPoint_X();
    int getPlayerRespawnPoint_Y();
    int getEnemyRespawnPoint_X();
    int getEnemyRespawnPoint_Y();

   private:
    void respawnPointGenerator();
    int playerRespawnPoint_X;
    int playerRespawnPoint_Y;
    int enemyRespawnPoint_X;
    int enemyRespawnPoint_Y;
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

int Board::getPlayerRespawnPoint_X(){
    return playerRespawnPoint_X;
}

int Board::getPlayerRespawnPoint_Y(){
    return playerRespawnPoint_Y;
}

int Board::getEnemyRespawnPoint_X(){
    return enemyRespawnPoint_X;
}

int Board::getEnemyRespawnPoint_Y(){
    return enemyRespawnPoint_Y;
}

void Board::respawnPointGenerator() {
    int i = map.size() - 2;
    int j = 1;
    enemyRespawnPoint_X = i;
    enemyRespawnPoint_Y = j;
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
    playerRespawnPoint_X = i;
    playerRespawnPoint_Y = j;
    map[i][j] = 'P';

    while (!connected) {
        if (map[i + 1][j] == ' ' || map[i][j - 1] == ' ')
            connected = true;
        else if (map[i][j] == 'W')
            map[i][j] = ' ';
        i++;
    }
}
