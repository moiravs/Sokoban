#include "Board.hpp"
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

void BoardModel::maxpasandlimit()
{
    int N;
    if (this->filename == level1)
    {
        N = 1;
    }
    std::ifstream in("Niveaux/limiteetmaxpas.txt");

    std::string s;

    // skip N lines
    for (int i = 0; i < N; ++i)
        std::getline(in, s);

    std::getline(in, s);
    std::cout << s << std::endl;
    this->minpas = atoi(s.c_str());
    std::getline(in, s);
    std::cout << s << std::endl;
    this->limitpas = atoi(s.c_str());
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
                this->player_y = this->matrix.size();
                this->player_x = line.size();
            }

            else if (atoi(&fileContent[index]) == BOX)
            {
                this->boxesPositions.push_back(std::tuple(this->matrix.size(), line.size()));
            }

            else if (atoi(&fileContent[index]) == TELEPORTATION)
            {
            }
            else if (atoi(&fileContent[index]) == LIGHT_BOX)
            {
                this->boxesPositions.push_back(std::tuple(this->matrix.size(), line.size()));
            }

            else if (atoi(&fileContent[index]) == BOX_FINAL_POS)
            {
                this->correctBoxesPositions.push_back(std::tuple(this->matrix.size(), line.size()));
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
    {
        return true;
    }
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
    int deplacement_x = final_player_pos_x - this->player_x, deplacement_y = final_player_pos_y - this->player_y;

    if ((this->matrix[final_player_pos_y][final_player_pos_x] == EMPTY) || (this->matrix[final_player_pos_y][final_player_pos_x] == BOX_FINAL_POS))
    { // if there is nothing
        if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), std::tuple(player_y, player_x)) != correctBoxesPositions.end())
            this->matrix[player_y][player_x] = BOX_FINAL_POS;
        else
            this->matrix[player_y][player_x] = EMPTY;
        this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
        this->player_y = final_player_pos_y;
        this->player_x = final_player_pos_x;
    }
    else if (this->matrix[final_player_pos_y][final_player_pos_x] == BOX)
    { // if there is a box
        if ((this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == EMPTY) || (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == BOX_FINAL_POS))
        {
            this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = BOX; // movement of the box
            this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
            if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), std::tuple(player_y, player_x)) != correctBoxesPositions.end())
                this->matrix[player_y][player_x] = BOX_FINAL_POS;
            else
                this->matrix[player_y][player_x] = EMPTY;
            this->player_y = final_player_pos_y;
            this->player_x = final_player_pos_x;
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
                if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), std::tuple(player_y, player_x)) != correctBoxesPositions.end())
                    this->matrix[player_y][player_x] = BOX_FINAL_POS;
                else
                    this->matrix[player_y][player_x] = EMPTY;
                this->player_y = final_player_pos_y;
                this->player_x = final_player_pos_x;
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
            if (std::find(correctBoxesPositions.begin(), correctBoxesPositions.end(), std::tuple(player_y, player_x)) != correctBoxesPositions.end())
            {
                this->matrix[player_y][player_x] = BOX_FINAL_POS;
            }
            else
            {
                this->matrix[player_y][player_x] = EMPTY;
            }
            this->player_y = final_player_pos_y;
            this->player_x = final_player_pos_x;
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
            if (this->matrix[index_y][index_x] == BOX)
            {
                this->boxesPositions.push_back(std::tuple(index_y, index_x));
            }
        }
    }
}