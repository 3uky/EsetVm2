#include "../include/memory.h"

using namespace std;

const int MAGIC_SIZE=8;
const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B

Memory::Memory(vector<char>& programMemory) : binary(programMemory), code(binary.begin() + HEADER_SIZE, binary.end())
{
    initializeHeader();
    checkHeader();
    initiateDataMemory();
}

void Memory::initializeHeader()
{
    header.codeSize = readDword(8);
    header.dataSize = readDword(12);
    header.initialDataSize = readDword(16);
}

void Memory::checkHeader()
{
    if(!isHeaderValid()) {
        printSizes();
        throw runtime_error(std::string("Memory validation failed"));
    }
}

VM_DWORD Memory::readDword(int i) const
{
    return (binary[i]) | (binary[i+1] << 8) | (binary[i+2] << 16) | (binary[i+3] << 24);
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
    cout << "Data size: " << header.dataSize << endl;
    cout << "Code size: " << header.codeSize << endl;
    cout << "Initial Data size: " << header.initialDataSize << endl;
}
