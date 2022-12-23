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
    std::string filename;
    int steps = 0;
    int minimumSteps = 0;
    int stepsLimit = 0;
    std::vector<std::vector<LogicCell *>> LogicCellVector;
    bool winorlose;
    

public:
    // TODO : destructeur    
    Player *player;
    BoardModel(std::string filename)
    {
        this->filename = filename;
        Player *player = new Player();
        this->player = player;
    }
    void createLogicCell(int index, std::string fileContent);
    bool isEndOfParty();
    bool isFailure();
    void teleport();
    std::string getFilename();
    void setFilename(std::string newFilename);
    bool getWinOrLose();
    void setWinOrLose(bool newValue);
    int getSteps();
    void setSteps(int newSteps);
    int getStepsLimit();
    int getMinimumSteps();
    bool checkIfBlocked(int i, int j);
    void move(int finalPosY, int finalPosX);
    std::string readFileIntoString();
    void createBoard(std::string fileContent);
    void setFirstTeleportation(bool value);
    bool getFirstTeleportation();
    bool isInBoard(int posY, int posX);
    void moveTo(int x, int y);
    void saveMinimumSteps();
    std::vector<std::vector<LogicCell *>> getLogicCellVector();
};

#endif