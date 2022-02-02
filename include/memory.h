#ifndef MEMORY_H
#define MEMORY_H

#include <vector>

#include "global.h"
#include "io.h"
#include "header.h"

class Memory
{
public:
    enum Size { byte=1, word=2, dword=4, qword=8 };

    Memory(IO&);

    IO &io;

    std::vector<VM_BYTE> code;
    std::vector<VM_BYTE> data;

    VM_QWORD read(int64_t, Memory::Size) const;
    void write(int64_t, Memory::Size, VM_QWORD);
    void printData() const;

private:
    Header header;

    void initializeCodeMemory();
    void initializeDataMemory();
};

#endif // MEMORY_H
