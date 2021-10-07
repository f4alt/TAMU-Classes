all: shell

main.o: main.cpp
	g++ -c -g main.cpp

shell: main.o
	g++ -o shell main.o

clean:
	rm *.o
	rm shell
