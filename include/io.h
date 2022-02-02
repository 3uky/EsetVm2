#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

#include "global.h"

class IO
{
public:
    IO(std::string& ifilename);

    std::vector<char> loadBinary();
    int read(int, int, std::vector<VM_BYTE>&);

private:
    std::string& filename;
    std::string filenameBinary;
};

#endif // IO_H
