CXX = g++
CFLAGS = -g -O0
PROGRAM = race

${PROGRAM}.out: ${PROGRAM}.cpp
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.cpp

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=helgrind ./${PROGRAM}.out
