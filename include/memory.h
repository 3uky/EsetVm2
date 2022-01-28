#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"

typedef struct {
    /* Here will be stored a data, that program is needed */
    VM_BYTE *dataArray;
    /* Here will be stack */
    //VM_QWORD stackArray[STACK_SIZE];
    /* Here will be stored a program's code */
    VM_BYTE *codeArray;
} ADDRESS_SPACE, *PADDRESS_SPACE;

typedef struct {
    VM_DWORD codeSize;
    VM_DWORD dataSize;
    VM_DWORD initialDataSize;
} HEADER ;

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
