CFLAGs=-Wall -Wextra -ggdb

all: shell shell.i shell.s

shell.o: main.cpp
		g++ $(CFLAGS) -Wa,-a=shell.lst -c main.cpp

shell: main.o
		g++ $(CFLAGS) -Bstatic -Wl,-Map=shell.map -o shell main.o

shell.i: main.cpp
		g++ -E main.cpp >shell.i

shell.s: main.cpp
		g++ -S main.cpp

# adding verbose for seeing all command line
verbose:
		g++ -v $(CFLAGS) -Wextra -c main.cpp

# cleaning after compilation
clean:
		rm -f shell shell.i main.s main.o shell.map