#include "Board.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit()
#include <fstream>

std::string Board::readFileIntoString(std::string fileName)
{
    std::ifstream ifs(fileName);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

std::vector<std::vector<int>> Board::getBoard()
{
    return (this->matrix);
}

void Board::createBoard(std::string fileContent)
{
    std::vector<int> line;
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

bool Board::end_of_party(){
   // (this->boxesPositions == this->correctBoxesPositions);
    return false;
}

bool Board::check_move(int final_pos_x, int final_pos_y)
{
    if ((final_pos_x < 0) || (final_pos_y < 0))
        return false;
    if ((final_pos_x > (int)matrix.size()) || (final_pos_y > (int)matrix[0].size()))
        return false;
    return true;
}

void Board::move(int final_pos_x, int final_pos_y)
{
    // TODO check if valid move
    // TODO check if end of game
    if (this->matrix[final_pos_x][final_pos_y] == 0)
    { // if there is nothing
        this->matrix[this->player_x][this->player_y] = 0;
        this->matrix[final_pos_x][final_pos_y] = 1;
        this->player_x = final_pos_x;
        this->player_y = final_pos_y;
    }
    else if (this->matrix[final_pos_x][final_pos_y] == 2)
    { // if there is a box
        int deplacement_x = final_pos_x - this->player_x, deplacement_y = final_pos_y - this->player_y;
        if (this->matrix[final_pos_x + deplacement_x][final_pos_y + deplacement_y] == 0)
        {
            this->matrix[final_pos_x + deplacement_x][final_pos_y + deplacement_y] = 2; // movement of the box
            this->matrix[final_pos_x][final_pos_y] = 1;                                 // Movement of the player
            this->matrix[this->player_x][this->player_y] = 0;
            this->player_x = final_pos_x;
            this->player_y = final_pos_y;
        }
    }
}

void Board::updateBoxPositions()
{
    this->boxesPositions.clear();
    for (size_t index_x=0; index_x < this->matrix.size(); index_x++){
        for (size_t index_y=0; index_y < this->matrix[index_y].size(); index_y++){
            if (this->matrix[index_x][index_y] == BOX){
                tuple boxPos = {index_x, index_y};
                boxesPositions.push_back(boxPos);
            }
        }
    }
}

std::vector<std::vector<int>> Board::getMatrix()
{
    return this->matrix;
}