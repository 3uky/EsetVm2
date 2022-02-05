!#/bin/bash

BINARY_DIR=./task/samples/precompiled
RESULT_DIR=./analysis/results
TMP_DIR=./res

function test() {
	if [ $# -eq 1 ]; then
		echo $1.evm
		./esetvm2 $BINARY_DIR/$1.evm | tee $TMP_DIR/$1.res
		check_result $1.res
	elif [ $# -eq 2 ]; then
		echo $1.evm \(input: $2\)
		echo $2 | ./esetvm2 $BINARY_DIR/$1.evm | tee $TMP_DIR/$1.res
		check_result $1.res
	fi
}

function check_result() {
	RESULT=""

	if [ $# -eq 1 ]; then
		RESULT=$(diff -q --strip-trailing-cr $TMP_DIR/$1 $RESULT_DIR/$1)
	elif [ $# -eq 2 ]; then
		RESULT=$(diff -q --strip-trailing-cr $1 $2)
	fi

	print_result $RESULT
}

function print_result() {
	if [ -z "$1" ]; then
		echo -e "\e[1;32m TEST OK\033[0m"
	else
		echo -e "\e[1;31m TEST FAILED\033[0m"
		echo $1
	fi
}
mkdir $TMP_DIR

make clean
make 

test math
test memory
test fibonacci_loop 10
test xor "11 29"
test xor-with-stack-frame "11 29"
test crc
test threadingBase
test lock
rm -dr $TMP_DIR

echo multithreaded_file_write.evm
./esetvm2 $BINARY_DIR/multithreaded_file_write.evm
check_result task/samples/multithreaded_file_write.bin analysis/results/multithreaded_file_write.bin

echo pseudorandom.evm \(run twice with different delay\)
RES1=$(echo 1; sleep 0.011 | ./esetvm2 $BINARY_DIR/pseudorandom.evm)
RES2=$(echo 2; sleep 0.012 | ./esetvm2 $BINARY_DIR/pseudorandom.evm)
echo $RES1
echo $RES2
RES=""; [ "$RES1" == "$RES2" ] && RES="failed"
print_result $RES

echo philosophers.evm \(specify number of philosophers e.g. 5\)
./esetvm2 $BINARY_DIR/philosophers.evm
