#include<iostream>
#include<fstream>
#include<vector>
#include <windows.h>
#include <random>
#include <queue>
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
void reverseBFS(node* in, node *out) {
	struct qwerty {
		node* item=NULL;
		int distance=0;
	}crt;
	vector <int> previous(nodes.size(), -1);
	queue <qwerty>q;
	previous[out->id] = 0;
	q.push(qwerty{ out,0 });
	while (!q.empty()) {
		crt = q.front();
		if (crt.item == in) {
			cout <<"Lenght: "<< crt.distance << endl;
			while (crt.item != out) {
				cout << crt.item->id << "->";
				crt.item = nodes[previous[crt.item->id]];
			}
			cout << crt.item->id << endl;
			return;
		}
		q.pop();
		for (int i = 0; i < crt.item->in.size(); i++) {
			if (previous[crt.item->in[i]->id] == -1) {
				previous[crt.item->in[i]->id] = crt.item->id;
				q.push(qwerty{ crt.item->in[i],crt.distance + 1 });
			}
		}
	}
	cout << "No path" << endl;
}
void randomGraph() {
	int n, m;
	cin >> n >> m;
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
		cout << "16. Reverse BFS" << endl;
		cout << "0. Exit" << endl;
		int choice;
		cin >> choice;
		cout << endl;
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
			cin >> id;
			for (int i = 0; i < nodes[id]->in.size(); i++) {
				cout << nodes[id]->in[i]->id << " ";
			}
			cout << endl;
			break;
		case 7:
			cin >> id;
			for (int i = 0; i < nodes[id]->out.size(); i++) {
				cout << nodes[id]->out[i]->id << " ";
			}
			cout << endl;
			break;
		case 8:
			int from, to;
			cin >> from >> to;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == from && edges[i].to->id == to) {
					cout << edges[i].cost << endl;
					break;
				}
			}
			cout << "Not found" << endl;
			break;
		case 9:
			cin >> from >> to;
			int cost;
			cin >> cost;
			for (int i = 0; i < edges.size(); i++) {
				if (edges[i].from->id == from && edges[i].to->id == to) {
					edges[i].cost = cost;
					break;
				}
			}
			cout << "Not found" << endl;
			break;
		case 10:
			cin >> id;
			cout << nodes[id]->in.size() << endl;
			break;
		case 11:
			cin >> id;
			cout << nodes[id]->out.size() << endl;
			break;
		case 12:
			nodes.push_back(new node(nodes.size()));
			break;
		case 13:
			cin >> from >> to;
			edges.push_back(edge());
			edges[edges.size() - 1].from = nodes[from];
			edges[edges.size() - 1].to = nodes[to];
			nodes[from]->out.push_back(nodes[to]);
			nodes[to]->in.push_back(nodes[from]);
			break;
		case 14:
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

		case 0:
			return 0;
		case 16:
			int fr,t;
			cout << "Enter from:" << endl;
			cin >> fr;
			cout << "Enter to:" << endl;
			cin >> t;
			cout << endl;
			reverseBFS(nodes[fr], nodes[t]);
			break;
		}
	}
	return 0;
}