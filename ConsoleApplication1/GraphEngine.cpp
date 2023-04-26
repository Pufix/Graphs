#include <algorithm>
#include <random>
#include <fstream>
#include <windows.h>
#include <vector>
#include "GraphEngine.h"
using namespace std;
graphEngine::graphEngine() {
	location = "storage.txt";
}
graphEngine::graphEngine(string location) {
	this->location = location;
}
void graphEngine::read() {
	ifstream fin;
	fin.open(location);
	int n, m;
	fin >> n >> m;
	nodes.clear();
	edges.clear();
	nodes.resize(n);
	edges.resize(m);
	for (int i = 0; i < n; i++)
		nodes[i] = new node(i);
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		fin >> from >> to >> cost;
		edges[i].from = nodes[from];
		edges[i].to = nodes[to];
		edges[i].cost = cost;
		nodes[from]->out.push_back(nodes[to]);
		nodes[to]->in.push_back(nodes[from]);
	}
}
void graphEngine::push() {
	ofstream fout(location);
	fout << nodes.size() << " " << edges.size() << endl;
	for (int i = 0; i < edges.size(); i++) {
		fout << edges[i].from->id << " " << edges[i].to->id << " " << edges[i].cost << endl;
	}
	fout.close();
}
void graphEngine::randomGraph(int n,int m) {
	if (n < 0 || m < 0) {
		return;
	}
	if (m > n * n) {
		return;
	}
	nodes.clear();
	edges.clear();
	nodes.resize(n);
	edges.resize(m);
	for (int i = 0; i < n; i++)
		nodes[i] = new node(i);
	for (int i = 0; i < m; i++) {
		int from, to, cost;
		from = rand() % n;
		to = rand() % n;
		cost = rand() % 100;
		edges[i].from = nodes[from];
		edges[i].to = nodes[to];
		edges[i].cost = cost;
		nodes[from]->out.push_back(nodes[to]);
		nodes[to]->in.push_back(nodes[from]);
	}
}

void graphEngine::addNode() {
	nodes.push_back(new node());
}
void graphEngine::addEdge(int from, int to, int cost) {
	if (from < 0 || from >= nodes.size() || to < 0 || to >= nodes.size()) {
		return;
	}
	edges.push_back(edge(nodes[from], nodes[to], cost));
	nodes[from]->out.push_back(nodes[to]);
	nodes[to]->in.push_back(nodes[from]);
}
void graphEngine::deleteNode(int id) {
	if (id < 0 || id >= nodes.size()) {
		cout << "Invalid input" << endl;
		return;
	}
	for (int i = 0; i < edges.size(); i++) {
		if (edges[i].from->id == id || edges[i].to->id == id) {
			edges.erase(edges.begin() + i);
			i--;
		}
	}
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->id == id) {
			nodes.erase(nodes.begin() + i);
			break;
		}
	}
}
void graphEngine::deleteEdge(int from,int to) {
	if (auto i:this->nodes[to]->in) {
		if (i->id == from) {
			this->nodes[to]->in.erase(remove(this->nodes[to]->in.begin(),this->nodes[to]->in.end(),i),this->nodes[to]->in.end());
			this->nodes[from]->out.erase(remove(this->nodes[from]->out.begin(),this->nodes[from]->out.end(),this->nodes[to]),this->nodes[from]->out.end());
			this->edges.erase(remove(this->edges.begin(),this->edges.end(),edge(this->nodes[from],this->nodes[to],0)),this->edges.end());
		}
	}
}
