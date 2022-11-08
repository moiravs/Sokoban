#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    MainWindow window;
    window.show(argc, argv);
    return Fl::run();
}