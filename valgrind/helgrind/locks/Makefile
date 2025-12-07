CXX = g++
CFLAGS = -g -O0 -DNDEBUG
PROGRAM = locks

${PROGRAM}.out: ${PROGRAM}.c
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.c

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=helgrind -s ./${PROGRAM}.out
