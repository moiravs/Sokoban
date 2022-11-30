#include "LogicCell.hpp"

LogicCell::LogicCell(size_t line, size_t column, cellType type){
    switch (type){
        case Normal:
        case Teleportation:
            LogicCell(this->line, this->column, Teleportation);
    }
}