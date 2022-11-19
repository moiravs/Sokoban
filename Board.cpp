#include "Board.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit()
#include <fstream>

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

void BoardModel::createBoard(std::string fileContent)
{
    std::vector<int> line;
    this->matrix.clear();
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
                this->player_x = this->matrix.size();
                this->player_y = line.size();
            }

            else if (atoi(&fileContent[index]) == BOX)
            {
                tuple boxPosition = {this->matrix.size(), line.size()};
                this->boxesPositions.push_back(boxPosition);
            }
            /*
            else if (atoi(&fileContent[index]) == TELEPORTATION){
                tuple teleporterPosition = {this->matrix.size(), line.size()};
            }*/

            else if (atoi(&fileContent[index]) == BOX_FINAL_POS)
            {
                tuple correctBoxPos = {this->matrix.size(), line.size()};
                this->correctBoxesPositions.push_back(correctBoxPos);
            }
            line.push_back(atoi(&fileContent[index]));
        }
    }
}

bool BoardModel::end_of_party()
{
    for (auto &correct_pos : this->correctBoxesPositions)
    {
        for (auto &pos : this->boxesPositions)
        {
            if (!(correct_pos.x_axis == pos.x_axis && correct_pos.y_axis == pos.x_axis))
            {
                return false;
            }
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
    return (0 <= pos_y < (int)matrix.size()) && (0 <= pos_x < (int)matrix[0].size());
}

void BoardModel::move(int final_player_pos_y, int final_player_pos_x)
{
    if (this->isInBoard(final_player_pos_y, final_player_pos_x) == true){
        if (this->matrix[final_player_pos_y][final_player_pos_x] == EMPTY)
        { // if there is nothing
            if (this->on_correct_box_pos == true){
                this->matrix[this->player_y][this->player_x] = BOX_FINAL_POS;
                this->on_correct_box_pos = false;
            }
            else {
                this->matrix[this->player_y][this->player_x] = EMPTY;
            }
            this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
            this->player_y = final_player_pos_y;
            this->player_x = final_player_pos_x;
        }
        else if (this->matrix[final_player_pos_y][final_player_pos_x] == BOX)
        { // if there is a box
            int deplacement_x = final_player_pos_x - this->player_x, deplacement_y = final_player_pos_y - this->player_y;
            if (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == EMPTY)
            {
                this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = BOX; // movement of the box
                this->updateBoxPositions();
                if (on_correct_box_pos){
                    this->matrix[final_player_pos_y][final_player_pos_x] = BOX_FINAL_POS;
                    on_correct_box_pos = false;
                }
                else {
                    this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER; 
                }                                // Movement of the player
                this->matrix[this->player_y][this->player_x] = EMPTY;
                this->player_y = final_player_pos_y;
                this->player_x = final_player_pos_x;
            }

        else if (this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] == BOX_FINAL_POS){
            this->matrix[final_player_pos_y + deplacement_y][final_player_pos_x + deplacement_x] = BOX;
            this->updateBoxPositions();
            this->matrix[final_player_pos_y][final_player_pos_x] = PLAYER;
            this->matrix[this->player_y][this->player_x] = EMPTY;
            this->player_x = final_player_pos_x; this->player_y = final_player_pos_y;
            this->on_correct_box_pos = true;
        }
    }
    else if (this->matrix[final_player_pos_y][final_player_pos_x] == BOX_FINAL_POS){
        
    }
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
                tuple boxPos = {index_y, index_x};
                boxesPositions.push_back(boxPos);
            }
        }
    }
}