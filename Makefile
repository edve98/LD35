CC = g++
CPP = $(shell find . -name '*.cpp')
H = $(shell find . -name '*.h')
LDFLAGS = -I$$HOME/Coding/Terminal-Play/src -L$$HOME/Coding/Terminal-Play/build -lterminalplay

build: $(CPP) $(H)
	$(CC) -std=c++11 $(LDFLAGS) -c $(CPP) $(H)
	mkdir -p obj
	mv *.o obj/
	$(CC) obj/*.o $(LDFLAGS) -o game
	rm src/*.gch

play: build
	./game

clean:
	rm -r obj
	rm -f *.o
	rm -f src/*.gch
