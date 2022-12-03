
#ifndef BOX_HPP
#define BOX_HPP
class Box
{
    int x;
    int y;
    
public:
    bool light = false;
    bool blocked = false;
    Box(int x, int y){
        this->x = x;
        this->y = y;
    }
    //TODO: liste d'initialisation serait mieux
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