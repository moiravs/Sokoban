#ifndef BOARD_HPP
#define BOARD_HPP
#include "BoxModel.hpp"
#include "Player.hpp"
#include "../Constants.hpp"
#include "Player.hpp"
#include "Teleportation.hpp"
#include <tuple>
#include "LogicCell.hpp"

class BoardModel
{
private:
    bool first_teleportation_on_board = false;

public:
    // TODO : destructeur
    // TODO :TOUT EN PRIVATE
    std::vector<Teleportation *> teleportation;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<LogicCell *>> LogicCellVector;
    std::string filename;
    int pas = 0;
    int minpas = 0;
    int limitpas = 0;
    bool endofparty = false;
    bool winorlose;
    Player *player;
    BoardModel(std::string filename)
    {
        this->filename = filename;
        Player *player = new Player();
        this->player = player;
    }
    void maxpasandlimit();
    bool end_of_party();
    bool isFailure();
    void teleport();
    bool check_if_blocked(int i, int j);
    std::vector<std::vector<int>> getMatrix();
    void move(int final_pos_y, int final_pos_x);
    bool check_move(int final_pos_y, int final_pos_x);
    std::string readFileIntoString();
    void createBoard(std::string fileContent);
    void setFirstTeleportation(bool value);
    bool getFirstTeleportation();
    bool isInBoard(int pos_y, int pos_x);
};

#endif