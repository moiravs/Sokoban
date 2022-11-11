#include "Board.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>  // fprintf()
#include <stdlib.h> // exit()
#include <fstream>

std::string Board::readFileIntoString(std::string fileName)
{
    std::ifstream ifs(fileName);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    return content;
}

std::vector<std::vector<int>> Board::getBoard(std::string fileContent)
{
    std::vector<std::vector<int>> lines;
    std::vector<int> line;
    for (size_t index = 0; index < fileContent.size(); index++)
    {
        if ((fileContent[index] == '\n'))
        {
            lines.push_back(line);
            line.clear();
        }
        else if (fileContent[index] != ' ')
        {
            line.push_back(atoi(&fileContent[index]));
        }
    }
    for (size_t i = 0; i < 8; i++)
    {
        /* code */
        std::cout << lines[i][0];
        std::cout << lines[i][1];
        std::cout << lines[i][2];
        std::cout << lines[i][3];
        std::cout << lines[i][4];
        std::cout << lines[i][5];
        std::cout << lines[i][6];
        std::cout << lines[i][7] << std::endl;
    }

    return lines;
}
