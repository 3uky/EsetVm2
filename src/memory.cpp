#include "../include/memory.h"

using namespace std;

const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B

Memory::Memory(vector<char>& programMemory) : memory(programMemory), code(memory.begin() + HEADER_SIZE, memory.end())
{
}

void Memory::setHeader(HEADER initHeader)
{
    header = initHeader;
}

bool Memory::isMagicValueValid() const
{
    return string(memory.begin(), memory.begin()+8) == "ESET-VM2";
}

bool Memory::isHeadeSizesValid() const
{
    return (header.dataSize >= header.initialDataSize) && ((HEADER_SIZE + header.codeSize + header.dataSize + header.initialDataSize) == memory.size());
}

bool Memory::isHeaderValid() const
{
    return isMagicValueValid() && isHeadeSizesValid();
}

void Memory::printSizes() const
{
    cout << "Binary file size: " << memory.size() << endl << endl;
    cout << "Magic size: " << HEADER_SIZE << endl;
    cout << "Data size: " << int(header.dataSize) << endl;
    cout << "Code size: " << int(header.codeSize) << endl;
    cout << "Initial Data size: " << int(header.initialDataSize) << endl;
}
