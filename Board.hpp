#ifndef BOARD_HPP
#define BOARD_HPP

#include "Constants.hpp"

class BoardModel
{
public:
    /* data */
    struct tuple
    {
        size_t y_axis;
        size_t x_axis;
    };
    std::vector<std::vector<int>> matrix;
    std::vector<std::tuple<int,int>> boxesPositions;
    std::vector<std::tuple<int, int>> correctBoxesPositions;
    std::vector<std::vector<std::tuple<int, int>>> teleportersPositions;
    int player_x;
    int player_y;
    std::string filename;
    int pas = 0;
    int minpas = 0;
    int limitpas = 0;
    bool endofparty = false;
    bool winorlose;

public:
    BoardModel(std::string filename)
    {
        this->filename = filename;
    }
    void maxpasandlimit();
    bool end_of_party();
    std::vector<std::vector<int>> getMatrix();
    bool move(int final_pos_y, int final_pos_x);
    bool check_move(int final_pos_y, int final_pos_x);
    std::vector<std::vector<int>> getBoard();
    std::string readFileIntoString();
    void createBoard(std::string fileContent);
    void printBoard();
    bool isInBoard(int pos_y, int pos_x);
    void updateBoxPositions();
};

#endif