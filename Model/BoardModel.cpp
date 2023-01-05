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
    for (int i = 0; i < (int)LogicCellVector.size(); i++)
    {
        for (int j = 0; j < (int)LogicCellVector[0].size(); j++)
        {
            if (LogicCellVector[i][j]->hasBox() && (LogicCellVector[i][j]->isBlocked() == false))
            {
                for (auto a : move)
                {
                    if (this->isInBoard(i + a[0], j + a[1]) == false && this->isInBoard(i + a[2], j + a[3]) == false)
                        LogicCellVector[i][j]->setBoxBlocked(true);
                    else if (this->isInBoard(i + a[0], j + a[1]) && this->isInBoard(i + a[2], j + a[3]))
                    {
                        if (LogicCellVector[i + a[0]][j + a[1]]->isBlocked() && LogicCellVector[i + a[2]][j + a[3]]->isBlocked())
                            LogicCellVector[i][j]->setBoxBlocked(true);
                    }
                    else if (this->isInBoard(i + a[0], j + a[1]) && LogicCellVector[i + a[0]][j + a[1]]->isBlocked())
                        LogicCellVector[i][j]->setBoxBlocked(true);
                    else if (this->isInBoard(i + a[2], j + a[3]) && LogicCellVector[i + a[2]][j + a[3]]->isBlocked())
                        LogicCellVector[i][j]->setBoxBlocked(true);
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
    std::string bestScore = "";
    while (fileContent[index] != '\n')
    {
        index++;
        bestScore += fileContent[index];
    }
    this->bestScore = atoi(bestScore.c_str());
    std::string stepsLimit = "";
    index++;
    while (fileContent[index] != '\n')
    {
        index++;
        stepsLimit += fileContent[index];
    }
    this->stepsLimit = atoi(stepsLimit.c_str());
    index++;
    this->createLogicCell(index, fileContent);
}

void BoardModel::createLogicCell(int index, std::string fileContent)
{
    this->LogicCellVector.clear();
    this->teleportation.clear();
    std::vector<LogicCell *> line;
    bool teleportationEnd = true;
    for (int ind = index; ind < (int)fileContent.size(); ind++)
    {
        LogicCell *logicCell;
        switch (fileContent[ind])
        {
        case EMPTY + '0':
        case WALL + '0':
            logicCell = new LogicCell(this->LogicCellVector.size(), line.size(), fileContent[ind] - '0');
            break;
        case PLAYER + '0':
        {
            logicCell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            this->player->y = this->LogicCellVector.size();
            this->player->x = line.size();
            logicCell->setPlayer(player);
            break;
        }
        case BOX + '0':
        case RED_BOX:
        case BLUE_BOX:
        case LIGHT_BOX + '0':
        {
            logicCell = new LogicCell(this->LogicCellVector.size(), line.size(), EMPTY);
            Box *box = new Box(fileContent[ind]);
            logicCell->setBox(box);
            break;
        }
        case RED_BOX_FINAL_POS:
        case BLUE_BOX_FINAL_POS:
        case BOX_FINAL_POS + '0':
            logicCell = new LogicCell(this->LogicCellVector.size(), line.size(), BOX_FINAL_POS, fileContent[ind]);
            break;
        case TELEPORTATION + '0':
        {
            Teleportation *firstTeleportationCell;
            logicCell = new LogicCell(this->LogicCellVector.size(), line.size(), TELEPORTATION);
            if (teleportationEnd)
            {
                firstTeleportationCell = new Teleportation();
                firstTeleportationCell->setFirstEnd(logicCell);
                teleportationEnd = false;
            }
            else
            {
                firstTeleportationCell->setSecondEnd(logicCell);
                this->teleportation.push_back(firstTeleportationCell);
                teleportationEnd = true;
            }
            break;
        }
        case ' ':
        case (char)10:
            break;
        default:
        {
            std::cout << "Number not recognized by the program" << (int)fileContent[ind] << std::endl;
            exit(1);
            break;
        }
        }
        if (fileContent[ind] == '\n' || fileContent[ind] == '\0')
        {
            this->LogicCellVector.push_back(line);
            line.clear();
            if ((LogicCellVector.size() > 15) || (line.size() > 15))
            {
                puts("Matrix is too big");
                exit(1);
            }
        }
        else
            line.push_back(logicCell);
    }
    this->steps = 0;
    checkBoard(teleportationEnd);
}

bool BoardModel::isEndOfParty()
{
    if ((this->steps == this->stepsLimit) || (this->isFailure()))
    {
        this->partyWin = false;
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
    this->partyWin = true;
    return true;
}

bool BoardModel::isInBoard(int posY, int posX)
{
    return 0 <= posY && posY < (int)LogicCellVector.size() && 0 <= posX && posX < (int)LogicCellVector[posY].size();
}

void BoardModel::teleport()
{
    for (auto i : this->teleportation)
    {
        std::tuple<int, int> teleportationCase = i->getOtherEnd(this->player->y, this->player->x);
        if (std::get<0>(teleportationCase) != -1 && std::get<1>(teleportationCase) != -1)
        {
            LogicCellVector[this->player->y][this->player->x]->setPlayer(nullptr);
            LogicCellVector[std::get<0>(teleportationCase)][std::get<1>(teleportationCase)]->setPlayer(this->player);
            this->player->x = std::get<1>(teleportationCase);
            this->player->y = std::get<0>(teleportationCase);
        }
    }
}

void BoardModel::move(int finalPosY, int finalPosX)
{
    if ((this->isInBoard(finalPosY, finalPosX) == false) || (LogicCellVector[finalPosY][finalPosX]->getType() == WALL))
        return;
    if (LogicCellVector[finalPosY][finalPosX]->hasBox())
    {
        int moveX = finalPosX - this->player->x, moveY = finalPosY - this->player->y;
        if (!this->isInBoard(finalPosY + moveY, finalPosX + moveX) || LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() == WALL)
            return;
        if (LogicCellVector[finalPosY][finalPosX]->getBox()->light)
        {
            if ((!this->isInBoard(finalPosY + moveY, finalPosX + moveX)) && (LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() != EMPTY) && (LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getType() != BOX_FINAL_POS))
                return;
            else if ((LogicCellVector[finalPosY + moveY][finalPosX + moveX]->hasBox()))
            {
                if (!(LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getBox()->light && this->isInBoard(finalPosY + 2 * moveY, finalPosX + 2 * moveX) && LogicCellVector[finalPosY + 2 * moveY][finalPosX + 2 * moveX]->getType() != WALL))
                    return;
                LogicCellVector[finalPosY + 2 * moveY][finalPosX + 2 * moveX]
                    ->setBox(LogicCellVector[finalPosY + moveY][finalPosX + moveX]->getBox());
            }
        }
        else
        {
            if ((LogicCellVector[finalPosY + moveY][finalPosX + moveX]->hasBox()))
                return;
        }
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

void BoardModel::saveBestScore()
{
    if (((this->steps < this->bestScore) && (this->partyWin)) || ((this->bestScore == 0 && this->partyWin)))
    {
        std::string strReplace = "l" + std::to_string(this->bestScore); // Source : StackOverflow
        std::string strNew = "l" + std::to_string(this->steps);
        std::ifstream filein(this->filename); // File to read from
        std::ofstream fileout("fileout.txt"); // Temporary file
        if (!filein || !fileout)
            std::cout << "Error opening files!" << std::endl;

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
        this->bestScore = this->steps;
    }
}
void BoardModel::checkBoard(bool teleportationEnd)
{
    if (!teleportationEnd)
    {
        puts("One of the teleportation has no second end");
        exit(1);
    }
    size_t previousSize = LogicCellVector[0].size();
    size_t currentSize;
    for (size_t i = 1; i < LogicCellVector.size(); i++)
    {
        currentSize = LogicCellVector[i].size();
        if (currentSize != previousSize)
        {
            puts("The lines of the board don't have the same size");
            exit(1);
        }
        previousSize = currentSize;
    }
    if (this->player->x == -1)
    {
        puts("Player doesn't exists");
        exit(1);
    }
}
