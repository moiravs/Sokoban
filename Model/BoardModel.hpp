/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef BOARD_HPP
#define BOARD_HPP
#include "BoxModel.hpp"
#include "Player.hpp"
#include "../Constants.hpp"
#include "Player.hpp"
#include "Teleportation.hpp"
#include "LogicCell.hpp"

class BoardModel
{
private:
    bool firstTeleportation = false;
    std::vector<Teleportation *> teleportation;

public:
    // TODO : destructeur
    // TODO :TOUT EN PRIVATE

    std::vector<std::vector<LogicCell *>> LogicCellVector;
    std::string filename;
    int steps = 0;
    int minimumSteps = 0;
    int stepsLimit = 0;
    bool endOfParty = false;
    bool winorlose;
    Player *player;
    BoardModel(std::string filename)
    {
        this->filename = filename;
        Player *player = new Player();
        this->player = player;
    }
    void maxpasandlimit();
    bool isEndOfParty();
    bool isFailure();
    void teleport();
    bool checkIfBlocked(int i, int j);
    void move(int finalPosY, int finalPosX);
    std::string readFileIntoString();
    void createBoard(std::string fileContent);
    void setFirstTeleportation(bool value);
    bool getFirstTeleportation();
    bool isInBoard(int posY, int posX);
    void moveTo(int x, int y);
    std::vector<std::vector<LogicCell *>> getLogicCellVector();
};

#endif