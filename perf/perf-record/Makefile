TARGET=mem_bound

${TARGET}:${TARGET}.c
	gcc -g -O1 ${TARGET}.c -o ${TARGET}.out -lm

demo: ${TARGET}
	perf record -e cycles,instructions,cache-misses,branches,branch-misses -- taskset -c 0 ./${TARGET}.out
	perf report --group ./${TARGET}.out

clean:
	rm ./${TARGET}.out
