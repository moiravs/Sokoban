#ifndef BOARD_HPP
#define BOARD_HPP

#include "Constants.hpp"

class BoardModel
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
    bool on_correct_box_pos = false;
    std::string filename;
    int pas = 0;

public:
    BoardModel(std::string filename)
    {
        this->filename = filename;
    }
    bool end_of_party();
    std::vector<std::vector<int>> getMatrix();
    void move(int final_pos_x, int final_pos_y);
    bool check_move(int final_pos_x, int final_pos_y);
    std::vector<std::vector<int>> getBoard();
    std::string readFileIntoString();
    void createBoard(std::string fileContent);
    void printBoard();
    bool isInBoard(int pos_x, int pos_y);
    void updateBoxPositions();
};

#endif