#pragma once
#include <algorithm>
#include <random>
#include <fstream>
#include <windows.h>
#include <vector>
#include <iostream>
using namespace std;
class node {
public:
	int id;
	vector<node*> in;
	vector<node*> out;
	node() {
		this->id = -1;
	}
	node(int id) {
		this->id = id;
	}
};
class edge {
public:
	int cost;
	node* from;
	node* to;
	edge() {
		cost = -1;
		from = NULL;
		to = NULL;
	}
	edge(node* from, node* to, int cost) {
		this->from = from;
		this->to = to;
		this->cost = cost;
	}
	edge(node* from, node* to) {
		this->from = from;
		this->to = to;
		this->cost = 0;
	}
};
class graphEngine {
public:
	graphEngine();
	graphEngine(string location);
	vector <node*> nodes;
	vector <edge> edges;
	vector <node*> oldNodes;
	vector <edge> oldEdges;
	string location;
	void push();
	void read();
	void randomGraph(int nodes,int edges);
	void addNode();
	void addEdge(int from, int to,int cost);
	void deleteNode(int id);
	void deleteEdge(int from,int to);
	void print();
};
