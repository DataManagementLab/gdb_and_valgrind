CXX = g++
CFLAGS = -g -O0 -lm
PROGRAM = race

${PROGRAM}.out: ${PROGRAM}.c
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.c

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=helgrind ./${PROGRAM}.out
