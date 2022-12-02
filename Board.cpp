#include "Board.hpp"
#include "Box.cpp"
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

void BoardModel::maxpasandlimit()
{
    int N;
    if (this->filename == level1)
    {
        N = 1;
    }
    std::ifstream in("Niveaux/limiteetmaxpas.txt");

    std::string line;

    // skip N lines
    for (int i = 0; i < N; ++i)
        std::getline(in, line);

    std::getline(in, line);
    std::cout << line << std::endl;Box *box = new Box(this->matrix.size(), line.size());

                this->correctBoxesPositions.push_back(*box);
    this->minpas = atoi(line.c_str());
    std::getline(in, line);
    std::cout << line << std::endl;
    this->limitpas = atoi(line.c_str());
}

bool BoardModel::isFailure()
{
    for (auto &box : boxesPositions)
    {
        std::cout << box.getX() << " " << box.getY() << std::endl;
        Box *checkbox1 = new Box(0, 0);
        Box *checkbox2 = new Box(0, matrix.size() - 1);
        Box *checkbox3 = new Box(matrix[0].size() - 1, 0);
        Box *checkbox4 = new Box(matrix[0].size() - 1, matrix.size() - 1);
        if (&box == checkbox1)
            ;
        else if (&box == checkbox2)
            ;
        else if (&box == checkbox3)
            ;
        else if (&box == checkbox4)
            ;
        // TODO: check if outside the board
        else if ((matrix[box.getX()][box.getY()-1] == WALL) &&(matrix[box.getX()-1][box.getY()] == WALL));
            //LA BOITE EST BLOQUEE -> METTRE ATTRIBUT DE LA BOITE A BLOQU
        else if ((matrix[box.getX()-1][box.getY()] == WALL) && (matrix[box.getX()][box.getY()+1] == WALL));
        else if ((matrix[box.getX()][box.getY()+1] == WALL) && (matrix[box.getX()+1][box.getY()] == WALL));
        else if ((matrix[box.getX()+1][box.getY()] == WALL) && (matrix[box.getX()][box.getY()-1] == WALL));
        

        //TODO: si entouré de boites bloquées
        //TODO : faire une fonction getbox(int x, int y)
        /*
        else if ((matrix[box.getX()][get<1>(box)-1] == BOX) && (matrix[box.getX()-1][box.getY()] == BOX)){
            if ((matrix[box.getX()][box.getY()-1].blocked == true)  && (matrix[box.getX()-1][box.getY()].blocked == true))}
        else if ((matrix[box.getX()-1][box.getY()] == BOX) && (matrix[box.getX()][box.getY()+1] == BOX)){
            if ((matrix[box.getX()][box.getY()-1].blocked == true)  && (matrix[box.getX()-1][box.getY()].blocked == true))}
        else if ((matrix[box.getX()][box.getY()+1] == BOX) && (matrix[box.getX()+1][box.getY()] == BOX)){
            if ((matrix[box.getX()][box.getY()-1].blocked == true)  && (matrix[box.getX()-1][box.getY()].blocked == true))}
        else if ((matrix[box.getX()+1][box.getY()] == BOX) && (matrix[box.getX()][box.getY()-1] == BOX)){
            if ((matrix[box.getX()][box.getY()-1].blocked == true)  && (matrix[box.getX()-1][box.getY()].blocked == true))}*/
        
        
        else
            return false;
    }
    return true;

    // bloqué à cause des murs
    // bloqué à cause des walls
    // bloqué à cause des autres boites bloquées
}

void BoardModel::createBoard(std::string fileContent)
{

    std::vector<int> line;
    this->matrix.clear();
    this->correctBoxesPositions.clear();
    this->boxesPositions.clear();
    for (size_t index = 0; index < fileContent.size(); index++)
    {
        if ((fileContent[index] == '\n'))
        {
            this->matrix.push_back(line);
            line.clear();
        }
        else if (fileContent[index] != ' ')
        {
            if (atoi(&fileContent[index]) == PLAYER)
            {

                this->player->setY(this->matrix.size());
                this->player->setX(line.size());
            }

            else if (atoi(&fileContent[index]) == BOX)
            {
                Box * box = new Box(this->matrix.size(), line.size());
                this->boxesPositions.push_back(*box);
            }

            else if (atoi(&fileContent[index]) == TELEPORTATION)
            {
                if (this->getFirstTeleportation() == false)
                {
                    Teleportation *firstTeleportationCell = new Teleportation(this->matrix.size(), line.size(), NULL);
                    this->teleportation.push_back(firstTeleportationCell);
                    this->setFirstTeleportation(true);
                }
                else 
                {
                    Teleportation *secondTeleportationCell = new Teleportation(this->matrix.size(), line.size(), teleportation[0]);
                    this->teleportation.push_back(secondTeleportationCell);
                }
            }
            /*
            else if (atoi(&fileContent[index]) == LIGHT_BOX)
            {
                this->boxesPositions.push_back(std::tuple(this->matrix.size(), line.size()));
            }*/

            else if (atoi(&fileContent[index]) == BOX_FINAL_POS)
            {
                Box *box = new Box(this->matrix.size(), line.size());

                this->correctBoxesPositions.push_back(*box);
            }
            line.push_back(atoi(&fileContent[index]));
        }
    }
    std::sort(this->correctBoxesPositions.begin(), this->correctBoxesPositions.end());
}

bool BoardModel::end_of_party()
{
    
    std::sort(this->boxesPositions.begin(), this->boxesPositions.end());
    if (this->correctBoxesPositions == this->boxesPositions)
        return true;
    return false;
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

bool BoardModel::move(int final_player_pos_y, int final_player_pos_x)
{

    if (this->isInBoard(final_player_pos_y, final_player_pos_x) == false)
        return false;
    int deplacement_x = final_player_pos_x - this->player->getX(), deplacement_y = final_player_pos_y - this->player->getY();

    if ((this->matrix[final_player_pos_y][final_player_pos_x] == EMPTY) || (this->matrix[final_player_pos_y][final_player_pos_x] == BOX_FINAL_POS))
    { // if there is nothing
        Box *box = new Box(this->player->getY(), this->player->getX());
        if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), *box) != correctBoxesPositions.end())
            this->matrix[this->player->getY()][this->player->getX()] = BOX_FINAL_POS;
        else
            this->matrix[this->player->getY()][this->player->getX()] = EMPTY;
        this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
        this->player->setY(final_player_pos_y);
        this->player->setX(final_player_pos_x);
    }
    else if (this->matrix[final_player_pos_y][final_player_pos_x] == BOX)
    { // if there is a box
    
        if ((this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == EMPTY) || (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == BOX_FINAL_POS))
        {
            this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = BOX; // movement of the box
            this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
            Box *box = new Box(this->player->getY(), this->player->getX());
            if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), *box) != correctBoxesPositions.end())
                this->matrix[this->player->getY()][this->player->getX()] = BOX_FINAL_POS;
            else
                this->matrix[this->player->getY()][this->player->getX()] = EMPTY;
            this->player->setY(final_player_pos_y);
            this->player->setX(final_player_pos_x);
            this->updateBoxPositions();
        }
    }
    else if (this->matrix[final_player_pos_y][final_player_pos_x] == LIGHT_BOX)
    {
        if (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == LIGHT_BOX)
        {
            if (!this->isInBoard(final_player_pos_y + 2 * deplacement_y, final_player_pos_x + 2 * deplacement_x))
                return false;
            if ((this->matrix[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x] == EMPTY) || (this->matrix[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x] == BOX_FINAL_POS))
            {
                this->matrix[final_player_pos_y + 2 * deplacement_y][final_player_pos_x + 2 * deplacement_x] = LIGHT_BOX;
                this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = LIGHT_BOX;
                this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
                Box *box = new Box(this->player->getY(), this->player->getX());
                if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), *box) != correctBoxesPositions.end())
                    this->matrix[this->player->getY()][this->player->getX()] = BOX_FINAL_POS;
                else
                    this->matrix[this->player->getY()][this->player->getX()] = EMPTY;
                this->player->setY(final_player_pos_y);
                this->player->setX(final_player_pos_x);
                this->updateBoxPositions();
            }
            else
            {
                return false;
            }
        }
        if ((this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == EMPTY) || (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == BOX_FINAL_POS))
        {
            this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = LIGHT_BOX; // movement of the box

            this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
            // Movement of the player
            Box *box = new Box(this->player->getY(), this->player->getX());
            if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), *box) != correctBoxesPositions.end())
                this->matrix[this->player->getY()][this->player->getX()] = BOX_FINAL_POS;
            else
                this->matrix[this->player->getY()][this->player->getX()] = EMPTY;
            this->player->setY(final_player_pos_y);
            this->player->setX(final_player_pos_x);
            this->updateBoxPositions();
        }
        return true;
    }
}

void BoardModel::updateBoxPositions()
{
    this->boxesPositions.clear();
    for (size_t index_y = 0; index_y < this->matrix.size(); index_y++)
    {
        for (size_t index_x = 0; index_x < this->matrix[index_y].size(); index_x++)
        {
            if (this->matrix[index_y][index_x] == BOX){
                Box *box = new Box(index_y, index_x);
                this->boxesPositions.push_back(*box);}
        }
    }
}