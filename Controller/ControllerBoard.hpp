#ifndef CONTROLLERBOARD_HPP
#define CONTROLLERBOARD_HPP

#include "../Constants.hpp"
#include "../Model/BoardModel.hpp"

class ControllerBoard
{
private:
    std::shared_ptr<BoardModel> boardModel;

public:
    ControllerBoard() {}
    ControllerBoard(std::shared_ptr<BoardModel> boardModel)
    {
        this->boardModel = boardModel;
    };
    int board_handle(int event);
    void move_to(int x, int y)
    {
        puts("ahhhh");
        int player_x = this->boardModel->player->getX();
        int player_y = this->boardModel->player->getY();
        std::cout << "position" << x << y << "player" << player_x << player_y << std::endl;

        if (x == player_x)
        {
            int deplacement;
            if (y > player_y)
                deplacement = 1;
            else if (y < player_y)
                deplacement = -1;
            if (y != player_y)
            {
                while (!this->boardModel->LogicCellVector[player_y + deplacement][player_x]->hasBox() && player_y != y)
                {
                    this->boardModel->LogicCellVector[this->boardModel->player->getY()][this->boardModel->player->getX()]->setPlayer(nullptr);
                    this->boardModel->LogicCellVector[player_y + deplacement][player_x]->setPlayer(this->boardModel->player);
                    this->boardModel->player->setY(player_y + deplacement);
                    this->boardModel->player->setX(player_x);
                    player_x = this->boardModel->player->getX();
                    player_y = this->boardModel->player->getY();
                }
            }
        }
        else if (y == player_y)
        {
            puts("bouuuufeiuuuuu");

            int deplacement;
            if (x > player_x)
                deplacement = 1;
            else if (x < player_x)
                deplacement = -1;
            if (x != player_x)
            {
                puts("bouuuuuuuuu");
                while (!this->boardModel->LogicCellVector[player_y][player_x + deplacement]->hasBox() && player_x != x)
                {
                    puts("hiiigorhefj");
                    this->boardModel->LogicCellVector[this->boardModel->player->getY()][this->boardModel->player->getX()]->setPlayer(nullptr);
                    this->boardModel->LogicCellVector[player_y][player_x + deplacement]->setPlayer(this->boardModel->player);
                    this->boardModel->player->setY(player_y);
                    this->boardModel->player->setX(player_x + deplacement);
                    player_x = this->boardModel->player->getX();
                    player_y = this->boardModel->player->getY();
                }
            }
        }
    }
};

#endif
