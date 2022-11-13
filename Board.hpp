#include "Constants.hpp"

class Board
{
public:
    /* data */
    struct tuple
    {
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
    bool Board::end_of_party();
    std::vector<std::vector<int>> getMatrix();
    void move(int final_pos_x, int final_pos_y);
    bool check_move(int final_pos_x, int final_pos_y);
    std::vector<std::vector<int>> getBoard();
    std::string readFileIntoString(std::string fileName);
    void createBoard(std::string fileContent);
    void printBoard();
    void updateBoxPositions();
};

/*
class ControllerBoard{
    private:
        Board board;
    public:
        ControllerBoard(std::shared_ptr<Board> board){
            Board = board
        };
};*/