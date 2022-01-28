#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"

const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B

class Memory
{
public:
    std::vector<char>& memory;
    std::vector<char>& code;

private:
    HEADER header;

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

public:
    Memory(std::vector<char>&);

    void setHeader(HEADER);
    bool isHeaderValid() const;
    void printHeaderSize() const;
};

#endif // MEMORY_H
