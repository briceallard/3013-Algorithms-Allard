#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "BSTree.h"

//http://www.webgraphviz.com/

using namespace std;

int BSTree::count(BSTnode *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		return 1 + count(root->left) + count(root->right);
	}
}

void BSTree::insert(BSTnode *&root, BSTnode *&temp)
{
	if (!root)
	{
		root = temp;
	}
	else
	{
		if (temp->data < root->data)
		{
			insert(root->left, temp);
		}
		else
		{
			insert(root->right, temp);
		}
	}
}

void BSTree::print_BSTnode(BSTnode *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->data << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->data << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

/**
* type = ['predecessor','successor']
*/
BSTnode *BSTree::minValueNode(BSTnode *root)
{
	BSTnode *current = root;

	if (!root) {
		return 0;
	}
	if (root->right)
	{
		current = root->right;
		while (current->left != NULL)
		{
			current = current->left;
		}
	}
	else if (root->left)
	{
		current = root->left;
		while (current->right != NULL)
		{
			current = current->right;
		}
	}

	return current;
}

//************************************************************************
// Method Name: searchNode
//
// Public 
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: integer to look for
//
// Returns: true if found, false otherwise 
//*************************************************************************
bool BSTree::search(string word) {
	BSTnode *BSTnodePtr = root;

	while (BSTnodePtr) {
		if (BSTnodePtr->data == word) {
			if (BSTnodePtr->type == "adj")
				count_adj++;
			else if (BSTnodePtr->type == "adv")
				count_adv++;
			else if (BSTnodePtr->type == "ani")
				count_ani++;
			else if (BSTnodePtr->type == "nouns")
				count_nouns++;
			else if (BSTnodePtr->type == "verbs")
				count_verbs++;
			return true;
		}
		else if (word < BSTnodePtr->data) {
			comparison++;
			BSTnodePtr = BSTnodePtr->left;
		}
		else {
			comparison++;
			BSTnodePtr = BSTnodePtr->right;
		}
	}
	return false;
}

BSTnode *BSTree::deleteNode(BSTnode *&root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->data)
	{
		cout << "going left" << endl;
		root->left = deleteNode(root->left, key);
	}
	else if (key > root->data)
	{
		cout << "going right" << endl;
		root->right = deleteNode(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			BSTnode *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			BSTnode *temp = root->left;
			delete root;
			return temp;
		}

		// BSTnode with two children: Get the inorder successor (smallest
		// in the right subtree)
		BSTnode *temp = minValueNode(root);

		print_BSTnode(temp, "minvalueBSTnode");

		// Copy the inorder successor's content to this BSTnode
		root->data = temp->data;

		// Delete the inorder successor
		root->right = deleteNode(root->right, temp->data);
	}
	return root;
}

int BSTree::height(BSTnode *root)
{
	if (!root)
	{
		return 0;
	}
	else
	{
		int left = height(root->left);
		int right = height(root->right);
		if (left > right)
		{
			return left + 1;
		}
		else
		{
			return right + 1;
		}
	}
}

/* Print BSTnodes at a given level */
void BSTree::printGivenLevel(BSTnode *root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
	{
		print_BSTnode(root);
	}
	else if (level > 1)
	{
		printGivenLevel(root->left, level - 1);
		printGivenLevel(root->right, level - 1);
	}
}
//************************************************************************
// Method to help create GraphViz code so the expression tree can
// be visualized. This method prints out all the unique BSTnode id's
// by traversing the tree.
// Recivies a BSTnode pointer to root and performs a simple recursive
// tree traversal.
//************************************************************************
void BSTree::GraphVizGetIds(BSTnode *BSTnodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (BSTnodePtr)
	{
		GraphVizGetIds(BSTnodePtr->left, VizOut);
		VizOut << "BSTnode" << BSTnodePtr->data
			<< "[label=\"" << BSTnodePtr->data << "\\n"
			//<<"Add:"<<BSTnodePtr<<"\\n"
			//<<"Par:"<<BSTnodePtr->parent<<"\\n"
			//<<"Rt:"<<BSTnodePtr->right<<"\\n"
			//<<"Lt:"<<BSTnodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!BSTnodePtr->left)
		{
			NullCount++;
			VizOut << "nBSTnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		GraphVizGetIds(BSTnodePtr->right, VizOut);
		if (!BSTnodePtr->right)
		{
			NullCount++;
			VizOut << "nBSTnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
	}
}

//************************************************************************
// This method is partnered with the above method, but on this pass it
// writes out the actual data from each BSTnode.
// Don't worry about what this method and the above method do, just
// use the output as your told:)
//************************************************************************
void BSTree::GraphVizMakeConnections(BSTnode *BSTnodePtr, ofstream &VizOut)
{
	static int NullCount = 0;
	if (BSTnodePtr)
	{
		GraphVizMakeConnections(BSTnodePtr->left, VizOut);
		if (BSTnodePtr->left)
			VizOut << "BSTnode" << BSTnodePtr->data << "->"
			<< "BSTnode" << BSTnodePtr->left->data << endl;
		else
		{
			NullCount++;
			VizOut << "BSTnode" << BSTnodePtr->data << "->"
				<< "nBSTnode" << NullCount << endl;
		}

		if (BSTnodePtr->right)
			VizOut << "BSTnode" << BSTnodePtr->data << "->"
			<< "BSTnode" << BSTnodePtr->right->data << endl;
		else
		{
			NullCount++;
			VizOut << "BSTnode" << BSTnodePtr->data << "->"
				<< "nBSTnode" << NullCount << endl;
		}

		GraphVizMakeConnections(BSTnodePtr->right, VizOut);
	}
}

BSTree::BSTree()
{
	root = NULL;
}
BSTree::~BSTree()
{
}

int BSTree::count()
{
	return count(root);
}

//************************************************************************
// Function Name:	getComparison
// Parameter:		None
// Returns:			int comparison
// Description:
//		returns the number of comparisons made while searching in the BST
//************************************************************************
int BSTree::getComparison() {
	return comparison;
}

//************************************************************************
// Function Name:	getAdjCount
// Parameter:		None
// Returns:			int count_adj
// Description:
//		returns the number of adjectives searched in the BST
//************************************************************************
int BSTree::getAdjCount() {
	return count_adj;
}

//************************************************************************
// Function Name:	getAdvCount
// Parameter:		None
// Returns:			int count_adv
// Description:
//		returns the number of adverbs searched in the BST
//************************************************************************
int BSTree::getAdvCount() {
	return count_adv;
}

//************************************************************************
// Function Name:	getAniCount
// Parameter:		None
// Returns:			int count_ani
// Description:
//		returns the number of animals searched in the BST
//************************************************************************
int BSTree::getAniCount() {
	return count_ani;
}

//************************************************************************
// Function Name:	getNounsCount
// Parameter:		None
// Returns:			int count_nouns
// Description:
//		returns the number of nouns searched in the BST
//************************************************************************
int BSTree::getNounsCount() {
	return count_nouns;
}

//************************************************************************
// Function Name:	getVerbsCount
// Parameter:		None
// Returns:			int count_verbs
// Description:
//		returns the number of Verbs searched in the BST
//************************************************************************
int BSTree::getVerbsCount() {
	return count_verbs;
}

void BSTree::insert(string x, string t)
{
	BSTnode *temp = new BSTnode(x, t);
	insert(root, temp);
}

void BSTree::deleteNode(string key)
{
	deleteNode(root, key);
}

void BSTree::minValue()
{
	print_BSTnode(minValueNode(root), "minVal");
}

int BSTree::height(string key = "")
{
	if (key != "")
	{
		//find BSTnode
	}
	else
	{
		return height(root);
	}
	return 0;
}

string BSTree::top()
{
	if (root)
		return root->data;
	else
		return 0;
}

/* Function to line by line print level order traversal a tree*/
void BSTree::printLevelOrder()
{
	cout << "Begin Level Order===================\n";
	int h = height(root);
	int i;
	for (i = 1; i <= h; i++)
	{
		printGivenLevel(root, i);
		cout << "\n";
	}
	cout << "End Level Order===================\n";
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void BSTree::graphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	VizOut << "Digraph G {\n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "}\n";
	VizOut.close();
}