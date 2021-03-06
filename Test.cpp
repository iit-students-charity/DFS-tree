#include "stdafx.h"
#include "GraphHeader.h"
#include <stdio.h>
#include <conio.h>


int main(void)
{
	bool exit = false, optionError = false, treeError = false;
	int option;
	unsigned int node, nodeA, nodeB, root;
	graph drakula;

	while (!exit)
	{
		system("cls");
		printf("Options:\n1 - Add node\n2 - Delete node\n3 - Add edge\n4 - Delte edge\n5 - Built tree\n0 - Exit\n");
		printf("\nAdjacency list of the graph, include %d nodes:\n", drakula.getSize());
		drakula.printList();
		if (!optionError)
			printf("\nInput option: ");
		else
		{
			printf("Incorrect option, try again: ");
			optionError = false;
		}
		scanf_s("%d", &option);
		switch (option)
		{
			case 1:
			{
				if (drakula.addNode())
				{
					printf("\nError! Press any key...");
					_getch();
				}
				break;
			}
			case 2:
			{
				printf("\nInput number of node to delete: ");
				scanf_s("%d", &node);
				if (drakula.deleteNode(node))
				{
					printf("\nError! Press any key...");
					_getch();
				}
				break;
			}
			case 3:
			{
				printf("\nInput the nodes to add the edge between them: ");
				scanf_s("%d %d", &nodeA, &nodeB);
				if (drakula.addEdge(nodeA, nodeB))
				{
					printf("\nError! Press any key...");
					_getch();
				}
				break;
			}
			case 4:
			{
				printf("\nInput the nodes between which you want to delete the edge: ");
				scanf_s("%d %d", &nodeA, &nodeB);
				if (drakula.deleteEdge(nodeA, nodeB))
				{
					printf("\nError! Press any key...");
					_getch();
				}
				break;
			}
			case 5:
			{
				treeError = false;
				printf("Input the root of the tree: ");
				scanf_s("%d", &root);
				if (drakula.DFSTree(root))
				{
					printf("\nError! Press any key...");
					treeError = true;
					_getch();
				}
				if (!treeError)
				{
					printf("\nForest list with %d roots:\n", drakula.getRootSize());
					drakula.printTree();
					printf("\nPress any key...");
					_getch();
				}
				break;
			}
			case 0:
			{
				exit = true;
				break;
			}
			default:
			{
				optionError = true;
				break;
			}
		}
	}

	return 0;
}