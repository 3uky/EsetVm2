#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"

class Memory
{
public:
    std::vector<char>& memory;
    std::vector<char>& code;
    //std::array<char>& data;

private:
    HEADER header;

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

public:
    Memory(std::vector<char>&);

    void setHeader(HEADER);
    bool isHeaderValid() const;
    void printSizes() const;
};

#endif // MEMORY_H
