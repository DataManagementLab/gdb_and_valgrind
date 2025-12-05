CXX = g++
CFLAGS = -g -O0
PROGRAM = memcheck_tutorial

${PROGRAM}.out: ${PROGRAM}.cpp
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.cpp

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=memcheck --track-origins=yes ./${PROGRAM}.out
