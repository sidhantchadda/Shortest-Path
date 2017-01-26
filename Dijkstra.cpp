#include "Dijkstra.h"
#include <iostream>
#include <queue>
#include <stack>
#include<limits>
typedef struct Node {
	int id;
	double dist;
} Node;

class Compare {
public:
	bool operator() (Node node, Node node1) {
		if(node.dist > node1.dist)
			return true;
		return false;
	}
};
void Dijkstra::compute(vector<LinkedList*> list, int startNode, int endNode) {
	int listSize = list.size();
	double dist[listSize];
	int prev[listSize];
	for(int i = 0; i<listSize; i++) {
		prev[i] = -1;
	}
	priority_queue<Node, vector<Node>, Compare> queue;
	
	bool visited[list.size()];
	dist[startNode] = 0.0;
	for(int i = 0; i<list.size(); i++) {
		if(i != startNode) {
			dist[i] = numeric_limits<double>::infinity();
		}
		prev[i] = -1;
		Node node;
		node.id = i;
		node.dist = dist[i];
		visited[node.id] = false;
		queue.push(node);		
	}
	prev[startNode] = -2;


	//everything is right up to this point
	while(!queue.empty()) {
		Node node = queue.top();
		LinkedList* link = list.at(node.id);
		visited[node.id] = true;
		queue.pop();
		Edge *edge = link -> head;
		
		//found target
		if(node.id == endNode) {
			cout << dist[endNode] << endl;
			int u = endNode;
			stack<int> stack;
			while(prev[endNode] != -1) {
				if(u == -2) {
					break;
				}
				stack.push(u);
				u = prev[u];
			}
			int n1 = stack.top();
			stack.pop();
			while(!stack.empty()) {
				int n2 = stack.top();
				stack.pop();

				LinkedList* link = list.at(n1);
				Edge* edgy = link -> head;
				while(edgy != NULL) {
					if(edgy -> node == n2) {
						cout << edgy -> edgeID << endl;
						break;
					}
					edgy = edgy -> next;
				}
				n1 = n2;
			}
			//come here to break
			//delete queue here
			return;
		}
		while(edge != NULL) {
			double alt = dist[node.id] + edge -> weight;
			if(alt < dist[edge -> node]) { // a shorter path to v has been found
				Node newNode;
				newNode.id = edge -> node;
				newNode.dist = alt;
				dist[edge -> node] = alt;
				prev[edge -> node] = node.id;
				queue.push(newNode);
			}
			edge = edge -> next;
		}
	}
	cout << "Inf" << endl;
}
