#include "Player.hpp"
Player::Player(/* args */)
{
}

Player::~Player()
{
}

void Player::move(std::vector<std::vector<int>> matrix, int pos_x, int pos_y, int final_pos_x, int final_pos_y)
{
    // copie le board
    // change le board -> 
    if (matrix[final_pos_x][final_pos_y] == 0){ // if there is nothing
        matrix[pos_x][pos_y] = 0;
        matrix[final_pos_x][final_pos_y] = 1;
    }
    else if (matrix[final_pos_x][final_pos_y] == 2){ // if there is a box
        int deplacement_x = final_pos_x-pos_x, deplacement_y = final_pos_y-pos_y;
        if (matrix[final_pos_x + deplacement_x][final_pos_y+ deplacement_y] == 0){
            matrix[final_pos_x + deplacement_x][final_pos_y + deplacement_y] = 3; // movement of the box
            matrix[final_pos_x][final_pos_y] = 1; // Movement of the player
            matrix[pos_x][pos_y]= 0 ;
        }
    }
    // set le board;
}