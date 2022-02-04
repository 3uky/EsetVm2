!#/bin/bash
BINARY_DIR=./task/samples/precompiled
RESULT_DIR=./analysis/results
TMP_DIR=res

mkdir $TMP_DIR

make clean
make 

echo math.evm
./esetvm2 $BINARY_DIR/math.evm | tee $TMP_DIR/math.res
diff --strip-trailing-cr $TMP_DIR/math.res $RESULT_DIR/math.res

echo memory.evm
./esetvm2 $BINARY_DIR/memory.evm | tee $TMP_DIR/memory.res
diff --strip-trailing-cr $TMP_DIR/memory.res $RESULT_DIR/memory.res

echo fibonacci_loop.evm
echo 10 | ./esetvm2 $BINARY_DIR/fibonacci_loop.evm | tee $TMP_DIR/fibonacci_loop.res
diff --strip-trailing-cr $TMP_DIR/fibonacci_loop.res $RESULT_DIR/fibonacci_loop_10.res

echo xor.evm
echo 11 29 | ./esetvm2 $BINARY_DIR/xor.evm | tee $TMP_DIR/xor.res
diff --strip-trailing-cr $TMP_DIR/xor.res $RESULT_DIR/xor_11_29.res

echo xor-with-stack-frame.evm
echo 11 29 | ./esetvm2 $BINARY_DIR/xor-with-stack-frame.evm | tee $TMP_DIR/xor-with-stack-frame.res
diff --strip-trailing-cr $TMP_DIR/xor-with-stack-frame.res $RESULT_DIR/xor_11_29.res

echo crc.evm
./esetvm2 $BINARY_DIR/crc.evm | tee $TMP_DIR/crc.res
diff --strip-trailing-cr $TMP_DIR/crc.res $RESULT_DIR/crc.res

echo threadingBase.evm
./esetvm2 $BINARY_DIR/threadingBase.evm | tee $TMP_DIR/threadingBase.res
diff --strip-trailing-cr $TMP_DIR/threadingBase.res $RESULT_DIR/threadingBase.res

echo lock.evm
./esetvm2 $BINARY_DIR/lock.evm | tee $TMP_DIR/lock.res
diff --strip-trailing-cr $TMP_DIR/lock.res $RESULT_DIR/lock.res

rm -dr $TMP_DIR

echo multithreaded_file_write.evm
./esetvm2 $BINARY_DIR/multithreaded_file_write.evm
diff task/samples/multithreaded_file_write.bin analysis/results/multithreaded_file_write.bin

echo pseudorandom.evm
sleep 0.0$((($RANDOM % 100))); echo 1 | ./esetvm2 $BINARY_DIR/pseudorandom.evm

echo philosophers.evm \(specify number of philosophers e.g. 5\)
./esetvm2 $BINARY_DIR/philosophers.evm
