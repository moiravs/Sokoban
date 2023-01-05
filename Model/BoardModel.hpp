/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#ifndef BOARD_HPP
#define BOARD_HPP
#include "../Constants.hpp"
#include "Teleportation.hpp"
#include "LogicCell.hpp"

class BoardModel
{
private:
    std::vector<Teleportation *> teleportation;
    std::string filename;
    int steps = 0;
    int bestScore = 0;
    int stepsLimit = 0;
    std::vector<std::vector<LogicCell *>> LogicCellVector;
    bool partyWin;
    Player *player = new Player();

public:
    // Constructor
    BoardModel(const std::string filename) : filename{filename}{};

    // Getters and setters
    std::vector<std::vector<LogicCell *>> getLogicCellVector() { return this->LogicCellVector; }
    std::string getFilename() { return this->filename; }
    void setFilename(const std::string newFilename) { this->filename = newFilename; }
    int getSteps() { return this->steps; }
    void setSteps(int newSteps) { this->steps = newSteps; }
    int getStepsLimit() { return this->stepsLimit; }
    int getMinimumSteps() { return this->bestScore; }
    bool getWinOrLose() { return this->partyWin; }
    void setWinOrLose(bool newValue) { this->partyWin = newValue; }
    Player *getPlayer() { return this->player; }

    // Methods
    /**
     * @brief  Creates the LogicCellVector
     * @param  index: the index in the file where the LogicCell is starting
     * @param  fileContent: the content of the file
     */
    void createLogicCell(int index, std::string fileContent);
    /**
     * @brief  Check if level is finished
     * @retval return true if the level is finished
     */

    bool isEndOfParty();
    /**
     * @brief  Check if there are no more possible moves ( if all the boxes are blocked)
     * @retval return true if all the boxes are blocked
     */

    bool isFailure();
    /**
     * @brief  Teleport from one side to another
     * @retval None
     */

    void teleport();
    /**
     * @brief  Move the player to finalPosY and finalPosX
     * @param  finalPosY: Final position of the player in Y
     * @param  finalPosX: Final position of the player in X
     * @retval None
     */
    void move(int finalPosY, int finalPosX);
    /**
     * @brief  Transform a file into a string
     * @retval A string with all the content of a file
     */
    std::string readFileIntoString();
    /**
     * @brief  Takes the minSteps and LimitOfSteps from the file
     * @param  fileContent: The content of the file
     * @retval None
     */
    void createBoard(std::string fileContent);
    /**
     * @brief  Check if cell is not outside the board
     * @param  posY: Position in Y
     * @param  posX: Position in X
     * @retval True if cell is in board
     */
    bool isInBoard(int posY, int posX);
    /**
     * @brief  moves the player till position x or position y, if there is no box in his way
     * @param  x: position x
     * @param  y: position y
     * @retval None
     */
    void moveTo(int x, int y);
    /**
     * @brief  Save the minimum steps in the file of the level
     * @retval None
     */
    void saveBestScore();
    /**
     * @brief Check if the board has one player, if the board is a rectangle and if all teleportation have a second end.
     * @param  teleportationEnd : true if the teleportation is finished
     * @retval None
     */
    void checkBoard(bool teleportationEnd);
};

#endif