CC = g++
CFLAGS = -g -Wall -std=c++11 -fopenmp
DEPS = 
OBJ = main.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

pa6: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	-rm *.o
