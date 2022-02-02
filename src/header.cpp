#include <string>

#include "header.h"
#include "io.h"

using namespace std;

const int MAGIC_SIZE=8;
const int CODE_OFFSET=8;
const int DATA_OFFSET=12;
const int INIT_DATA_OFFSET=16;
const string MAGIC_VALUE = "ESET-VM2";

Header::Header(IO& io)
{
    initialize(io);
    check();
}

void Header::initialize(IO& io)
{
    io.read(0, HEADER_SIZE, header);

    codeSize = readSize(CODE_OFFSET);
    dataSize = readSize(DATA_OFFSET);
    initialDataSize = readSize(INIT_DATA_OFFSET);
    filesize = io.getFileSize();
}

VM_DWORD Header::readSize(unsigned int offset) const
{
    VM_QWORD res = 0;
    for(int i = 0; i < 4; i++)
        res |= (VM_QWORD(header[offset + i]) << (i * 8));

    return res;
}

void Header::check()
{
    if(!isMagicValueValid()) {
        printSizes();
        throw runtime_error(string("Header magic value isn't correct!"));
    }
    if(!isHeadeSizesValid()) {
        printSizes();
        throw runtime_error(string("Header size check failed!"));
    }
}

bool Header::isMagicValueValid() const
{
    return string(header.begin(), header.begin() + MAGIC_SIZE) == MAGIC_VALUE;
}

bool Header::isHeadeSizesValid() const
{
    return (dataSize >= initialDataSize) && ((HEADER_SIZE + codeSize + initialDataSize) == filesize);
}

void Header::printSizes() const
{
    cout << "Binary file size: " << filesize << endl << endl;
    cout << "Magic size: " << HEADER_SIZE << endl;
    cout << "Data size: " << dataSize << endl;
    cout << "Code size: " << codeSize << endl;
    cout << "Initial Data size: " << initialDataSize << endl;
}
