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
    enum msize { byte=1, word=2, dword=4, qword=8 };

    std::vector<char>& binary;
    std::vector<VM_BYTE> head;
    std::vector<VM_BYTE> code;
    std::vector<VM_BYTE> data;

    Memory(std::vector<char>&);

    VM_QWORD read(int64_t, Memory::msize) const;
    void write(int64_t, Memory::msize, VM_QWORD);
    void printData() const;
    void printHeaderSizes() const;

private:
    HEADER header;

    void initializeHeader(); // tbd: initiate from file without vector copy
    void checkHeader();
    VM_DWORD readDwordForHeader(int) const; // tbd: replace with read

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

    void initiateCodeMemory(); // tbd: initiate from file without vector copy
    void initiateDataMemory(); // tbd: initiate from file without vector copy
};

#endif // MEMORY_H
