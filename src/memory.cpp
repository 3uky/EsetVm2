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

VM_QWORD Memory::read(int64_t i, Memory::msize msize) const
{
    if((i + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory read out of bound!"));

    if(msize == Memory::msize::byte)
        return (data[i]);
    else if(msize == Memory::msize::word)
        return (data[i]) | (data[i+1] << 8);
    else if(msize == Memory::msize::dword)
        return VM_QWORD(data[i]) | (VM_QWORD(data[i+1]) << 8) | (VM_QWORD(data[i+2]) << 16) | (VM_QWORD(data[i+3]) << 24);
    else {
        VM_QWORD res = (VM_QWORD(data[i])) | (VM_QWORD(data[i+1]) << 8) | (VM_QWORD(data[i+2]) << 16) | (VM_QWORD(data[i+3]) << 24) | (VM_QWORD(data[i+4]) << 32) | (VM_QWORD(data[i+5]) << 40) | (VM_QWORD(data[i+6]) << 48) | (VM_QWORD(data[i+7]) << 56);
        return res;
    }
}

void Memory::write(int64_t i, Memory::msize msize, VM_QWORD value)
{
    if((i + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory write out of bound!"));

    if(msize == Memory::msize::byte)
        data[i] = value;
    else if(msize == Memory::msize::word) {
        data[i] = value;
        data[i+1] = value >> 8;
    }
    else if(msize == Memory::msize::dword) {
        data[i] = value;
        data[i+1] = value >> 8;
        data[i+2] = value >> 16;
        data[i+3] = value >> 24;
    }
    else {
        data[i] = value;
        data[i+1] = value >> 8;
        data[i+2] = value >> 16;
        data[i+3] = value >> 24;
        data[i+4] = value >> 32;
        data[i+5] = value >> 40;
        data[i+6] = value >> 48;
        data[i+7] = value >> 56;
    }
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

void Memory::print(int64_t adr, Memory::msize memSize) const
{
    for(int i = adr; i < (adr + memSize); i++)
        std::cout << setfill('0') << setw(2) << right << std::hex << int(data[i]);
    std::cout << std::endl;
}
