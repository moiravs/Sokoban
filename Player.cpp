

#include "Player.hpp"

void Player::setX(int x)
{
    this->x = x;
}
void Player::setY(int y)
{
    this->y = y;
}
int Player::getX()
{
    return (this->x);
}
int Player::getY()
{
    return (this->y);
}

void Player::incrementSteps()
{
    stepsCount++;
}
