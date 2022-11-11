#include <vector>
#include <string>
class Board
{
private:
    /* data */
public:
    std::string readFileIntoString(std::string fileName);
    std::vector<std::vector<int>> getBoard(std::string fileContent);
};