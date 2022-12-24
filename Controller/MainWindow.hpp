/*
 * Projet : Sokoban project
 * Autors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"
#include "../View/PopUp.hpp"
#include "../View/HelpWindow.hpp"
#include "../View/StartWindow.hpp"

class MainWindow : public Fl_Window
{
    std::shared_ptr<BoardModel> boardModel;
    DisplayBoard *display;
    const char *steps;
    Fl_Text_Buffer *buff;
    PopUp *popUp;
    HelpWindow *helpWindow;

public:
    MainWindow(std::shared_ptr<BoardModel> boardModel, PopUp *popUp, HelpWindow *helpWindow);
    /**
     * @brief  Override the drawing function from Fl_Window, draw the number of steps, the steps limit, the 
     * minimum steps for this level and draw a text if the player win or lose.
     * @retval None
     */
    void draw() override;
    /**
     * @brief  Handle the events, override from FL_Window
     * @param  event: The event
     * @retval return 1 on success
     */
    int handle(int event) override;
    /**
     * @brief  Callback for the window, when the window closes it saves the Minimum steps and hides the window
     * @param  *widget: the window widget
     * @retval None
     */
    static void windowCallback(Fl_Widget *widget, void *);
    /**
     * @brief
     * @param  *widget:
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void resetLevelCallback(Fl_Widget *widget, void *mainWindow);
    /**
     * @brief Callback for the resetLevel button, resets the level
     * @param  *widget: the resetLevel button
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void changeLevelCallback(Fl_Widget *widget, void *mainWindow);
    /**
     * @brief Callback for the changeLevel button, opens a new window with all levels
     * @param  *widget: The changeLevel button
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void resetMinStepsCallback(Fl_Widget *widget, void *mainWindow);
    /**
     * @brief  Callback for the help button, opens a new window and shows help
     * @param  *widget: The help button
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void helpCallback(Fl_Widget *widget, void *mainWindow);
};

