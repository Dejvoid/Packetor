OBJS	= bin/main.o bin/options.o
SOURCE	= src/main.cpp src/options.cpp
HEADER	= include/options.hpp
OUT	= Makefile
CC	 = g++
FLAGS	 = -g -c -Wall -Wextra -Werror --std=c++17 -Iinclude


LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

bin/main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp -std=c++17 

bin/options.o: src/options.cpp
	$(CC) $(FLAGS) src/options.cpp -std=c++17


clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)


#g++ include/options.hpp src/options.cpp src/main.cpp -Iinclude