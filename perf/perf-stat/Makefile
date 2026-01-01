TARGET=compute_bound

${TARGET}:${TARGET}.c
	gcc -g -O1 ${TARGET}.c -o ${TARGET}.out -lm

demo: ${TARGET}
	perf stat -d ./${TARGET}.out

clean:
	rm ./${TARGET}.out
