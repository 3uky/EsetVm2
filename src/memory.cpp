#include "../include/memory.h"

Memory::Memory(std::vector<char>& programMemory) : memory(programMemory), code(programMemory) // tbd
{
    // initial header
    // initial code
    // initial data
    // initial initial data

    // checks
}

void Memory::setHeader(HEADER initHeader)
{
    header = initHeader;
}

bool Memory::isMagicValueValid() const
{
    return std::string(memory.begin(), memory.begin()+8) == "ESET-VM2";
}

bool Memory::isHeadeSizesValid() const
{
    return (header.dataSize >= header.initialDataSize) && ((HEADER_SIZE + header.codeSize + header.dataSize + header.initialDataSize) == memory.size());
}

bool Memory::isHeaderValid() const
{
    return isMagicValueValid() && isHeadeSizesValid();
}

void Memory::printHeaderSize() const
{
    std::cout << "Data size: " << int(header.dataSize) << std::endl;
    std::cout << "Code size: " << int(header.codeSize) << std::endl;
    std::cout << "Initial Data size: " << int(header.initialDataSize) << std::endl;
}
