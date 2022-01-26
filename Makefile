# Define required macros here
SHELL = /bin/sh

OBJS =  main.o vm.o
CFLAGS = -Wall -g -pthread
CC = g++
INCLUDES = -I include
LIBS = -lm
SRC_DIR = src

main: ${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}
.cpp.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $<

clean:
	-rm -f *.o core *.core

# with separate src
#g++ -Wall -fexceptions -g -Iinclude -c /home/buky/eset/EsetVm2/main.cpp -o obj/Debug/main.o
#g++ -Wall -fexceptions -g -Iinclude -c /home/buky/eset/EsetVm2/src/decoder.cpp -o obj/Debug/src/decoder.o
#g++ -Wall -fexceptions -g -Iinclude -c /home/buky/eset/EsetVm2/src/vm.cpp -o obj/Debug/src/vm.o
#g++  -o bin/Debug/test obj/Debug/main.o obj/Debug/src/decoder.o obj/Debug/src/vm.o   
 


