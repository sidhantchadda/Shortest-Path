all: lab6

lab6: main.cpp Dijkstra.cpp A.cpp
	g++ -std=c++11 -g -o lab6 main.cpp Dijkstra.cpp A.cpp

clean:
	rm -rf lab6
