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

struct BSTnode
{
	string data;
	string type;
	BSTnode *left;
	BSTnode *right;
	BSTnode()
	{
		data = "";
		type = "";
		left = NULL;
		right = NULL;
	}
	BSTnode(string w, string t)
	{
		data = w;
		type = t;
		left = NULL;
		right = NULL;
	}
};

class BSTree {
private:
	BSTnode * root;
	int count(BSTnode *root);
	void insert(BSTnode *&root, BSTnode *&temp);
	void print_BSTnode(BSTnode *, string);
	BSTnode *minValueNode(BSTnode *root);
	BSTnode *deleteNode(BSTnode *&root, string key);
	BSTnode *temp = minValueNode(root);
	int height(BSTnode *);
	void printGivenLevel(BSTnode *root, int level);
	void GraphVizGetIds(BSTnode *BSTnodePtr, ofstream &VizOut);
	void GraphVizMakeConnections(BSTnode *BSTnodePtr, ofstream &VizOut);

public:
	BSTree();
	~BSTree();

	int count();
	int getComparison();
	int getAdjCount();
	int getAdvCount();
	int getAniCount();
	int getNounsCount();
	int getVerbsCount();
	void insert(string x, string t);
	void deleteNode(string key);
	void minValue();
	int height(string);
	string top();
	void printLevelOrder();
	void graphVizOut(string filename);
	bool search(string);

protected:
	int comparison;
	int count_adj;
	int count_adv;
	int count_ani;
	int count_nouns;
	int count_verbs;
};