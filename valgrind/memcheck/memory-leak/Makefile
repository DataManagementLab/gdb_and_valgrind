CXX = g++
CFLAGS = -g -O0
PROGRAM = memory_leak

${PROGRAM}.out: ${PROGRAM}.c
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.c

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=memcheck --track-origins=yes --leak-check=full  --show-reachable=yes ./${PROGRAM}.out
