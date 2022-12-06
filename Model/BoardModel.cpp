#include "BoardModel.hpp"
#include "Player.cpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit()
#include <fstream>
#include <algorithm>
#include <tuple>

std::string BoardModel::readFileIntoString()
{
    std::cout << this->filename;
    std::ifstream ifs(this->filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

std::vector<std::vector<int>> BoardModel::getBoard()
{
    return (this->matrix);
}

void BoardModel::setFirstTeleportation(bool value)
{
    if (!(this->first_teleportation_on_board == value))
        this->first_teleportation_on_board = value;
}

bool BoardModel::getFirstTeleportation()
{
    return this->first_teleportation_on_board;
}

bool BoardModel::isFailure()
{

    for (size_t i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            if (LogicCellVector[i][j]->hasBox())
            {
                if ((i == 0 && j == 0) || (i == 0 && j == matrix.size() - 1) || (i == matrix[0].size() && j == 0) || (i == matrix[0].size() - 1 && j == matrix.size() - 1))
                    LogicCellVector[i][j]->setBoxblocked();
                // TODO: check if outside the board
                // si la boite est bloquée par des murs ou par une boite bloquée
                else if (((LogicCellVector[i][j - 1]->isBlocked()) && (LogicCellVector[i - 1][j]->isBlocked())) || ((LogicCellVector[i - 1][j]->isBlocked()) && (LogicCellVector[i][j + 1]->isBlocked())) || ((LogicCellVector[i][j + 1]->isBlocked()) && (LogicCellVector[i + 1][j]->isBlocked())) || ((LogicCellVector[i + 1][j]->isBlocked()) && (LogicCellVector[i][j - 1]->isBlocked())))
                {
                    LogicCellVector[i][j]->setBoxblocked();
                }
                else
                    return false;
            }
        }
    }
    return true;
}

void BoardModel::createBoard(std::string fileContent)
{

    std::vector<int> line;
    this->matrix.clear();
    // TODO : capter comment faire un vector dynamique ig
    std::vector<std::vector<LogicCell *>> LogicCellVectortest(8, std::vector<LogicCell *>(8));
    std::cout << fileContent;
    for (size_t index = 0; index < fileContent.size(); index++)
    {
        if ((fileContent[index] == 'l'))
        {
            std::string minpas = "";
            while (fileContent[index] != '\n')
            {
                index++;
                minpas += fileContent[index];
            }
            this->minpas = atoi(minpas.c_str());
        }
        else if ((fileContent[index] == 'm'))
        {
            std::string limitpas = "";
            while (fileContent[index] != '\n')
            {
                index++;
                limitpas += fileContent[index];
            }
            this->limitpas = atoi(limitpas.c_str());
        }
        else if ((fileContent[index] == '\n') || (fileContent[index] == '\0'))
        {
            this->matrix.push_back(line);
            line.clear();
        }
        else if (fileContent[index] != ' ')
        {
            LogicCell *logiccell;
            int charcontent = fileContent[index] - '0';
            if (charcontent == EMPTY)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Normal);
            }
            else if (charcontent == PLAYER)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Normal);
                this->player->setY(this->matrix.size());
                this->player->setX(line.size());
                logiccell->setPlayer(player);
            }

            else if (charcontent == BOX)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Normal);
                Box *box = new Box(this->matrix.size(), line.size());
                logiccell->setBox(box);
            }
            else if (charcontent == WALL)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Wall);
            }

            else if (charcontent == TELEPORTATION)
            {
                puts("blockeqd");
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Teleportation);
                Teleportation *firstTeleportationCell;

                if (this->getFirstTeleportation() == false)
                {
                    firstTeleportationCell = new Teleportation(logiccell);
                    this->setFirstTeleportation(true);
                }
                else
                {
                    firstTeleportationCell->set_second_end(logiccell);
                    this->teleportation.push_back(firstTeleportationCell);
                }
                puts("blockeqdhruji");
            }

            else if (charcontent == LIGHT_BOX)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Normal);
                Box *box = new Box(this->matrix.size(), line.size());
                box->light = true;
                logiccell->setBox(box);
            }
            else if (charcontent == BOX_FINAL_POS)
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Box_final_pos);
            }
            else
            {
                logiccell = new LogicCell(this->matrix.size(), line.size(), LogicCell::cellType::Normal);
            }
            LogicCellVectortest[this->matrix.size()][line.size()] = logiccell;
            line.push_back(charcontent);
        }
    }
    this->LogicCellVector = LogicCellVectortest;
}

bool BoardModel::end_of_party()
{
    for (size_t i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 7; j++)
        {
            if (!LogicCellVector[i][j]->isComplete())
                return false;
        }
    }
    return true;
}

bool BoardModel::check_move(int final_pos_y, int final_pos_x)
{
    if ((final_pos_y < 0) || (final_pos_x < 0))
        return false;
    if ((final_pos_y > (int)matrix.size()) || (final_pos_x > (int)matrix[0].size()))
        return false;
    return true;
}

bool BoardModel::isInBoard(int pos_y, int pos_x)
{
    return (0 <= pos_y && pos_y < (int)matrix.size()) && (0 <= pos_x && pos_x < (int)matrix[pos_y].size());
}

void BoardModel::teleport()
{
    std::cout << "player x" << this->player->getX() << "player y" << this->player->getY() << std::endl;
    std::cout << "tele x" << this->teleportation[0]->get_second_end()->getX() << "tele y" << this->teleportation[0]->get_second_end()->getY() << std::endl;
    if ((this->player->getY() == this->teleportation[0]->get_first_end()->getY()) && this->player->getX() == this->teleportation[0]->get_first_end()->getX())
    {
        LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
        LogicCellVector[this->teleportation[0]->get_second_end()->getY()][this->teleportation[0]->get_second_end()->getX()]->setPlayer(this->player);
        this->player->setX(this->teleportation[0]->get_second_end()->getX());
        this->player->setY(this->teleportation[0]->get_second_end()->getY());
    }
    else if ((this->player->getX() == this->teleportation[0]->get_second_end()->getX()) && this->player->getY() == this->teleportation[0]->get_second_end()->getY())
    {
        LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
        LogicCellVector[this->teleportation[0]->get_first_end()->getY()][this->teleportation[0]->get_first_end()->getX()]->setPlayer(this->player);
        this->player->setX(this->teleportation[0]->get_first_end()->getX());
        this->player->setY(this->teleportation[0]->get_first_end()->getY());
    }
}

bool BoardModel::move(int final_player_pos_y, int final_player_pos_x)
{
    if (this->isInBoard(final_player_pos_y, final_player_pos_x) == false)
        return false;
    int deplacement_x = final_player_pos_x - this->player->getX(), deplacement_y = final_player_pos_y - this->player->getY();
    if (LogicCellVector[final_player_pos_y][final_player_pos_x]->hasBox())
    {
        if (LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox()->light == true)
        {
            if (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getBox()->light == true)
            {
                // TODO : or teleportation
                if ((LogicCellVector[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x]->getType() == EMPTY) || (LogicCellVector[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x]->getType() == BOX_FINAL_POS))
                {
                    LogicCellVector[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x]
                        ->setBox(LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getBox());
                    LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]
                        ->setBox(LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox());
                    LogicCellVector[final_player_pos_y][final_player_pos_x]->setBox(nullptr);
                    LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
                    LogicCellVector[final_player_pos_y][final_player_pos_x]->setPlayer(this->player);
                    this->player->setY(final_player_pos_y);
                    this->player->setX(final_player_pos_x);
                }
            }
            else if ((LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() == EMPTY) || (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() == BOX_FINAL_POS))
            {
                LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]
                    ->setBox(LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox());
                LogicCellVector[final_player_pos_y][final_player_pos_x]->setBox(nullptr);
                LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
                LogicCellVector[final_player_pos_y][final_player_pos_x]->setPlayer(this->player);
                this->player->setY(final_player_pos_y);
                this->player->setX(final_player_pos_x);
            }
            else
            {
                return false;
            }
        }
        else if ((LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() == EMPTY) || (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() == BOX_FINAL_POS))
        {
            LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]
                ->setBox(LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox());
            LogicCellVector[final_player_pos_y][final_player_pos_x]->setBox(nullptr);
            LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
            LogicCellVector[final_player_pos_y][final_player_pos_x]->setPlayer(this->player);
            this->player->setY(final_player_pos_y);
            this->player->setX(final_player_pos_x);
        }
    }
    else if ((LogicCellVector[final_player_pos_y][final_player_pos_x]->getType() == EMPTY) || (LogicCellVector[final_player_pos_y][final_player_pos_x]->getType() == BOX_FINAL_POS) || (LogicCellVector[final_player_pos_y][final_player_pos_x]->getType() == TELEPORTATION))
    {
        LogicCellVector[this->player->getY()][this->player->getX()]->setPlayer(nullptr);
        LogicCellVector[final_player_pos_y][final_player_pos_x]->setPlayer(this->player);
        this->player->setY(final_player_pos_y);
        this->player->setX(final_player_pos_x);
    }
}
