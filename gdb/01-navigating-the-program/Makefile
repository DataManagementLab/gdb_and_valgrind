CXX = g++

CFLAGS = -g -O0

PROGRAM = navigate

${PROGRAM}.out: ${PROGRAM}.cpp
	$(CXX) $(CFLAGS) -o $(PROGRAM).out $(PROGRAM).cpp

clean:
	rm $(PROGRAM).out

demo: ${PROGRAM}.out
	gdb -x gdb.exe
