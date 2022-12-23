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
     * @brief  Getter for the filename
     * @retval Return the filename
     */
    std::string getFilename();
    /**
     * @brief  Setter for the filename
     * @param  newFilename: the filename
     * @retval None
     */
    void setFilename(std::string newFilename);
    /**
     * @brief  Getter for winorlose
     * @retval return true if the player won, false if the player lose
     */
    bool getWinOrLose();
    /**
     * @brief  Setter for winorlose
     * @param  newValue: WinOrLose value
     * @retval None
     */
    void setWinOrLose(bool newValue);
    /**
     * @brief  Getter for steps
     * @retval Steps
     */
    
    int getSteps();
    /**
     * @brief  Setter for steps
     * @param  newSteps: Steps
     * @retval None
     */

    void setSteps(int newSteps);
    /**
     * @brief  Getter for StepsLimit
     * @retval StepsLimit
     */
    
    int getStepsLimit();
    /**
     * @brief  Getter for MinimumSteps
     * @retval MinSteps
     */
    int getMinimumSteps();
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
    void saveMinimumSteps();
    /**
     * @brief  Getter for LogicCellVector
     * @retval the LogicCellVector
     */
    std::vector<std::vector<LogicCell *>> getLogicCellVector();

};

#endif