#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"
#include "io.h"

typedef struct {
    VM_DWORD codeSize;
    VM_DWORD dataSize;
    VM_DWORD initialDataSize;
} HEADER ;

class Memory
{
public:
    enum msize { byte=1, word=2, dword=4, qword=8 };

    Memory(IO&);

    IO &io;

    std::vector<VM_BYTE> head;
    std::vector<VM_BYTE> code;
    std::vector<VM_BYTE> data;

    VM_QWORD read(int64_t, Memory::msize) const;
    void write(int64_t, Memory::msize, VM_QWORD);
    void printData() const;
    void printHeaderSizes() const;

private:
    HEADER header;

    void initiateHeader();
    void checkHeader();
    VM_DWORD readDwordForHeader(int) const; // tbd: replace with read

    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;

    void initiateCodeMemory();
    void initiateDataMemory();
};

#endif // MEMORY_H
