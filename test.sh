!#/bin/bash
BINARY_DIR=./task/samples/precompiled
RESULT_DIR=./analysis/results
TMP_DIR=./res

function check_result() {
	if diff -q --strip-trailing-cr $TMP_DIR/$1 $RESULT_DIR/$1 &>/dev/null; then
		echo -e "\e[1;32m TEST OK\033[0m"
	else
		echo -e "\e[1;31m TEST FAILED\033[0m"
	fi
}


function check_result_a_b() {
	if diff -q --strip-trailing-cr $1 $2 &>/dev/null; then
		echo -e "\e[1;32m TEST OK\033[0m"
	else
		echo -e "\e[1;31m TEST FAILED\033[0m"
	fi
}

mkdir $TMP_DIR

make clean
make 

echo math.evm
./esetvm2 $BINARY_DIR/math.evm | tee $TMP_DIR/math.res
check_result math.res

echo memory.evm
./esetvm2 $BINARY_DIR/memory.evm | tee $TMP_DIR/memory.res
check_result memory.res

echo fibonacci_loop.evm \(input: 10\)
echo 10 | ./esetvm2 $BINARY_DIR/fibonacci_loop.evm | tee $TMP_DIR/fibonacci_loop.res
check_result fibonacci_loop.res

echo xor.evm \(input: 11 29\)
echo 11 29 | ./esetvm2 $BINARY_DIR/xor.evm | tee $TMP_DIR/xor.res
check_result xor.res

echo xor-with-stack-frame.evm
echo 11 29 | ./esetvm2 $BINARY_DIR/xor-with-stack-frame.evm | tee $TMP_DIR/xor-with-stack-frame.res
check_result xor-with-stack-frame.res

echo crc.evm
./esetvm2 $BINARY_DIR/crc.evm | tee $TMP_DIR/crc.res
check_result crc.res

echo threadingBase.evm
./esetvm2 $BINARY_DIR/threadingBase.evm | tee $TMP_DIR/threadingBase.res
check_result threadingBase.res

echo lock.evm
./esetvm2 $BINARY_DIR/lock.evm | tee $TMP_DIR/lock.res
check_result lock.res

rm -dr $TMP_DIR

echo multithreaded_file_write.evm
./esetvm2 $BINARY_DIR/multithreaded_file_write.evm
check_result_a_b task/samples/multithreaded_file_write.bin analysis/results/multithreaded_file_write.bin

echo pseudorandom.evm \(check manually\)
sleep 0.0$((($RANDOM % 100))); echo 1 | ./esetvm2 $BINARY_DIR/pseudorandom.evm

echo philosophers.evm \(specify number of philosophers e.g. 5\)
./esetvm2 $BINARY_DIR/philosophers.evm
