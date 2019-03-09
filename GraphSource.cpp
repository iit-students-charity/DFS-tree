#include "stdafx.h"
#include "GraphHeader.h"

using namespace std;


int graph::getSize(void)
{
	return list.size();
}

int graph::getSize(unsigned int node)
{
	if (node > list.size())
		return 0;
	else
		return list[node - 1].size();
}

vector<vector<unsigned int>> graph::getList(void)
{
	return list;
}

vector<vector<unsigned int>> graph::getTree(void)
{
	return tree;
}

vector<bool> graph::getUsed(void)
{
	return used;
}

vector<unsigned int> graph::getRoot(void)
{
	return root;
}

int graph::getRootSize(void)
{
	return root.size();
}

int graph::addNode(void)	
{
	if (list.size() >= list.max_size())
		return 1;

	list.resize(list.size() + 1);	
	list[list.size() - 1].reserve(EDGES);

	return 0;
}

int graph::deleteNode(unsigned int node)
{
	if (node > list.size() || node == 0)
		return 1;

	list.erase(list.begin() + node - 1);

	for (unsigned int i = 0; i < list.size(); i++)
		for (unsigned int j = 0; j < list[i].size(); j++)
			if (list[i][j] == node)
				list[i].erase(list[i].begin() + j);
	for (unsigned int i = 0; i < list.size(); i++)
		for (unsigned int j = 0; j < list[i].size(); j++)
			if (list[i][j] > node)
				list[i][j]--;

	return 0;
}

int graph::addEdge(unsigned int nodeA, unsigned int nodeB)
{
	if (nodeA > list.size() || nodeB > list.size() || nodeA == 0 || nodeB == 0)
		return 1;
	for (unsigned int i = 0; i < list[nodeA - 1].size(); i++)
		if (list[nodeA - 1][i] == nodeB)
			return 1;
	for (unsigned int i = 0; i < list[nodeB - 1].size(); i++)
		if (list[nodeB - 1][i] == nodeA)
			return 1;

	list[nodeA-1].push_back(nodeB);
	if (nodeA != nodeB)
		list[nodeB-1].push_back(nodeA);

	sort(nodeA);											//
	sort(nodeB);											//

	return 0;
}

int graph::deleteEdge(unsigned int nodeA, unsigned int nodeB)
{
	bool existMarkerA = false, existMarkerB = false;
	unsigned int posInA, posInB;

	if (nodeA > list.size() || nodeB > list.size() || nodeA == 0 || nodeB == 0)
		return 1;
	for (unsigned int i = 0; i < list[nodeA - 1].size(); i++)
		if (list[nodeA - 1][i] == nodeB)
		{
			existMarkerA = true;
			posInA = i;
			break;
		}
	for (unsigned int i = 0; i < list[nodeB - 1].size(); i++)
		if (list[nodeB - 1][i] == nodeA )
		{
			existMarkerB = true;
			posInB = i;
			break;
		}
	if (!existMarkerA || !existMarkerB)
		return 1;

	list[nodeA - 1].erase(list[nodeA - 1].begin() + posInA);
	if (nodeA != nodeB)
		list[nodeB - 1].erase(list[nodeB - 1].begin() + posInB);

	return 0;
}

int graph::DFSTree(unsigned int root)
{
	if (root > list.size() || root == 0)
		return 1;

	this->root.clear();
	this->root.reserve(ROOTS);
	this->root.push_back(root - 1);
	tree.clear();
	tree.reserve(list.size());
	tree.resize(list.size());
	for (unsigned int i = 0; i < tree.size(); i++)
		tree[i].reserve(EDGES);
	used.clear();
	used.reserve(list.size());
	used.resize(list.size());
	fill(used.begin(), used.end(), false);

	DFS(root - 1);
	for (unsigned int i = 0; i < used.size(); i++)			//
		if (!used[i])										//
		{													//
			this->root.push_back(i);						//
			DFS(i);											//
		}													//
	return 0;
}

void graph::DFS(unsigned int node)
{
	used[node] = true;
	for (unsigned int i = 0; i < list[node].size(); i++)
		if (!(used[list[node][i]-1]))
		{
			tree[node].push_back(list[node][i]);
			DFS(list[node][i] - 1);
		}
	
	return;
}

void graph::printList(void)
{
	for (unsigned int i = 0; i < list.size(); i++)
	{
		printf("%d:", i + 1);
		for (unsigned int j = 0; j < list[i].size(); j++)
			printf(" %d", list[i][j]);
		printf("\n");
	}

	return;
}

void graph::printTree(void)
{
	bool rootMarker;

	for (unsigned int i = 0; i < tree.size(); i++)
	{
		rootMarker = false;
		for (unsigned int j = 0; j < root.size(); j++)
			if (root[j] == i)
			{
				printf("%d:(root)", i + 1);
				rootMarker = true;
				break;
			}
		if (!rootMarker)
			printf("%d:      ", i + 1);
		for (unsigned int j = 0; j < tree[i].size(); j++)
		{
			printf(" %d", tree[i][j]);
		}
		printf("\n");
	}

	return;
}

void graph::sort(unsigned int node)
{
	for (unsigned int i = 0; i < list[node - 1].size() - 1; i++)
		for (unsigned int j = 0; j < list[node - 1].size() - i - 1; j++)
			if (list[node - 1][j + 1] < list[node - 1][j])
				swap(list[node - 1][j], list[node - 1][j + 1]);

	return;
}