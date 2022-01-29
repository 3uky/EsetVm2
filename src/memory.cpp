#include "../include/memory.h"

using namespace std;

const int MAGIC_SIZE=8;
const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B

Memory::Memory(vector<char>& programMemory) : binary(programMemory), code(binary.begin() + HEADER_SIZE, binary.end())
{
}

void Memory::setHeader(HEADER initHeader)
{
    header = initHeader;
}

bool Memory::isMagicValueValid() const
{
    return string(binary.begin(), binary.begin() + MAGIC_SIZE) == "ESET-VM2";
}

bool Memory::isHeadeSizesValid() const
{
    return (header.dataSize >= header.initialDataSize) && ((HEADER_SIZE + header.codeSize + header.initialDataSize) == binary.size());
}

bool Memory::isHeaderValid() const
{
    return isMagicValueValid() && isHeadeSizesValid();
}

void Memory::initiateDataMemory()
{
    data.resize(header.dataSize);
}

void Memory::printSizes() const
{
    cout << "Binary file size: " << binary.size() << endl << endl;
    cout << "Magic size: " << HEADER_SIZE << endl;
    cout << "Data size: " << int(header.dataSize) << endl;
    cout << "Code size: " << int(header.codeSize) << endl;
    cout << "Initial Data size: " << int(header.initialDataSize) << endl;
}
