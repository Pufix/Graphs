#include<iostream>
#include<fstream>
#include<vector>
#include <windows.h>
#include <random>
using namespace std;
string location;
class node {
public:
	int id;
	vector <node*> in;
	vector <node*> out;
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
};
vector <node*> nodes;
vector <edge> edges;
vector <node*> oldNodes;
vector <edge> oldEdges;
void read() {
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
void push() {
	ofstream fout(location);
	fout << nodes.size() << " " << edges.size() << endl;
	for (int i = 0; i < edges.size(); i++) {
		fout << edges[i].from->id << " " << edges[i].to->id << " " << edges[i].cost << endl;
	}
	fout.close();
}
void randomGraph() {
	int n, m;
	cin >> n >> m;
	if (n < 0 || m < 0) {
		cout << "Invalid input" << endl;
		return;
	}
	if (m > n * n) {
		cout << "Invalid input" << endl;
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
int main() {
	bool ok;
	TCHAR buffer[1000] = { 0 };
	GetModuleFileName(NULL, buffer, 1000);
	location = string(buffer);
	location = location.substr(0, location.find_last_of("\\"));
	location = location.substr(0, location.find_last_of("\\"));
	location = location.substr(0, location.find_last_of("\\"));
	location += "\\storage.txt";
	bool running = true;
	while (running) {
		cout << endl;
		cout << endl;
		cout << endl;
		cout << "1. Read graph from file" << endl;
		cout << "2. Push graph to file" << endl;
		cout << "3. Generate random graph" << endl;
		cout << "4. Get egdes count" << endl;
		cout << "5. Get nodes count" << endl;
		cout << "6. Get inbount of a node" << endl;
		cout << "7. Get outbound of a node" << endl;
		cout << "8. Get cost of an edge" << endl;
		cout << "9. Set cost of an edge" << endl;
		cout << "10. Get in degree of a node" << endl;
		cout << "11. Get out degree of a node" << endl;
		cout << "12. Add node" << endl;
		cout << "13. Add edge" << endl;
		cout << "14. Remove node" << endl;
		cout << "15. Remove edge" << endl;
		cout << "16. Copy graph" << endl;
		cout << "17. Restore graph" << endl;
		cout << "0. Exit" << endl;
		int choice;
		cin >> choice;
		cout << endl;
		cout << endl;
		cout << endl;
		cout << endl;
		switch (choice) {
		case 1:
			read();
			break;
		case 2:
			push();
			break;
		case 3:
			randomGraph();
			break;
		case 4:
			cout << edges.size() << endl;
			break;
		case 5:
			cout << nodes.size() << endl;
			break;
		case 6:
			int id;
			cout << "Enter node id: ";
			cin >> id;
			for (int i = 0; i < nodes[id]->in.size(); i++) 
				cout << nodes[id]->in[i]->id << " ";
			cout << endl;
			break;
		case 7:
			cout << "Enter node id: ";
			cin >> id;
			for (int i = 0; i < nodes[id]->out.size(); i++)
				cout << nodes[id]->out[i]->id << " ";
			cout << endl;
			break;
		case 8:
			int from, to;
			cout << "Enter from and to: ";
			cin >> from >> to;
			ok = true;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == from && edges[i].to->id == to) {
					cout << edges[i].cost << endl;
					ok = false;
					break;
				}
			}
			if (ok)
				cout << "Not found" << endl;
			break;
		case 9:
			cout << "Enter from and to: ";
			cin >> from >> to;
			int cost;
			cout << "Enter cost: ";
			cin >> cost;
			ok = true;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == from && edges[i].to->id == to) {
					edges[i].cost = cost;
					ok = false;
					break;
				}
			}
			if (ok)
				cout << "Not found" << endl;
			break;
		case 10:
			cout << "Enter node id: ";
			cin >> id;
			cout << nodes[id]->in.size() << endl;
			break;
		case 11:
			cout << "Enter node id: ";
			cin >> id;
			cout << nodes[id]->out.size() << endl;
			break;
		case 12:
			cout << "Enter node id: ";
			cin >> id;
			nodes.push_back(new node(nodes.size()));
			nodes[nodes.size() - 1]->id = id;
			break;
		case 13:
			cout << "Enter from and to: ";
			cin >> from >> to;
			for (int i=0;i<nodes[to]->in.size();)
			edges.push_back(edge());
			edges[edges.size() - 1].from = nodes[from];
			edges[edges.size() - 1].to = nodes[to];
			nodes[from]->out.push_back(nodes[to]);
			nodes[to]->in.push_back(nodes[from]);
			break;
		case 14:
			cout << "Enter node id: ";
			cin >> id;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == id || edges[i].to->id == id) {
					edges.erase(edges.begin() + i);
					i--;
				}
			}
			for (int i = 0; i < nodes.size(); i++) {
				for (int j = 0; j < nodes[i]->in.size(); j++) {
					if (nodes[i]->in[j]->id == id) {
						nodes[i]->in.erase(nodes[i]->in.begin() + j);
						j--;
					}
				}
				for (int j = 0; j < nodes[i]->out.size(); j++) {
					if (nodes[i]->out[j]->id == id) {
						nodes[i]->out.erase(nodes[i]->out.begin() + j);
						j--;
					}
				}
			}
			nodes.erase(nodes.begin() + id);
			for (int i = 0; i < nodes.size(); i++) {
				nodes[i]->id = i;
			}
			break;
		case 15:
			cout << "Enter from and to: ";
			cin >> from >> to;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == from && edges[i].to->id == to) {
					edges.erase(edges.begin() + i);
					break;
				}
			}
			for (int i = 0; i < nodes[from]->out.size(); i++) {
				if (nodes[from]->out[i]->id == to) {
					nodes[from]->out.erase(nodes[from]->out.begin() + i);
					break;
				}
			}
			for (int i = 0; i < nodes[to]->in.size(); i++) {
				if (nodes[to]->in[i]->id == from) {
					nodes[to]->in.erase(nodes[to]->in.begin() + i);
					break;
				}
			}
			break;
		case 16:
			oldEdges=edges;
			oldNodes=nodes;
			break;
		case 17:
			edges=oldEdges;
			nodes=oldNodes;
			break;
		case 0:
			return 0;
		}
	}
	return 0;
}