#include <vector>
class Player
{
private:
    /* data */
public:
    Player(/* args */);
    ~Player();
    void move(std::vector<std::vector<int>> matrix, int pos_y, int pos_x, int final_pos_y, int final_pos_x);
};


