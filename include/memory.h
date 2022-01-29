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

    Memory(std::vector<char>&);

private:
    HEADER header;

    void initializeHeader();
    void checkHeader();
    VM_DWORD readDword(int) const;

    bool isHeaderValid() const;
    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

    void printSizes() const;

    void initiateDataMemory();

};

#endif // MEMORY_H
