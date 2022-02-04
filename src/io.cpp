#include "io.h"

#include <fstream>
#include <string>

using namespace std;

IO::IO(string& ifilename) : filename(ifilename)
{
    InitializeFilenameBinary();
    InitializeFilesize();
}

void IO::InitializeFilenameBinary()
{
    std::string path = filename.substr(0, filename.find_last_of("/\\"));
    std::string base_filename = filename.substr(filename.find_last_of("/\\") + 1);
    std::string::size_type const p(base_filename.find_last_of('.'));
    std::string file_without_extension = base_filename.substr(0, p);
    //filenameBinary = path + "/" + file_without_extension + ".bin"; // Do you expect to have bin file in same folder?
    filenameBinary = path + "/../" + file_without_extension + ".bin"; // Do you expect to have bin file in previous folder?
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

void IO::write(unsigned int storageOffset, unsigned int noBytes, vector<VM_BYTE>& toWrite)
{
    ofstream f(filenameBinary, ios::binary | ios::out | ios::in);

    if (!f.is_open())
        throw runtime_error(string("Cannot open file: ") + filenameBinary);

    f.seekp(storageOffset);
    f.write(reinterpret_cast<char*>(toWrite.data()), noBytes);

    f.close();
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
