/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "BoardModel.hpp"

std::string BoardModel::readFileIntoString()
{
    std::ifstream ifs(this->filename);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

bool BoardModel::isFailure()
{
    std::vector<std::vector<int>> move{{0, -1, -1, 0}, {-1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 0, -1}};
    bool allBoxes = true;
    for (int j = 0; j < (int)LogicCellVector.size(); j++)
    {
        for (int i = 0; i < (int)LogicCellVector[0].size(); i++)
        {
            if (LogicCellVector[i][j]->hasBox() && (LogicCellVector[i][j]->isBlocked() == false))
            {
                for (auto a : move)
                {
                    if (this->isInBoard(i + a[0], j + a[1]) == false && this->isInBoard(i + a[2], j + a[3]) == false)
                    {
                        LogicCellVector[i][j]->setBoxblocked(true);
                    }
                    else if (this->isInBoard(i + a[0], j + a[1]) && this->isInBoard(i + a[2], j + a[3]))
                    {
                        if (LogicCellVector[i + a[0]][j + a[1]]->isBlocked() && LogicCellVector[i + a[2]][j + a[3]]->isBlocked())
                        {
                            LogicCellVector[i][j]->setBoxblocked(true);
                        }
                    }
                    else if (this->isInBoard(i + a[0], j + a[1]) && LogicCellVector[i + a[0]][j + a[1]]->isBlocked())
                    {
                        LogicCellVector[i][j]->setBoxblocked(true);
                    }
                    else if (this->isInBoard(i + a[2], j + a[3]) && LogicCellVector[i + a[2]][j + a[3]]->isBlocked())
                    {
                        LogicCellVector[i][j]->setBoxblocked(true);
                    }
                }
                if (LogicCellVector[i][j]->isBlocked() == false)
                    allBoxes = false;
            }
        }
    }
    if (allBoxes == false)
        return false;
    return true;
}

void BoardModel::createBoard(std::string fileContent)
{

    int index = 0;
    bool finish = false;
    while (!finish)
    {
        switch (fileContent[index])
        {
        case 'l':
        {
            std::string minimumSteps = "";
            while (fileContent[index] != '\n')
            {
                index++;
                minimumSteps += fileContent[index];
            }
            this->minimumSteps = atoi(minimumSteps.c_str());
            break;
        }
        case 'm':
        {
            std::string stepsLimit = "";
            while (fileContent[index] != '\n')
            {
                index++;
                stepsLimit += fileContent[index];
            }
            this->stepsLimit = atoi(stepsLimit.c_str());
            finish = true;
            break;
        }
        }
        index++;
    }
    this->createLogicCell(index--, fileContent);
}

void BoardModel::createLogicCell(int index, std::string fileContent)
{
    this->LogicCellVector.clear();
    this->teleportation.clear();
    std::vector<LogicCell *> line;
    bool tele = true;

    for (int ind = index; ind < (int)fileContent.size(); ind++)
    {
        switch (fileContent[ind])
        {
        case '\n':
        case '\0':
        {
            this->LogicCellVector.push_back(line);
            line.clear();
            break;
        }
        case EMPTY + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            line.push_back(logiccell);
            break;
        }
        case PLAYER + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            this->player->y = this->LogicCellVector.size();
            this->player->x = line.size();
            logiccell->setPlayer(player);
            line.push_back(logiccell);
            break;
        }
        case BOX + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            Box *box = new Box();
            box->color = FL_WHITE;
            logiccell->setBox(box);
            line.push_back(logiccell);
            break;
        }
        case RED_BOX:
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            Box *box = new Box();
            box->color = FL_RED;
            logiccell->setBox(box);
            line.push_back(logiccell);
            break;
        }
        case RED_BOX_FINAL_POS:
        {
            puts("ah");
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), BOX_FINAL_POS);
            logiccell->setColor(FL_RED);
            line.push_back(logiccell);
            break;
        }
        case BLUE_BOX:
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            Box *box = new Box();
            box->color = FL_BLUE;
            logiccell->setBox(box);
            line.push_back(logiccell);
            break;
        }
        case BLUE_BOX_FINAL_POS:
        {
            puts("ah");
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), BOX_FINAL_POS);
            logiccell->setColor(FL_BLUE);
            line.push_back(logiccell);
            break;
        }
        case WALL + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), WALL);
            line.push_back(logiccell);
            break;
        }

        case TELEPORTATION + '0':
        {
            Teleportation *firstTeleportationCell;
            if (tele)
            {
                LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), TELEPORTATION);
                firstTeleportationCell = new Teleportation();
                firstTeleportationCell->setFirstEnd(logiccell);
                tele = false;
                line.push_back(logiccell);
            }
            else
            {
                LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), TELEPORTATION);
                firstTeleportationCell->setSecondEnd(logiccell);
                this->teleportation.push_back(firstTeleportationCell);
                tele = true;
                line.push_back(logiccell);
            }
            break;
        }
        case LIGHT_BOX + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            Box *box = new Box();
            box->light = true;
            logiccell->setBox(box);
            line.push_back(logiccell);
            break;
        }
        case BOX_FINAL_POS + '0':
        {
            LogicCell *logiccell = new LogicCell(this->LogicCellVector.size(), line.size(), BOX_FINAL_POS);
            line.push_back(logiccell);
            break;
        }
        }
    }
    puts("agi");
    this->steps = 0;
}

bool BoardModel::isEndOfParty()
{
    if ((this->steps == this->stepsLimit) || (this->isFailure()))
    {
        this->winorlose = false;
        return true;
    }
    for (size_t i = 0; i < LogicCellVector.size(); i++)
    {
        for (size_t j = 0; j < LogicCellVector[0].size(); j++)
        {
            if (!LogicCellVector[i][j]->isComplete())
                return false;
        }
    }
    this->winorlose = true;
    return true;
}


bool BoardModel::isInBoard(int posY, int posX)
{
    return 0 <= posY && posY < (int)LogicCellVector.size() && 0 <= posX && posX < (int)LogicCellVector[posY].size();
}

void BoardModel::teleport()
{
    std::tuple<int, int> teleportationCase = this->teleportation[0]->getOtherEnd(this->player->y, this->player->x);
    if (std::get<0>(teleportationCase) != -1 && std::get<1>(teleportationCase) != -1)
    {
        LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
        LogicCellVector[std::get<0>(teleportationCase)][std::get<1>(teleportationCase)]->setPlayer(this->player);
        this->player->x = std::get<1>(teleportationCase);
        this->player->y = std::get<0>(teleportationCase);
    }
}

void BoardModel::move(int finalPosY, int finalPosX)
{
    if ((this->isInBoard(finalPosY, finalPosX) == false) || (LogicCellVector[finalPosY][finalPosX]->getType() == WALL))
        return;
    if (LogicCellVector[finalPosY][finalPosX]->hasBox())
    {
        int moveX = finalPosX - this->player->x, moveY = finalPosY - this->player->y;
        if (LogicCellVector[finalPosY][finalPosX]->getBox()->light)
        {
            if (!this->isInBoard(finalPosY + moveY, finalPosX + moveX))
            {
                return;
            }
            if ((LogicCellVector[finalPosY + moveY][finalPosX + moveX]->hasBox()) && (LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getBox()->light))
            {
                if ((this->isInBoard(finalPosY + 2 * moveY, finalPosX + 2 * moveX)) && (LogicCellVector[finalPosY + 2 * moveY][finalPosX + 2 * moveX]->getType() != WALL))
                    LogicCellVector[finalPosY + 2 * moveY][finalPosX + 2 * moveX]
                        ->setBox(LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getBox());
                else
                    return;
            }
            else if ((LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() != EMPTY) && (LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() != BOX_FINAL_POS))
            {
                return;
            }
        }
        else if (!this->isInBoard(finalPosY + moveY, finalPosX + moveX) || LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() == WALL)
            return;
        else if ((LogicCellVector[finalPosY + moveY][finalPosX + moveX]->hasBox()) && (LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getBox()->light))
            return;
        LogicCellVector[finalPosY + moveY][finalPosX + moveX]
            ->setBox(LogicCellVector[finalPosY][finalPosX]->getBox());
        LogicCellVector[finalPosY][finalPosX]->setBox(nullptr);
    }
    LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
    LogicCellVector[finalPosY][finalPosX]->setPlayer(this->player);
    this->player->y = finalPosY;
    this->player->x = finalPosX;
    this->steps += 1;
}

void BoardModel::moveTo(int x, int y)
{
    if ((x == this->player->x) || (y == this->player->y))
    {
        int moveX = 0;
        int moveY = 0;
        if (y > this->player->y)
            moveY = 1;
        else if (y < this->player->y)
            moveY = -1;
        else if (x > this->player->x)
            moveX = 1;
        else if (x < this->player->x)
            moveX = -1;
        while ((this->player->y != y || this->player->x != x) && !this->LogicCellVector[this->player->y + moveY][this->player->x + moveX]->hasBox() && this->LogicCellVector[this->player->y + moveY][this->player->x + moveX]->getType() != WALL)
        {
            this->steps += 1;
            this->LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
            this->LogicCellVector[this->player->y + moveY][this->player->x + moveX]->setPlayer(this->player);
            this->player->y = this->player->y + moveY;
            this->player->x = this->player->x + moveX;
        }
    }
}

void BoardModel::saveMinimumSteps()
{
    if (((this->steps < this->minimumSteps) && (this->winorlose)) || ((this->minimumSteps == 0 && this->winorlose)))
    {
        std::string strReplace = "l" + std::to_string(this->minimumSteps);
        std::string strNew = "l" + std::to_string(this->steps);
        std::ifstream filein(this->filename); // File to read from
        std::ofstream fileout("fileout.txt"); // Temporary file
        if (!filein || !fileout)
        {
            std::cout << "Error opening files!" << std::endl;
        }

        std::string strTemp;
        bool found = false;
        while (filein >> strTemp)
        {
            if ((strTemp == strReplace) && (found == false))
            {
                strTemp = strNew;
                found = true;
            }
            strTemp += "\n";
            fileout << strTemp;
        }
        filein.close();
        std::remove(this->filename.c_str());
        std::rename("fileout.txt", this->filename.c_str());
        this->minimumSteps = this->steps;
    }
}

BoardModel::BoardModel(std::string filename)
{
    this->filename = filename;
    Player *player = new Player();
    this->player = player;
}
