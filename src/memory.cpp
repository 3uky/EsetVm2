#include "../include/memory.h"

#include <iomanip>

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
    header.codeSize = readDwordForHeader(8);
    header.dataSize = readDwordForHeader(12);
    header.initialDataSize = readDwordForHeader(16);
}

void Memory::checkHeader()
{
    if(!isHeaderValid()) {
        printSizes();
        throw runtime_error(std::string("Memory validation failed"));
    }
}

VM_DWORD Memory::readDwordForHeader(int i) const
{
    return (binary[i]) | (binary[i+1] << 8) | (binary[i+2] << 16) | (binary[i+3] << 24);
}

VM_QWORD Memory::read(int64_t adr, Memory::msize msize) const
{
    if((adr + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory read out of bound!"));

    VM_QWORD res=0;
    for(int i = 0; i < msize; i++)
        res |= (VM_QWORD(data[adr + i]) << (i * 8));

    return res;
}

void Memory::write(int64_t adr, Memory::msize msize, VM_QWORD value)
{
    if((adr + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory write out of bound!"));

    for(int i = 0; i < msize; i++)
        data[adr + i] = value >> (i * 8);
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

void Memory::print() const
{
    std::cout << "Memory = ";
    for(auto& byte : data)
        std::cout << setfill('0') << setw(2) << right << std::hex << int(byte);
    std::cout << std::endl;
}
