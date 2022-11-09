#include "MainWindow.cpp"

int main(int argc, char *argv[])
{

    MainWindow window;
    
    window.show();

    srand(static_cast<unsigned>(time(nullptr)));
    return Fl::run();
}