#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "global.h"

class Argument
{
    public:
        enum type {
            mem = 1,
            reg = 0
        };

        enum memSize {
            byte = 0b00,
            word = 0b01,
            dword = 0b10,
            qword = 0b11
        };

        int index;
        VM_BYTE type;
        VM_BYTE memSize;
        VM_DWORD address;

        Argument();
        Argument(VM_BYTE, int);
        Argument(VM_BYTE, int, VM_BYTE);

        bool isRegister() const;
        bool isMemory() const;

        void print() const;
};

#endif // ARGUMENT_H
