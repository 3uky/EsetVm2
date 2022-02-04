#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

#include "global.h"

class IO
{
public:
    enum Filetype { evm, bin };

    IO(std::string& ifilename);

    unsigned int read(unsigned int, unsigned int, std::vector<VM_BYTE>&, Filetype type=Filetype::evm);
    void write(unsigned int, unsigned int, std::vector<VM_BYTE>&);
    unsigned int getFileSize() const;

private:
    void InitializeFilenameBinary();
    void InitializeFilesize();

    std::string& getFileName(Filetype);
    std::string& filename;
    std::string filenameBinary;
    unsigned int filesize;
};

#endif // IO_H
