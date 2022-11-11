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
            if (atoi(&fileContent[index]) == 1)
            {
                player_x = this->matrix.size();
                player_y = line.size();
            }
            line.push_back(atoi(&fileContent[index]));
        }
    }
}
void Board::printBoard()
{
    for (size_t i = 0; i < this->matrix.size(); i++)
    {
        for (size_t j = 0; j < this->matrix[0].size(); j++)
        {
            std::cout << this->matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}
bool Board::check_move(int final_pos_x, int final_pos_y)
{
    if ((final_pos_x < 0) or (final_pos_y < 0))
        return false;
    if ((final_pos_x > (int)matrix.size()) or (final_pos_y > (int)matrix[0].size()))
        return false;
    return true;
}

void Board::move(int final_pos_x, int final_pos_y)
{
    // check if valid move

    if (this->matrix[final_pos_x][final_pos_y] == 0)
    { // if there is nothing
        this->matrix[player_x][player_y] = 0;
        this->matrix[final_pos_x][final_pos_y] = 1;
        player_x = final_pos_x;
        player_y = final_pos_y;
    }
    else if (this->matrix[final_pos_x][final_pos_y] == 2)
    { // if there is a box
        int deplacement_x = final_pos_x - player_x, deplacement_y = final_pos_y - player_y;
        if (this->matrix[final_pos_x + deplacement_x][final_pos_y + deplacement_y] == 0)
        {
            this->matrix[final_pos_x + deplacement_x][final_pos_y + deplacement_y] = 2; // movement of the box
            this->matrix[final_pos_x][final_pos_y] = 1;                                 // Movement of the player
            this->matrix[player_x][player_y] = 0;
            player_x = final_pos_x;
            player_y = final_pos_y;
        }
    }
    printBoard();
    std::cout << player_x << player_y;

    // set le board;
}
