/*
 * Projet : Sokoban project
 * Authors : Andrius Ezerskis & Moïra Vanderslagmolen
 * Matricule : 000542698 & 000547486
 * Date : 21 december 2022
 * */
#include "../View/DisplayBoard.hpp"
#include "../View/CellDisplay.hpp"
#include "../View/HelpWindow.hpp"
#include "../View/StartWindow.hpp"

class MainWindow : public Fl_Window
{
    std::shared_ptr<BoardModel> boardModel;
    DisplayBoard *display;
    const char *steps;
    Fl_Text_Buffer *buff;
    HelpWindow *helpWindow;
    Fl_Button *reset = new Fl_Button(RESET_X, RESET_Y, RESET_W, RESET_H, "Reset Level");
    Fl_Button *resetMinSteps = new Fl_Button(RESET_BEST_SCORE_X, RESET_BEST_SCORE_Y, RESET_BEST_SCORE_W, RESET_BEST_SCORE_H, "Reset Min Steps");
    Fl_Button *levels = new Fl_Button(CHOICE_X, CHOICE_Y, CHOICE_W, CHOICE_H, "Levels");
    Fl_Button *help = new Fl_Button(HELP_X, HELP_Y, HELP_W, HELP_H, "Help");

public:
    // Constructors and Destructors
    MainWindow(std::shared_ptr<BoardModel> boardModel, HelpWindow *helpWindow);
    ~MainWindow();
    // Methods
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
     * @brief Callback for the resetLevel button, resets the level
     * @param  *widget: the resetLevel button
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void resetLevelCallback(Fl_Widget *widget, void *mainWindow);
    /**
     * @brief Callback for the changeLevel button, opens a new window with all levels
     * @param  *widget: The changeLevel button
     * @param  *mainWindow: Instance of mainWindow
     * @retval None
     */
    static void changeLevelCallback(Fl_Widget *widget, void *mainWindow);
    /**
     * @brief Callback for the reset minimum steps button, resets the minimum steps
     * @param  *widget: The reset minimum steps button
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
