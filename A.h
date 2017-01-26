#include <vector>
#include "Dijkstra.h"
using namespace std;

typedef struct Point {
	double xcord;
	double ycord;
	int nodeID;
	double fscore;
}Point;

class A {
	public:
		void compute(vector<LinkedList*> adjList, int startNode, int endNode, vector<Point> points);
		double heuristic_cost(Point p1, Point p2);
};
