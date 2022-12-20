
#ifndef BOX_HPP
#define BOX_HPP
class Box
{
    int x;
    int y;
    int color;
public:
    //TODO : à mettre en private
    bool light = false;
    bool blocked = false;
    Box(int x, int y) : x{x}, y{y}{}
    int getColor(){
        return this->color;
    }
    void setColor(int color){
        this->color = color;
    }
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    bool operator==(const Box &) const;
    int operator<(Box box){
        if (x == box.x){
            return y < box.y;
        }
        else 
            return x < box.x;
    }
};
#endif