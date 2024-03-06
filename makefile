main: main.o
	cc -o main main.o

nfl: nfl.o
	cc -o nfl nfl.o

clean:
	rm -f main main.o nfl nfl.o
