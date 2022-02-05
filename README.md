# EsetVm2

Virtual Machine for interpreting EsetVm2 (.evm) binary programs. 

## description

Input binaries (.evm) could be compiled from specific Eset assembeler (.easm) files with compiler ```task/compiler.py```. Eset assembler language is described in ```task/task.pdf```. Documentation contains also file format, bytecode description and other mechanisms. The code examples could be found in ```task/samples```. Precompiled examples are in ```task/samples/precompiled```.

## usage

```bash
make
./esetvm2 task/samples/precompiled/math.evm
```

## regression tests
```bash
./test.sh
```

## compilation easm scripts
```bash
python2 task/samples/math.easm task/samples/precompiled/math.evm
```
