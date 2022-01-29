#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"

typedef struct {
    VM_DWORD codeSize;
    VM_DWORD dataSize;
    VM_DWORD initialDataSize;
} HEADER ;

class Memory
{
public:
    std::vector<char>& binary;
    std::vector<char> code;
    std::vector<char> data;

private:
    HEADER header;

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

public:
    Memory(std::vector<char>&);

    void setHeader(HEADER);
    bool isHeaderValid() const;

    void initialDataMemory();

    void printSizes() const;
};

#endif // MEMORY_H
