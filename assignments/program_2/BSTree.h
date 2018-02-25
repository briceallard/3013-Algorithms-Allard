//************************************************************************
// Brice Allard
// 2/13/2018
// Adv. Algorithms
// Dr. Griffin
//************************************************************************

#pragma once
#include <string>
#include <fstream>

using namespace std;

struct node
{
	int data;
	node *left;
	node *right;
	node()
	{
		data = -1;
		left = NULL;
		right = NULL;
	}
	node(int x)
	{
		data = x;
		left = NULL;
		right = NULL;
	}
};

class BSTree {
private:
	node *root;
	int count(node *root);
	void insert(node *&root, node *&temp);
	void print_node(node *, string);
	node *minValueNode(node *root);
	node *deleteNode(node *&root, int key);
	node *temp = minValueNode(root);
	int height(node *);
	void printGivenLevel(node *root, int level);
	void GraphVizGetIds(node *nodePtr, ofstream &VizOut);
	void GraphVizMakeConnections(node *nodePtr, ofstream &VizOut);

public:
	BSTree();
	~BSTree();

	int count();
	void insert(int x);
	void deleteNode(int key);
	void minValue();
	int height(int);
	int top();
	void printLevelOrder();
	void GraphVizOut(string filename);
};
