#include "Constantes.hpp"
#include "Canvas.hpp"

class MainWindow : public Fl_Window
{
    Canvas canvas;

public:
    MainWindow();
    void draw() override;
    int handle(int event) override;
    static void Timer_CB(void *userdata);
};