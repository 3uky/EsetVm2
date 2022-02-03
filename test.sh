!#/bin/bash
BINARY_DIR=./task/samples/precompiled
make clean
make 

echo math.evm
./esetvm2 $BINARY_DIR/math.evm

echo memory.evm
./esetvm2 $BINARY_DIR/memory.evm

echo xor.evm
echo 11 29 | ./esetvm2 $BINARY_DIR/xor.evm

echo xor-with-stack-frame.evm
echo 11 29 | ./esetvm2 $BINARY_DIR/xor-with-stack-frame.evm

echo crc.evm
./esetvm2 $BINARY_DIR/crc.evm

echo threadingBase.evm
./esetvm2 $BINARY_DIR/threadingBase.evm
