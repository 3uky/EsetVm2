#ifndef HEADER_H
#define HEADER_H

#include <vector>

#include "global.h"
#include "io.h"

const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B

class Header
{
public:
    Header(IO&);

    VM_DWORD codeSize;
    VM_DWORD dataSize;
    VM_DWORD initialDataSize;

private:
    std::vector<VM_BYTE> header;
    unsigned int filesize;

    void initialize(IO&);
    VM_DWORD readSize(unsigned int) const;
    void check();
    bool isMagicValueValid() const;
    bool isHeadeSizesValid() const;
    void printSizes() const;
};

#endif // HEADER_H
