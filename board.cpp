#include <iostream>
#include <vector>

using namespace std;

typedef std::vector<std::vector<int>> Map;
Map createMap(int,int); 

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
   this->map = createMap(height, width);
}

void Board::printBoard()
{
    for (size_t i = 0; i < Board::map.size(); i++)
        for (size_t j = 0; j < Board::map[i].size(); j++)
            std::cout << map[i][j] << ' ';
}

Map createMap(int m, int n)
{
    
}

