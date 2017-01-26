#include "A.h"
#include <iostream>
#include <stdio.h>
#include <queue>
#include <cmath>
#include <stack>
#include <limits>
class Compare {
	public:
		bool operator() (Point p, Point p1) {
			if(p.fscore > p1.fscore)
				return true;
			return false;
		}
};
void A::compute(vector<LinkedList*> adjList, int startNode, int endNode, vector<Point> points) {
	bool closedSet[points.size()];
	priority_queue<Point, vector<Point>, Compare> queue;
	int cameFrom[points.size()];
	double gScore[points.size()];
	bool openSet[points.size()];
	for(int i = 0; i<points.size(); i++) {
		gScore[i] = numeric_limits<double>::max();
		closedSet[i] = false;
		openSet[i] = false;
		cameFrom[i] = -1;
	}
	gScore[startNode] = 0.0;

	Point p;
	p.fscore = heuristic_cost(points.at(startNode), points.at(endNode));
	p.nodeID = startNode;
	openSet[startNode] = true;
	queue.push(p);
	cameFrom[startNode] = -2;
	while(!queue.empty()) {
		Point curr = queue.top();	

		if(curr.nodeID == endNode) {
			printf("%0.6f\n", gScore[curr.nodeID]);
			//cout <<gScore[curr -> nodeID] << endl;

			int u = endNode;
			stack<int> stack;
			while(cameFrom[endNode] != -1) {
				if(u == -2) {
					break;
				}
				stack.push(u);
				u = cameFrom[u];
			}
			int n1 = stack.top();
			stack.pop();
			while(!stack.empty()) {
				int n2 = stack.top();
				stack.pop();

				LinkedList* linky = adjList.at(n1);
				Edge* edgy = linky -> head;
				while(edgy != NULL) {
					if(edgy -> node == n2) {
						cout << edgy -> edgeID << endl;
						break;
					}
					edgy = edgy -> next;
				}
				n1 = n2;
			}
			return;
		}
		queue.pop();
		openSet[curr.nodeID] = false;
		closedSet[curr.nodeID] = true;
		LinkedList* link = adjList.at(curr.nodeID);
		Edge *edge = link -> head;
		while(edge != NULL) {
			if(closedSet[edge -> node] == true) {
				edge = edge -> next;
				continue;
			}

			double tentscore = gScore[curr.nodeID] + edge -> weight;
			//og code
			/*
			   if(openSet[edge -> node] == false) {
			   openSet[edge -> node] = true;
			   Point* neigh = new Point();
			   neigh -> fscore = tentscore + heuristic_cost(points.at(edge -> node), points.at(endNode));
			   neigh -> nodeID = edge -> node;
			   neigh -> xcord = points.at(edge -> node) -> xcord;
			   neigh -> ycord = points.at(edge -> node) -> ycord;
			   queue.push(neigh);
			   }*/

			//delete this thing
			//non og code
			if(tentscore < gScore[edge -> node]) {
				Point neigh;
				neigh.fscore = tentscore + heuristic_cost(points.at(edge -> node), points.at(endNode));
				neigh.nodeID = edge -> node;
				//neigh -> xcord = points.at(edge -> node) -> xcord;
				//neigh -> ycord = points.at(edge -> node) -> ycord;
				queue.push(neigh);
				openSet[edge -> node] = true;
				cameFrom[edge -> node] = curr.nodeID;
				gScore[edge -> node] = tentscore;

			}
			edge = edge -> next;

			//og code
			/*
			   else if(tentscore >= gScore[edge -> node]) {
			   edge = edge -> next;
			   continue; // this is not a better path
			   }

			   cameFrom[edge -> node] = curr -> nodeID;
			   gScore[edge -> node] = tentscore;
			   edge = edge -> next;
			   */
		}
	}
	cout << "Inf" << endl;
}

double A::heuristic_cost(Point p1, Point p2) {
	double f1 = p2.xcord - p1.xcord;
	f1 = f1*f1;

	double f2 = p2.ycord - p1.ycord;
	f2 = f2 * f2;
	return sqrt(f1+f2);
}
