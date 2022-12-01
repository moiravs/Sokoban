#ifndef BOARD_HPP
#define BOARD_HPP
#include "Box.hpp"
#include "Player.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include <tuple>



class Teleportation{
    //TODO: teleportation
    std::tuple<int, int> teleportation_a;
    std::tuple<int, int> teleporation_b;
    bool pourpasfaireinfini = false;
};


class BoardModel
{
public:
    /* data */
    std::vector<Teleportation> teleportation;
    std::vector<std::vector<int>> matrix;
    std::vector<Box> boxesPositions;
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
    bool isFailure();

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