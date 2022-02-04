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

echo lock.evm
./esetvm2 $BINARY_DIR/lock.evm

echo multithreaded_file_write.evm
./esetvm2 $BINARY_DIR/multithreaded_file_write.evm

echo pseudorandom.evm
sleep 0.0$((($RANDOM % 100))); echo 1 | ./esetvm2 $BINARY_DIR/pseudorandom.evm

echo philosophers.evm
./esetvm2 $BINARY_DIR/philosophers.evm
