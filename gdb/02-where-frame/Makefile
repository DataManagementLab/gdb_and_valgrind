CXX = g++

CFLAGS = -g -O0

PROGRAM = where-frame

${PROGRAM}.out: ${PROGRAM}.cpp
	$(CXX) $(CFLAGS) -o $(PROGRAM).out $(PROGRAM).cpp

clean:
	rm $(PROGRAM).out

demo: ${PROGRAM}.out
	gdb -q -x gdb.exe
