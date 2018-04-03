#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Node {
	int index;
	vector<Node*>following;

	Node(int index, int size) {
		this->index = index;
		following.resize(size);
		for (int i = 0; i<size; i++)
			following[i] = nullptr;
	}
	~Node() {
		for (int i = 0; i<following.size(); i++)
			if (following[i] != nullptr)
				delete following[i];
	}
};
class Graph {
private:
	Node * graph;
	int size;
	bool *visited;
public:
	Graph(int size) {
		graph = new Node(0, size);
		graph->following[0] = graph;
		this->size = size;
		visited = new bool[size];
	}
	~Graph() {
		delete graph;
		delete[] visited;
	}
	bool push(int from, int to) {
		if ((from >= size || to >= size) || (from<0 || to<0))
			return false;
		if (from == 0 || to == 0) {
			if (from == 0)
				if (graph->following[to] == nullptr) {
					graph->following[to] = new Node(to, size);
					graph->following[to]->following[0] = graph;
					return true;
				}
				else {
					if (graph->following[from] == nullptr) {
						graph->following[from] = new Node(from, size);
						graph->following[from]->following[to] = graph;
						return true;
					}
					else {
						graph->following[from]->following[to] = graph;
						return true;
					}
				}
		}
		if (graph->following[from] == nullptr)
			graph->following[from] = new Node(from, size);

		graph->following[from]->following[to] = (graph->following[to] == nullptr ? graph->following[to] = new Node(to, size) : graph->following[to]);
		graph->following[to]->following[to] = graph->following[to];
		return true;
	}
	void DFS() {
		stack<Node*> stk;
		for (int i = 0; i<size; i++)
			visited[i] = false;
		stk.push(graph);
		cout << graph->index << " ";
		visited[graph->index] = true;
		while (stk.size()) {
			for (int i = 0; i<size; i++) {
				if(stk.top()->following[i]!=nullptr){
					if (visited[stk.top()->following[i]->index] == false) {
						cout << stk.top()->following[i]->index << " ";
						visited[stk.top()->following[i]->index] = true;
					}
				}
			}
			stk.pop();
		}

	}
};
int main() {
	Graph *grph = new Graph(5);
	grph->push(0, 1);
	grph->push(3, 4);
	grph->DFS();
}