CXX = g++
CFLAGS = -g -O1
PROGRAM = profileme

${PROGRAM}.out: ${PROGRAM}.cpp
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.cpp

clean:
	rm ${PROGRAM}.out cachegrind.out.*

demo: ${PROGRAM}.out
	valgrind --tool=cachegrind --cache-sim=yes --branch-sim=yes ./${PROGRAM}.out
