#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

struct AVLnode {
	string value;
	string type;
	AVLnode *left;
	AVLnode *right;
	AVLnode *parent;
	int avlValue;

	AVLnode()
	{
		value = "";
		type = "";
		left = right = parent = NULL;
		avlValue = 0;
	}
	AVLnode(string word, string s)
	{
		value = word;
		type = s;
		left = right = parent = NULL;
		avlValue = 0;
	}
};

class AVLTree {
private:
	AVLnode * root;
	bool rightHeavy(AVLnode *);
	bool leftHeavy(AVLnode *);
	void insert(AVLnode *&, AVLnode *&);
	void inorder(AVLnode *);
	void preorder(AVLnode *);
	void postorder(AVLnode *);
	AVLnode* remove(AVLnode*&, string);
	AVLnode* predSuccessor(AVLnode*);
	void printNode(AVLnode *, string);
	int  height(AVLnode *);
	void computeAvlValues(AVLnode *&);
	void rotateLeft(AVLnode *&);
	void rotateRight(AVLnode *&);
	int  avlValue(AVLnode *);

public:
	AVLTree();
	~AVLTree();
	void doDumpTree(AVLnode *);
	void dumpTree() {
		cout << "---------------------------------" << endl;
		cout << "Root:   " << root << "\n";
		doDumpTree(root);
	};
	void insert(string, string);
	int getComparison();
	int getAdjCount();
	int getAdvCount();
	int getAniCount();
	int getNounsCount();
	int getVerbsCount();
	void showInorder() { inorder(root); };
	void showPreorder() { preorder(root); };
	void showPostorder() { postorder(root); };
	bool search(string);
	void remove(string word) { root = remove(root, word); };
	int  treeHeight();
	void graphVizGetIds(AVLnode *, ofstream &);
	void graphVizMakeConnections(AVLnode *, ofstream &);
	void graphVizOut(string);

protected:
	int comparison;
	int count_adj;
	int count_adv;
	int count_ani;
	int count_nouns;
	int count_verbs;
};
