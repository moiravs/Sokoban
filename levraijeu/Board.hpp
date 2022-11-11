#include <vector>
#include <string>
class Board
{
private:
    /* data */
    std::vector<std::vector<int>> matrix;
    int player_x;
    int player_y;

public:
    void move( int final_pos_x, int final_pos_y);
    bool check_move(int final_pos_x, int final_pos_y);
    std::vector<std::vector<int>> getBoard();
        std::string readFileIntoString(std::string fileName);
    void createBoard(std::string fileContent);
    void printBoard();
};