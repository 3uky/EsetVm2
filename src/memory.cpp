#include "../include/memory.h"

#include <iomanip>

using namespace std;

const int MAGIC_SIZE=8;
const int HEADER_SIZE=20; // magic 8B + dataSize 4B + codeSize 4B + initialDataSize 4B = 20B
const int CODE_OFFSET=8;
const int DATA_OFFSET=12;
const int INIT_DATA_OFFSET=16;
const string MAGIC_VALUE = "ESET-VM2";

Memory::Memory(IO& iio) : io(iio), binary(io.loadBinary())
{
    initializeHeader();
    checkHeader();
    initiateCodeMemory();
    initiateDataMemory();
}

void Memory::initializeHeader()
{
    head.insert(head.begin(), binary.begin(), binary.begin() + HEADER_SIZE);

    header.codeSize = readDwordForHeader(CODE_OFFSET);
    header.dataSize = readDwordForHeader(DATA_OFFSET);
    header.initialDataSize = readDwordForHeader(INIT_DATA_OFFSET);
}

VM_DWORD Memory::readDwordForHeader(int a) const
{
    VM_QWORD res = 0;
    for(int i = 0; i < 4; i++)
        res |= (VM_QWORD(head[a + i]) << (i * 8));

    return res;
}

void Memory::checkHeader()
{
    if(!isMagicValueValid()) {
        printHeaderSizes();
        throw runtime_error(string("Header magic value isn't correct!"));
    }
    if(!isHeadeSizesValid()) {
        printHeaderSizes();
        throw runtime_error(string("Header size check failed!"));
    }
}

bool Memory::isMagicValueValid() const
{
    return string(binary.begin(), binary.begin() + MAGIC_SIZE) == MAGIC_VALUE;
}

bool Memory::isHeadeSizesValid() const
{
    return (header.dataSize >= header.initialDataSize) && ((HEADER_SIZE + header.codeSize + header.initialDataSize) == binary.size());
}

void Memory::initiateCodeMemory()
{
    code.insert(code.begin(), binary.begin() + HEADER_SIZE, binary.begin() + HEADER_SIZE + header.codeSize);
}

void Memory::initiateDataMemory()
{
    data.resize(header.dataSize);

    if(header.initialDataSize > 0)
        data.insert(data.begin(), binary.begin() + HEADER_SIZE + header.codeSize, binary.end()); // replace vector copy
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

void Memory::printHeaderSizes() const
{
    cout << "Binary file size: " << binary.size() << endl << endl;
    cout << "Magic size: " << HEADER_SIZE << endl;
    cout << "Data size: " << header.dataSize << endl;
    cout << "Code size: " << header.codeSize << endl;
    cout << "Initial Data size: " << header.initialDataSize << endl;
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
