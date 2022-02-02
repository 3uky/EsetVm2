#include "io.h"

#include <fstream>

IO::IO(std::string& ifilename) : filename(ifilename)
{
    filenameBinary = "task/samples/crc.bin"; // tbd
}

std::vector<char> IO::loadBinary()
{
    std::ifstream f(filename, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error((std::string("Cannot open file: ") + filename));
    }
    std::vector<char> binary(std::istreambuf_iterator<char>(f), (std::istreambuf_iterator<char>()));
    f.close();

    return binary;
}

int IO::read(int storageOffset, int noBytes, std::vector<VM_BYTE>& readed)
{

    std::ifstream f(filenameBinary, std::ios::in | std::ios::binary);

    if (!f.is_open())
        throw std::runtime_error((std::string("Cannot open file: ") + filenameBinary));

    readed.resize(noBytes);

    f.seekg(storageOffset);
    f.read(reinterpret_cast<char*>(readed.data()), noBytes);
    f.close();

    readed.resize(f.gcount());

    return f.gcount();
}
