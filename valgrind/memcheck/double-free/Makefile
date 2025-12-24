CXX = g++
CFLAGS = -g -O0
PROGRAM = double_free

${PROGRAM}.out: ${PROGRAM}.c
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.c

clean:
	rm ${PROGRAM}.out

demo: ${PROGRAM}.out
	valgrind --tool=memcheck --track-origins=yes ./${PROGRAM}.out
