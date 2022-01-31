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
    std::vector<char> code;
    std::vector<VM_BYTE> data;

    Memory(std::vector<char>&);

    VM_QWORD read(int64_t, Memory::msize) const;
    void write(int64_t, Memory::msize, VM_QWORD);
    void printData() const;

private:
    HEADER header;

    void initializeHeader();
    void checkHeader();
    VM_DWORD readDwordForHeader(int) const;

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;
    void printHeaderSizes() const;

    void initiateDataMemory();
};

#endif // MEMORY_H
