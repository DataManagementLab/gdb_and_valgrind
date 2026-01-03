TARGET=compute_bound

${TARGET}.out:${TARGET}.c
	gcc -g -O1 ${TARGET}.c -o ${TARGET}.out -lm

demo: ${TARGET}.out
	perf stat -d ./${TARGET}.out

clean:
	rm ./${TARGET}.out
