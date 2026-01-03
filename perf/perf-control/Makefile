TARGET=init_and_compute

${TARGET}.out:${TARGET}.c
	gcc -g -O1 ${TARGET}.c -o ${TARGET}.out -lm

demo: ${TARGET}.out
	perf stat -D -1 --control fifo:/tmp/perf_fifo -- ./${TARGET}.out 0
	perf stat -D -1 --control fifo:/tmp/perf_fifo -- ./${TARGET}.out 1

clean:
	rm ./${TARGET}.out
