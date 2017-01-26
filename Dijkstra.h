#ifndef ADD_H
#define ADD_H
#include<vector>
#include <iostream>

using namespace std;
typedef struct Edge {
	Edge* next;
	int edgeID;
	int node;
	double weight;

}Edge;
typedef struct LinkedList {
	Edge* head;
	~LinkedList() {
		while(head != NULL) {
			Edge* prev = head;
			head = head -> next;
			delete prev;
		}
		delete head;
	}
} LinkedList;

class Dijkstra {
	public:
		void compute(vector<LinkedList*> list, int startNode, int endNode);
};

#endif
