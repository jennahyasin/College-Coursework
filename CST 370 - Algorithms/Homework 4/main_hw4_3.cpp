/*
 * INSTRUCTION:
 *     This is a C++ starting code for hw4_3.
 *     When you finish the development, download this file.
 *     Note that the current filename is "main.cpp".
 *     But rename it to "main_hw4_3.cpp".
 *     After that, upload the renamed file on Canvas.
 */

// Finish the head comment with Abstract, Name, and Date.
/*
 * Title: main_hw4_3.cpp
 * Abstract: This program is an implementation of Kahn's Algorithm on a graph
 *  whos info is inputted by user and ultiamtely displays the initial in-degree
 *  values of all vertices and the topological order. 
 * Name: Jennah Yasin 
 * Date: November 29, 2022
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// function that takes in the inputted graph infor and starting inDegrees
// and displays its topological order based on Kahn's Algorithm
void topologicalSorting(vector<vector<int>> &g, vector<int> &inDegrees) {
	// queue that holds all vertices that have in-degree value of 0
	queue<int> queue;
	// vector that holds topological order of graph
	vector<int> order;
	// keeps track of visited vertices
	int visited = 0;

	// add all vertices that initially have in-degree values of 0 to the queue
	for (int i = 0; i < g.size(); i++) {
		if (inDegrees[i] == 0) {
			queue.push(i);
		}
	}

	// do until queue is empty (=all vertices have been visited)
	while (!queue.empty()) {
		visited++;
		// for every current element and its adjacent/neighbor vertices
		for (auto i : g[queue.front()]) {
			// when visited, decrease in-degree values by 1
			inDegrees[i]--;
			// if in degree value becomes 0 after decrementing, add those
			// vertices to the queue
			if (inDegrees[i] == 0) {
				queue.push(i);
			}
		}
		// add the vertices from the queue to the order vector to hold
		// topological order
		order.push_back(queue.front());
		// take element off of queue to start at next vertice
		queue.pop();
	}

	// if there is still elements that haven't been visited,
	// that means there is a cycle, no order.
	if (visited != g.size()) {
		cout << "No Order:" << endl;
	}
	// otherwise display the topological order
	else {
		cout << "Order:";
		// displays the elements in the order vector
		for (int i = 0; i < order.size(); i++) {
			// if current element is the last element, don't add arrow after
			if (i == order.size() - 1) {
				cout << order[i];
			}
			// otheriwse, add arrows between all other vertices
			else {
				cout << order[i] << "->";
			}
		}
		cout << endl;
	}
}

int main() {
	vector<vector<int>> graph;
	// total number of total vertices in graph
	int numVertices;
	cin >> numVertices;

	// resize graph to fit number of vertices
	graph.resize(numVertices);

	// number of total edges to be in graph
	int numEdges;
	cin >> numEdges;

	for (int i = 0; i < numVertices; i++) {
		graph[i].resize(numVertices);
	}

	int source, destination;
	int count = 0;
	// initialize all vertices in in-degree as 0 and hold
	vector<int> inDegrees(numVertices, 0);

	// add edges between vertices for all edges
	for (int i = 0; i < numEdges; i++) {
		cin >> source;
		cin >> destination;
		graph[source].push_back(destination);
		// set adjacent edges to 1 in 2d matrix
		graph[source][destination] = 1;
		// add the count of each vertex value's in-degree
		inDegrees[destination]++;
	}
	// display the in-degree values of all num vertices initially
	for (int i = 0; i < numVertices; i++) {
		cout << "In-degree[" << i << "]:" << inDegrees[i] << endl;
	}
	// run the topologicaSorting function on given graph and initially set
	// inDegrees
	topologicalSorting(graph, inDegrees);

	return 0;
}
