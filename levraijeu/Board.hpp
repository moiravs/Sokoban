#include "Constants.hpp"
#include <vector>
#include <string>
class Board
{
private:
    /* data */
    struct tuple {
        size_t x_axis;
        size_t y_axis;
    };
    std::vector<std::vector<int>> matrix;
    std::vector<tuple> boxesPositions;
    std::vector<tuple> correctBoxesPositions;
    std::vector<std::vector<tuple>> teleportersPositions;
    int player_x;
    int player_y;

public:
    void move(int final_pos_x, int final_pos_y);
    bool check_move(int final_pos_x, int final_pos_y);
    std::vector<std::vector<int>> getBoard();
    std::string readFileIntoString(std::string fileName);
    void createBoard(std::string fileContent);
    void printBoard();
};