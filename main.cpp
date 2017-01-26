#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Dijkstra.h"
#include "A.h"
using namespace std;

const static string INCORRECT = "Incorrect Usage of function\n"; 

void testAdjList(vector<LinkedList*> list) {
	for(int i = 0; i< list.size(); i++) {
		LinkedList* link = list.at(i);
		Edge* edge = link -> head;
		cout << i << ": ";
		while(edge != NULL) {
			cout << edge -> node << " ";
			edge = edge -> next;
		}
		cout << endl;
	}
}
void killAdj(vector<LinkedList*> adjList) {
	for(int i = 0; i<adjList.size(); i++) {
		delete adjList.at(i);
	}
	adjList.clear();
}
void killAll(vector<LinkedList*> adjList, vector<Point> points) {
	killAdj(adjList);
	points.clear();
}
int main(int argc, char* argv[]) {
	if(argc == 5) {
		//checkf for Dijkstra's Algo
		string str = argv[1];
		if(!str.compare("dijkstra")) {
			//they will intentionally give bad files check for bad files
			//perform dijkstra
			string fileName = argv[2];
			string startNodeStr = argv[3];
			string endNodeStr = argv[4];
			int startNode = stoi(startNodeStr);
			int endNode = stoi(endNodeStr);
			ifstream input(fileName);
			if(input.fail()) {
				cout << "file does not exist" << endl;
				return 1;
			}
			int id, node1, node2;
			double distance;
			int size = 0;
			while(input >> id >> node1 >> node2 >> distance) {
				//check for bad values
				if(node1 < 0) {
					cout << "bad node value" << endl;
					return 1;
				}
				if(node2 < 0) {
					cout << "bad node value" << endl;
					return 1;
				}
				if(distance < 0) {	
					cout << "distance cannot be negative" << endl;
					return 1;
				}
				if(node1 > size) {
					size = node1;
				}
				if(node2 > size) {
					size = node2;
				}
			}
			if(startNode > size || startNode < 0) {
				cout << "this startNode1 is not in the graph" << endl;
				return 1;
			}
			if(endNode > size || endNode < 0) {
				cout << "this endNode is not in the graph" << endl;
				return 1;
			}
			size++;
			vector<LinkedList*> nodes (size);
			for(int x = 0; x< size; x++) {
				LinkedList* linky = new LinkedList();
				linky -> head = NULL;
				nodes.at(x) = linky;
			}
			ifstream input1(fileName);
			if(input1.fail()) {
				killAdj(nodes);
				cout << "file does not exist" << endl;
				return 1;
			}
			while(input1 >> id >> node1 >> node2 >> distance) {
				Edge* edge = new Edge();
				edge -> edgeID = id;
				edge -> node = node2;
				edge -> weight = distance;
				LinkedList* list = nodes.at(node1);
				edge -> next = list -> head;
				list -> head = edge;

				Edge *edge2 = new Edge();
				edge2 -> edgeID = id;
				edge2 -> node = node1;
				edge2 -> weight = distance;
				LinkedList* list2 = nodes.at(node2);
				edge2 -> next = list2 -> head;
				list2 -> head = edge2;
			}

			//testAdjList(nodes);
			//run algorithim
			Dijkstra dij;
			dij.compute(nodes, startNode, endNode);
			//delete adj
			killAdj(nodes);
		}
		else {
			cout << INCORRECT;	
			return 1;
		}
	}
	else if(argc == 6){
		string str = argv[1];
		//same file format for both
		if((!str.compare("Astar")) || (!str.compare("ID"))) {
			string mapFileName = argv[2];
			string nodesFileName = argv[3];
			string startNodeStr = argv[4];
			string endNodeStr = argv[5];
			int startNode = stoi(startNodeStr);
			int endNode = stoi(endNodeStr);
			ifstream input(nodesFileName);
			if(input.fail()) {
				cout << "file does not exist" << endl;
				return 1;
			}
			int nodeid;
			double xcord, ycord;
			vector<Point> points;
			vector<LinkedList*> adjList;
			
			while(input >> nodeid >> xcord >> ycord) {
//				cout << nodeid << " " <<  xcord << " " << " " << ycord << endl;
				Point p;
				p.xcord = xcord;
				p.ycord = ycord;
				points.push_back(p);
				LinkedList* list = new LinkedList();
				adjList.push_back(list);
			}
			ifstream input2(mapFileName);
			if(input2.fail()) {
				cout << "file does not exist" << endl;
				killAll(adjList, points);
				return 1;
			}
			int edgeID, node1, node2;
			double weight;
			while(input2 >> edgeID >> node1 >> node2 >> weight) {
				if(node1 < 0) {
					cout << "bad node value" << endl;
					killAll(adjList, points);
					return 1;
				}
				if(node2 < 0) {
					cout << "bad node value" << endl;
					killAll(adjList, points);
					return 1;
				}
				if(weight < 0) {
					cout << "weight cannot be negative" << endl;
					killAll(adjList, points);
					return 1;
				}
				Edge *edge = new Edge();
				edge -> edgeID = edgeID;
				edge -> node = node2;
				edge -> weight = weight;

				LinkedList* list = adjList.at(node1);
				edge -> next = list -> head;
				list -> head = edge;

				Edge *edge2 = new Edge();
				edge2 -> edgeID = edgeID;
				edge2 -> node = node1;
				edge2 -> weight = weight;
				
				LinkedList* list2 = adjList.at(node2);
				edge2 -> next = list2 -> head;
				list2 -> head = edge2;
			}
			if(startNode > adjList.size()-1 || startNode < 0) {
				killAll(adjList, points);
				cout << "startNode not in graph" << endl;
				return 1;
			}
			if(endNode > adjList.size()-1 || startNode < 0) {
				killAll(adjList, points);
				cout << "endNode not in graph" << endl;
				return 1;
			}
			A a = A();
			a.compute(adjList, startNode, endNode, points);
			killAll(adjList, points);
				
		}
		else {
			cout << INCORRECT;
			return 1;
		}
	}
	else {
		cout << INCORRECT;
		return 1;
	}
	return 0;
}

