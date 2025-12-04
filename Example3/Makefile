CXX = g++

CFLAGS = -g

OBJS = Ex3.o

TARGET = main.out

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm $(TARGET) $(OBJS)

check_threading_errors: $(TARGET)
	valgrind --tool=helgrind ./$(TARGET)
