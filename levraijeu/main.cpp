#include "Player.hpp"
#include "Board.cpp"
#include <iostream>
int main(int argc, char const *argv[])
{
    Board board;
    std::string file = "Niveaux/niveau1.txt";
    std::string buffer = board.readFileIntoString(file);
    std::cout << buffer << std::endl;
    board.getBoard(buffer);
    return 0;
}
