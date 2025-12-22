TARGET=branch_bound.out

${TARGET}:${TARGET}.c
	gcc -O3 ${TARGET}.c -o ${TARGET} -lm

stat: ${TARGET}
	perf stat -d -e cycles,cpu-clock,cache-references,cache-misses,branch-instructions,branch-misses,L1-icache-load-misses,L1-dcache-loads,L1-dcache-load-misses,L1-dcache-stores,dTLB-loads,dTLB-loads-misses,dTLB-stores,dTLB-store-misses,iTLB-load-misses,mem-loads,mem-stores,page-faults ./${TARGET}

record: ${TARGET}
	perf record ./${TARGET}
	perf report

annotate: ${TARGET}
	perf record ./${TARGET}
	perf annotate -e cycles,cpu-clock -d ./${TARGET}

top: ${TARGET}
	perf top ./${TARGET}

clean: ${TARGET}
	rm ./${TARGET}
