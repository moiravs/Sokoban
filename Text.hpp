#include "Constantes.hpp"
#include "Cell.hpp"
class Text
{
    std::string s;
    Point center;
    int fontSize;
    Fl_Color color;

public:
    // Constructor
    Text(std::string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK) : s{s}, center{center}, fontSize{fontSize}, color{color} {}

    // Draw
    void draw();

    // Setters and getters
    std::string getString()
    {
        return s;
    }
    void setString(const std::string &newString)
    {
        s = newString;
    }
    int getFontSize()
    {
        return fontSize;
    }
    void setFontSize(int newFontSize)
    {
        fontSize = newFontSize;
    }
    Point getCenter()
    {
        return center;
    }
    void setCenter(Point newCenter)
    {
        center = newCenter;
    }
};