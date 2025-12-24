CXX = g++
CFLAGS = -g -O1
PROGRAM = profileme

${PROGRAM}.out: ${PROGRAM}.cpp
	${CXX} ${CFLAGS} -o ${PROGRAM}.out ${PROGRAM}.cpp

clean:
	rm ${PROGRAM}.out cachegrind.out.*

demo: ${PROGRAM}.out
	valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=./${PROGRAM}.cachegrind.out ./${PROGRAM}.out
	cg_annotate ./${PROGRAM}.cachegrind.out
