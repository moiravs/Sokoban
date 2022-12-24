/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"

class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(300, 300, 400, 50, "Andrius Ezerskis & Moïra Vanderslagmolen");
    int wait = 0;

public:
    StartWindow();
    /**
     * @brief  Override the drawing function from Fl_Window, draw the names of the authors of the game
     * @retval None
     */
    void draw() override;
    /**
     * @brief  Refresh the window
     * @param  *userdata: Instance of StartWindow
     */
    static void Time_CB(void *userdata);
};