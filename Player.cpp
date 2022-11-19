#include "Player.hpp"
Player::Player(/* args */)
{
}

Player::~Player()
{
}

void Player::move(std::vector<std::vector<int>> matrix, int pos_y, int pos_x, int final_pos_y, int final_pos_x)
{
    // copie le board
    // change le board -> 
    if (matrix[final_pos_y][final_pos_x] == 0){ // if there is nothing
        matrix[pos_y][pos_x] = 0;
        matrix[final_pos_y][final_pos_x] = 1;
    }
    else if (matrix[final_pos_y][final_pos_x] == 2){ // if there is a box
        int deplacement_y = final_pos_y-pos_y, deplacement_x = final_pos_x-pos_x;
        if (matrix[final_pos_y + deplacement_y][final_pos_x+ deplacement_x] == 0){
            matrix[final_pos_y + deplacement_y][final_pos_x + deplacement_x] = 3; // movement of the box
            matrix[final_pos_y][final_pos_x] = 1; // Movement of the player
            matrix[pos_y][pos_x]= 0;
        }
    }
    // set le board;
}