#ifndef BOARD_HPP
#define BOARD_HPP

#include "Constants.hpp"
#include <tuple>


class Teleportation{
    std::tuple<int, int> teleportation_a;
    std::tuple<int, int> teleporation_b;
    bool pourpasfaireinfini = false;
};
class Player
{

    int x;
    int y;

public:
    void setX(int x)
    {
        this->x = x;
    }
    void setY(int y)
    {
        this->y = y;
    }
    int getX()
    {
        return (this->x);
    }
    int getY()
    {
        return (this->y);
    }
};
class BoardModel
{
public:
    /* data */
    std::vector<Teleportation> teleportation;
    std::vector<std::vector<int>> matrix;
    std::vector<std::tuple<int,int>> boxesPositions;
    std::vector<std::tuple<int, int>> correctBoxesPositions;
    std::vector<std::vector<std::tuple<int, int>>> teleportersPositions;

    std::string filename;
    int pas = 0;
    int minpas = 0;
    int limitpas = 0;
    bool endofparty = false;
    bool winorlose;
    Player * player;
public:
    BoardModel(std::string filename)
    {
        this->filename = filename;
        Player * player = new Player();
        this->player = player;
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