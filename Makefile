all: path

path: main.cpp Dijkstra.cpp A.cpp
	g++ -std=c++11 -g -o path main.cpp Dijkstra.cpp A.cpp

clean:
	rm -rf path
