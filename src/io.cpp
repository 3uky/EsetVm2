#include "io.h"

#include <fstream>
#include <filesystem> //tbd filesystem::path(filename).filename();

using namespace std;

IO::IO(string& ifilename) : filename(ifilename)
{
    filenameBinary = "./task/samples/crc.bin"; //tbd
    InitializeFilesize();
}

void IO::InitializeFilesize()
{
    ifstream f(filename, ios::in | ios::binary);

    if (!f.is_open())
        throw runtime_error(string("Cannot open file: ") + filename);

    f.seekg (0, f.end);
    filesize = f.tellg();
    f.seekg (0, f.beg);

    f.close();
}

unsigned int IO::read(unsigned int storageOffset, unsigned int noBytes, vector<VM_BYTE>& readed, Filetype type)
{
    auto& filename = getFileName(type);

    ifstream f(filename, ios::in | ios::binary);

    if (!f.is_open())
        throw runtime_error(string("Cannot open file: ") + filename);

    readed.resize(noBytes);

    f.seekg(storageOffset);
    f.read(reinterpret_cast<char*>(readed.data()), noBytes);
    f.close();

    readed.resize(f.gcount());

    return f.gcount();
}

std::string& IO::getFileName(Filetype type)
{
    if(type == Filetype::evm)
        return filename;
    else
        return filenameBinary;
}

unsigned int IO::getFileSize() const
{
    return filesize;
}

/*
vector<char> IO::loadBinary()
{
    ifstream f(filename, ios::in | ios::binary);
    if (!f.is_open()) {
        throw runtime_error((string("Cannot open file: ") + filename));
    }
    std::vector<char> binary(istreambuf_iterator<char>(f), (istreambuf_iterator<char>()));
    f.close();

    return binary;
}
*/
