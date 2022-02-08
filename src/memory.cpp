#include "memory.h"

#include <iomanip>

using namespace std;

Memory::Memory(IO& iio) : io(iio), header(iio)
{
    initializeCodeMemory();
    initializeDataMemory();
}

void Memory::initializeCodeMemory()
{
    io.read(HEADER_SIZE, header.codeSize, code);
}

void Memory::initializeDataMemory()
{
    if(header.initialDataSize > 0)
        io.read(HEADER_SIZE + header.codeSize, header.initialDataSize, data);

    data.resize(header.dataSize);
}

VM_QWORD Memory::read(int64_t adr, Memory::Size msize) const
{
    if((adr + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory read out of bound!"));

    VM_QWORD res=0;
    for(int i = 0; i < msize; i++)
        res |= (VM_QWORD(data[adr + i]) << (i * 8));

    return res;
}

void Memory::write(int64_t adr, Memory::Size msize, VM_QWORD value)
{
    if((adr + msize) > int64_t(data.size()))
        throw runtime_error(std::string("Memory write out of bound!"));

    for(int i = 0; i < msize; i++)
        data[adr + i] = value >> (i * 8);
}

void Memory::printData() const
{
    if(MEMORY_PRINT_LIMIT > data.size())
    {
        cout << "Memory = ";
        for(auto& byte : data)
            cout << setfill('0') << setw(2) << right << hex << int(byte);
        cout << endl;
    }
    else {
        cout << "Memory = ";
        for(size_t i = 0; i < MEMORY_PRINT_LIMIT; i++)
            cout << setfill('0') << setw(2) << right << hex << int(data[i]);
        cout << " ..." << endl;
    }
}
