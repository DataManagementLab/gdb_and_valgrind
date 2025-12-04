CXX = g++

CFLAGS = -g

OBJS = Ex1.o

TARGET = main.out

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm $(TARGET) $(OBJS)

check_mem_err: $(TARGET)
	valgrind --tool=memcheck ./$(TARGET)
