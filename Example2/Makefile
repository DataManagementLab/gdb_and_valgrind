CXX = g++

CFLAGS = -g

OBJS = Ex2.o

TARGET = main.out

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

clean:
	rm $(TARGET) $(OBJS)

cache_prof: $(TARGET)
	valgrind --tool=cachegrind ./$(TARGET)
