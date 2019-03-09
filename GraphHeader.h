#pragma once

#include <vector>

#define NODES 15
#define EDGES 5
#define ROOTS 3

using namespace std;


class graph
{
public:
	graph()
	{
		list.reserve(NODES);
		list.resize(0);
		used.resize(0);
		root.resize(0);
		tree.resize(0);
	}
	~graph()
	{
		list.clear();
		tree.clear();
		used.clear();
		root.clear();
	}
	int getSize(void);
	int getSize(unsigned int node);
	int getRootSize(void);
	vector<vector<unsigned int>> getList(void);
	vector<vector<unsigned int>> getTree(void);
	vector<bool> getUsed(void);
	vector<unsigned int> getRoot(void);

	int addNode(void);
	int deleteNode(unsigned int node);
	int addEdge(unsigned int nodeA, unsigned int nodeB);
	int deleteEdge(unsigned int nodeA, unsigned int nodeB);
	int DFSTree(unsigned int root);

	void printList(void);
	void printTree(void);
private:
	vector<vector<unsigned int>> tree;
	vector<bool> used;
	vector<unsigned int> root;
	void DFS(unsigned int node);

	vector<vector<unsigned int>> list;
	void sort(unsigned int node);
};