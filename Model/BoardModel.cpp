/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "BoardModel.hpp"

std::string BoardModel::readFileIntoString()
{
    std::cout << this->filename << std::endl;
    std::ifstream ifs(this->filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

std::vector<std::vector<LogicCell *>> BoardModel::getLogicCellVector()
{
    return this->LogicCellVector;
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
/*
bool BoardModel::check_if_blocked(int i, int j)
{
    std::vector<std::vector<int, int>> moinsplus = {{0, -1}, {-1, 0}};
    for (auto move : moinsplus)
    {
        if ((0 < i + move[0]) && (i + move[0] < this->LogicCellVector.size()) && (0 < j + move[1]) && (j + move[1]) < this->LogicCellVector[0].size()){
            if
        }
    }
}*/

bool BoardModel::isFailure()
{
    for (size_t i = 0; i < LogicCellVector.size(); i++)
    {
        for (size_t j = 0; j < LogicCellVector[0].size(); j++)
        {
            if (LogicCellVector[i][j]->hasBox())
            {
                if ((i == 0 && j == 0) || (i == 0 && j == LogicCellVector.size() - 1) || (i == LogicCellVector[0].size() && j == 0) || (i == LogicCellVector[0].size() - 1 && j == LogicCellVector.size() - 1))
                    LogicCellVector[i][j]->setBoxblocked();

                // TODO: check if outside the board
                // si la boite est bloquée par des murs ou par une boite bloquée
                else if (((LogicCellVector[i][j - 1]->isBlocked()) && (LogicCellVector[i - 1][j]->isBlocked())) || ((LogicCellVector[i - 1][j]->isBlocked()) && (LogicCellVector[i][j + 1]->isBlocked())) || ((LogicCellVector[i][j + 1]->isBlocked()) && (LogicCellVector[i + 1][j]->isBlocked())) || ((LogicCellVector[i + 1][j]->isBlocked()) && (LogicCellVector[i][j - 1]->isBlocked())))
                {
                    LogicCellVector[i][j]->setBoxblocked();
                }
                else
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void BoardModel::createBoard(std::string fileContent)
{
    this->LogicCellVector.clear();
    std::vector<LogicCell *> line;
    for (size_t index = 0; index < fileContent.size(); index++)
    {
        switch (fileContent[index])
        {
        case 'l':
        {
            std::string minpas = "";
            while (fileContent[index] != '\n')
            {
                index++;
                minpas += fileContent[index];
            }
            this->minpas = atoi(minpas.c_str());
            break;
        }
        case 'm':
        {
            std::string limitpas = "";
            while (fileContent[index] != '\n')
            {
                index++;
                limitpas += fileContent[index];
            }
            this->limitpas = atoi(limitpas.c_str());
            break;
        }
        case '\n':
        case '\0':
        {
            this->LogicCellVector.push_back(line);
            line.clear();
            break;

        case ' ':
            break;
        default:
        {
            LogicCell *logiccell;
            int charcontent = fileContent[index] - '0';
            switch (charcontent)
            {
            case EMPTY:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Normal);
                break;
            }
            case PLAYER:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Normal);
                this->player->y = this->LogicCellVector.size();
                this->player->x = line.size();
                logiccell->setPlayer(player);
                break;
            }
            case BOX:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Normal);
                Box *box = new Box(this->LogicCellVector.size(), line.size());
                box->setColor(FL_BLUE);
                logiccell->setBox(box);
                break;
            }
            case RED_BOX - '0':
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Normal);
                Box *box = new Box(this->LogicCellVector.size(), line.size());
                box->setColor(FL_RED);
                logiccell->setBox(box);
                break;
            }
            case RED_BOX_FINAL_POS - '0':
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Box_final_pos);
                logiccell->setColor(FL_RED);
                break;
            }
            case WALL:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Wall);
                break;
            }

            case TELEPORTATION:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Teleportation);
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
                    this->setFirstTeleportation(false);
                }
                break;
            }
            case LIGHT_BOX:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Normal);
                Box *box = new Box(this->LogicCellVector.size(), line.size());
                box->setLight(true);
                logiccell->setBox(box);
                break;
            }
            case BOX_FINAL_POS:
            {
                logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), LogicCell::cellType::Box_final_pos);
                logiccell->setColor(FL_BLUE);
                break;
            }
            }
            line.push_back(logiccell);
            break;
        }
        }
        }
    }
}

bool BoardModel::end_of_party()
{
    for (size_t i = 0; i < LogicCellVector.size(); i++)
    {
        for (size_t j = 0; j < LogicCellVector[0].size(); j++)
        {
            if (!LogicCellVector[i][j]->isComplete())
                return false;
        }
    }
    return true;
}

bool BoardModel::isInBoard(int pos_y, int pos_x)
{
    return (0 <= pos_y && pos_y < (int)LogicCellVector.size()) && (0 <= pos_x && pos_x < (int)LogicCellVector[pos_y].size());
}

void BoardModel::teleport()
{
    if ((this->player->y == this->teleportation[0]->get_first_end()->getY()) && this->player->x == this->teleportation[0]->get_first_end()->getX())
    {
        LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
        LogicCellVector[this->teleportation[0]->get_second_end()->getY()][this->teleportation[0]->get_second_end()->getX()]->setPlayer(this->player);
        this->player->x = this->teleportation[0]->get_second_end()->getX();
        this->player->y = this->teleportation[0]->get_second_end()->getY();
    }
    else if ((this->player->x == this->teleportation[0]->get_second_end()->getX()) && this->player->y == this->teleportation[0]->get_second_end()->getY())
    {
        LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
        LogicCellVector[this->teleportation[0]->get_first_end()->getY()][this->teleportation[0]->get_first_end()->getX()]->setPlayer(this->player);
        this->player->x = this->teleportation[0]->get_first_end()->getX();
        this->player->y = this->teleportation[0]->get_first_end()->getY();
    }
}

void BoardModel::move(int final_player_pos_y, int final_player_pos_x)
{
    if (this->isInBoard(final_player_pos_y, final_player_pos_x) == false)
        return;
    if (LogicCellVector[final_player_pos_y][final_player_pos_x]->getType() == WALL)
        return;
    if (LogicCellVector[final_player_pos_y][final_player_pos_x]->hasBox())
    {
        int deplacement_x = final_player_pos_x - this->player->x, deplacement_y = final_player_pos_y - this->player->y;
        if (LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox()->getLight() == true)
        {
            if ((LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getBox()->getLight() == true) && (LogicCellVector[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x]->getType() != WALL))
            {
                LogicCellVector[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x]
                    ->setBox(LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getBox());
            }
            else if ((LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() != EMPTY) && (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() != BOX_FINAL_POS))
                return;
        }
        else if ((LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->hasBox()) && (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getBox()->getLight() == false))
            return;
        else if (LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]->getType() == WALL)
            return;
        LogicCellVector[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x]
            ->setBox(LogicCellVector[final_player_pos_y][final_player_pos_x]->getBox());
        LogicCellVector[final_player_pos_y][final_player_pos_x]->setBox(nullptr);
    }
    LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
    LogicCellVector[final_player_pos_y][final_player_pos_x]->setPlayer(this->player);
    this->player->y = final_player_pos_y;
    this->player->x = final_player_pos_x;
    this->pas += 1;
}

void BoardModel::move_to(int x, int y)
{
    if ((x == this->player->x) || (y == this->player->y))
    {
        int deplacement_x = 0;
        int deplacement_y = 0;
        if (y > this->player->y)
            deplacement_y = 1;
        else if (y < this->player->y)
            deplacement_y = -1;
        else if (x > this->player->x)
            deplacement_x = 1;
        else if (x < this->player->x)
            deplacement_x = -1;
        while (!this->LogicCellVector[this->player->y + deplacement_y][this->player->x + deplacement_x]->hasBox() && (this->player->y != y || this->player->x != x))
        {
            this->pas += 1;
            this->LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
            this->LogicCellVector[this->player->y + deplacement_y][this->player->x + deplacement_x]->setPlayer(this->player);
            this->player->y = this->player->y + deplacement_y;
            this->player->x = this->player->x + deplacement_x;
        }
    }
}
