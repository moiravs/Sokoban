
#include "MainWindow.hpp"
#include <memory>



class StartWindow : public Fl_Window
{
private:
    Fl_Button *button = new Fl_Button(200, 200, 100, 50, "Start the game");

public:
    StartWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Start the game")
    {
        Fl::add_timeout(1.0 / refreshPerSecond, Timer_CB, this);
        resizable(this);
        this->show();

        button->tooltip("Make advanced search");
        button->callback((Fl_Callback *)ad_cb);
    }
    void draw() override
    {
        Fl_Window::draw();
        Fl_Widget *b = button;
        b->draw();
    }
    static void Timer_CB(void *userdata)
    {
        StartWindow *o = static_cast<StartWindow *>(userdata);
        o->redraw();
        Fl::repeat_timeout(1.0 / refreshPerSecond, Timer_CB, userdata);
    }

    static void ad_cb(Fl_Button *theButton, void *)
    {
    }
};

class DisplayBoard
{
    private:
        Board boardmodel;
    public:
        DisplayBoard(std::shared_ptr<Board> board){
            //MainWindow MW = new MainWindow();
            //MW.show();
            boardmodel = board;
        };
        void printBoard(){
            for (size_t i = 0; i < boardmodel->matrix.size(); i++)
            {
                for (size_t j = 0; j < boardmodel->matrix[0].size(); j++)
                {
                    std::cout << this->boardmodel[i][j] << " ";
                }
                std::cout << "\n";
            }
        }
}
class ControllerBoard{
    private:
        Board board;
    public:
        ControllerBoard(std::shared_ptr<Board> board){
            Board = board
        };
}