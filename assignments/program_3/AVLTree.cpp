#include <iostream>
#include <fstream>
#include <time.h>
#include "AVLTree.h"

//https://visualgo.net/en/bst

using namespace std;

AVLTree::AVLTree() {
	root = NULL;
}

AVLTree::~AVLTree() {

}

//************************************************************************
// Method Name: insert
//
// Private 
//
// Purpose: Inserts a AVLnode into a binary tree
//
// Arguments: reference to the root, and a reference to the new AVLnode
//
// Returns: Nothing.
//*************************************************************************
void AVLTree::insert(AVLnode *&AVLnodePtr, AVLnode *&newNode) {

	if (AVLnodePtr == NULL) {
		AVLnodePtr = newNode;
	}
	else if (newNode->value <= AVLnodePtr->value) {
		newNode->parent = AVLnodePtr;
		insert(AVLnodePtr->left, newNode);

	}
	else {
		newNode->parent = AVLnodePtr;
		insert(AVLnodePtr->right, newNode);
	}

}

//************************************************************************
// Method Name: insertNode
//
// Public 
//
// Purpose: Creates a new AVLnode and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the AVLnode in
//          proper location. 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AVLTree::insert(string word, string type) {
	AVLnode *newNode;

	newNode = new AVLnode(word, type);
	insert(root, newNode);
	computeAvlValues(root);
}

//************************************************************************
// Method Name: inorder,postorder,preorder (all the same)
//
// Public 
//
// Purpose: Traverses a binary tree 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AVLTree::inorder(AVLnode *AVLnodePtr) {
	if (AVLnodePtr) {
		inorder(AVLnodePtr->left);
		cout << AVLnodePtr->value << " " << "(" << AVLnodePtr->avlValue << ") ";
		inorder(AVLnodePtr->right);
	}
}

void AVLTree::postorder(AVLnode *AVLnodePtr) {
	if (AVLnodePtr) {
		inorder(AVLnodePtr->left);
		inorder(AVLnodePtr->right);
		cout << AVLnodePtr->value << " " << "(" << AVLnodePtr->avlValue << ") ";
	}
}

void AVLTree::preorder(AVLnode *AVLnodePtr) {
	if (AVLnodePtr) {
		cout << AVLnodePtr->value << " " << "(" << AVLnodePtr->avlValue << ") ";
		inorder(AVLnodePtr->left);
		inorder(AVLnodePtr->right);
	}
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
bool AVLTree::search(string word) {
	AVLnode *AVLnodePtr = root;

	while (AVLnodePtr) {
		if (AVLnodePtr->value == word) {
			if (AVLnodePtr->type == "adj")
				count_adj++;
			else if (AVLnodePtr->type == "adv")
				count_adv++;
			else if (AVLnodePtr->type == "ani")
				count_ani++;
			else if (AVLnodePtr->type == "nouns")
				count_nouns++;
			else if (AVLnodePtr->type == "verbs")
				count_verbs++;
			return true;
		}
		else if (word < AVLnodePtr->value) {
			comparison++;
			AVLnodePtr = AVLnodePtr->left;
		}
		else {
			comparison++;
			AVLnodePtr = AVLnodePtr->right;
		}
	}
	return false;
}


//************************************************************************
// Method Name: remove
//
// Private 
//
// Purpose: Actually removes a AVLnode from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of AVLnode to be deleted
//
// Returns: void 
//*************************************************************************

AVLnode* AVLTree::remove(AVLnode*& root, string key)
{
	if (!root)
	{
		return NULL;
	}
	if (key < root->value)
	{
		cout << "going left" << endl;
		root->left = remove(root->left, key);
	}
	else if (key > root->value)
	{
		cout << "going right" << endl;
		root->right = remove(root->right, key);
	}
	else
	{
		if (root->left == NULL)
		{
			AVLnode *temp = root->right;
			delete root;
			return temp;
		}
		else if (root->right == NULL)
		{
			AVLnode *temp = root->left;
			delete root;
			return temp;
		}

		// AVLnode with two children: Get the inorder successor (smallest
		// in the right subtree)
		AVLnode *temp = predSuccessor(root);

		printNode(temp, "predSuccessor");

		// Copy the inorder successor's content to this AVLnode
		root->value = temp->value;

		// Delete the inorder successor
		root->right = remove(root->right, temp->value);
	}
	return root;
}

void AVLTree::printNode(AVLnode *n, string label = "")
{
	if (label != "")
	{
		cout << "[" << label << "]";
	}
	cout << "[[" << n << "][" << n->value << "]]\n";
	if (n->left)
	{
		cout << "\t|-->[L][[" << n->left << "][" << n->left->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[L][null]\n";
	}
	if (n->right)
	{
		cout << "\t\\-->[R][[" << n->right << "][" << n->right->value << "]]\n";
	}
	else
	{
		cout << "\t\\-->[R][null]\n";
	}
}

AVLnode* AVLTree::predSuccessor(AVLnode *root)
{
	AVLnode *current = root;

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
// Method Name: height
//
// Private 
//
// Purpose: Actually removes a AVLnode from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of the root of the tree (or subtree)
//
// Returns: void 
//*************************************************************************
int AVLTree::height(AVLnode *AVLnodePtr) {
	int left_height = 0;
	int right_height = 0;
	if (AVLnodePtr == NULL)
		return 0;
	else {
		left_height = height(AVLnodePtr->left);
		right_height = height(AVLnodePtr->right);
	}
	if (left_height>right_height)
		return 1 + left_height;
	else
		return 1 + right_height;
}

//************************************************************************
// Method Name: treeHeight
//
// Public 
//
// Purpose: Public method to call the private height method
//
// Arguments: none
//
// Returns: void 
//*************************************************************************
int AVLTree::treeHeight() {
	return height(root);
}

//************************************************************************
// Function Name:	getComparison
// Parameter:		None
// Returns:			int comparison
// Description:
//		returns the number of comparisons made while searching in the AVL
//************************************************************************
int AVLTree::getComparison() {
	return comparison;
}

//************************************************************************
// Function Name:	getAdjCount
// Parameter:		None
// Returns:			int count_adj
// Description:
//		returns the number of adjectives searched in the AVL
//************************************************************************
int AVLTree::getAdjCount() {
	return count_adj;
}

//************************************************************************
// Function Name:	getAdvCount
// Parameter:		None
// Returns:			int count_adv
// Description:
//		returns the number of adverbs searched in the AVL
//************************************************************************
int AVLTree::getAdvCount() {
	return count_adv;
}

//************************************************************************
// Function Name:	getAniCount
// Parameter:		None
// Returns:			int count_ani
// Description:
//		returns the number of animals searched in the AVL
//************************************************************************
int AVLTree::getAniCount() {
	return count_ani;
}

//************************************************************************
// Function Name:	getNounsCount
// Parameter:		None
// Returns:			int count_nouns
// Description:
//		returns the number of nouns searched in the AVL
//************************************************************************
int AVLTree::getNounsCount() {
	return count_nouns;
}

//************************************************************************
// Function Name:	getVerbsCount
// Parameter:		None
// Returns:			int count_verbs
// Description:
//		returns the number of Verbs searched in the AVL
//************************************************************************
int AVLTree::getVerbsCount() {
	return count_verbs;
}

//************************************************************************
// Method Name: avlValue
//
// Private 
//
// Purpose: Private method to calculate the avl value of a AVLnode.
//
// Arguments: address of a AVLnode
//
// Returns: void 
//*************************************************************************
int AVLTree::avlValue(AVLnode *AVLnodePtr)
{
	return height(AVLnodePtr->right) - height(AVLnodePtr->left);
}

//************************************************************************
// Method Name: computeAvlValues
//
// Private 
//
// Purpose: Private method to calculate the avl values of the entire tree.
//
// Arguments: address of a AVLnode
//
// Returns: void 
//*************************************************************************
void AVLTree::computeAvlValues(AVLnode *&AVLnodePtr)
{
	if (AVLnodePtr) {
		computeAvlValues(AVLnodePtr->left);
		computeAvlValues(AVLnodePtr->right);
		AVLnodePtr->avlValue = avlValue(AVLnodePtr);
		if (AVLnodePtr->avlValue > 1) {
			rotateLeft(AVLnodePtr);
		}
		else if (AVLnodePtr->avlValue < -1) {
			rotateRight(AVLnodePtr);
		}
	}
}

//************************************************************************
// Method Name: rotateLeft 
//
// Private 
//
// Purpose: Private method to perform a left rotation from a given position in a tree
//
// Arguments: address of a AVLnode
//
// Returns: void 
//*************************************************************************
void AVLTree::rotateLeft(AVLnode *&SubRoot)
{


	if (leftHeavy(SubRoot->right)) {
		rotateRight(SubRoot->right);
	}

	AVLnode *Temp;

	Temp = SubRoot->right;
	SubRoot->right = Temp->left;
	Temp->left = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: rotateLeft 
//
// Private 
//
// Purpose: Private method to perform a right rotation from a given position in a tree
//
// Arguments: address of a AVLnode
//
// Returns: void 
//*************************************************************************
void AVLTree::rotateRight(AVLnode *&SubRoot)
{
	if (rightHeavy(SubRoot->left)) {
		rotateLeft(SubRoot->left);
	}

	AVLnode *Temp;

	Temp = SubRoot->left;
	SubRoot->left = Temp->right;
	Temp->right = SubRoot;
	SubRoot = Temp;

	computeAvlValues(SubRoot);
}

//************************************************************************
// Method to help create GraphViz code so the expression tree can 
// be visualized. This method prints out all the unique AVLnode id's
// by traversing the tree.
// Recivies a AVLnode pointer to root and performs a simple recursive 
// tree traversal.
//************************************************************************
void AVLTree::graphVizGetIds(AVLnode *AVLnodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (AVLnodePtr) {
		graphVizGetIds(AVLnodePtr->left, VizOut);
		VizOut << "AVLnode" << AVLnodePtr->value
			<< "[label=\"" << AVLnodePtr->value << "\\n"
			<< "Avl:" << AVLnodePtr->avlValue << "\\n"
			//<<"Add:"<<AVLnodePtr<<"\\n"
			//<<"Par:"<<AVLnodePtr->parent<<"\\n"
			//<<"Rt:"<<AVLnodePtr->right<<"\\n"
			//<<"Lt:"<<AVLnodePtr->left<<"\\n"
			<< "\"]" << endl;
		if (!AVLnodePtr->left) {
			NullCount++;
			VizOut << "nAVLnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;
		}
		graphVizGetIds(AVLnodePtr->right, VizOut);
		if (!AVLnodePtr->right) {
			NullCount++;
			VizOut << "nAVLnode" << NullCount << "[label=\"X\",shape=point,width=.15]" << endl;

		}
	}
}

//************************************************************************
// This method is partnered with the above method, but on this pass it 
// writes out the actual data from each AVLnode.
// Don't worry about what this method and the above method do, just
// use the output as your told:)
//************************************************************************
void AVLTree::graphVizMakeConnections(AVLnode *AVLnodePtr, ofstream &VizOut) {
	static int NullCount = 0;
	if (AVLnodePtr) {
		graphVizMakeConnections(AVLnodePtr->left, VizOut);
		if (AVLnodePtr->left)
			VizOut << "AVLnode" << AVLnodePtr->value << "->" << "AVLnode" << AVLnodePtr->left->value << endl;
		else {
			NullCount++;
			VizOut << "AVLnode" << AVLnodePtr->value << "->" << "nAVLnode" << NullCount << endl;
		}

		if (AVLnodePtr->right)
			VizOut << "AVLnode" << AVLnodePtr->value << "->" << "AVLnode" << AVLnodePtr->right->value << endl;
		else {
			NullCount++;
			VizOut << "AVLnode" << AVLnodePtr->value << "->" << "nAVLnode" << NullCount << endl;
		}

		graphVizMakeConnections(AVLnodePtr->right, VizOut);

	}
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void AVLTree::graphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	graphVizGetIds(root, VizOut);
	graphVizMakeConnections(root, VizOut);
	VizOut.close();

}

//************************************************************************
// Method Name: doDumpTree 
//
// Private 
//
// Purpose: Private method to show the basic pointer structure of the tree. 
//          Initially written to help with debugging.
//
// Arguments: address of a AVLnode
//
// Returns: void 
// Outputs: tree information
//*************************************************************************
void AVLTree::doDumpTree(AVLnode *AVLnodePtr)
{
	if (AVLnodePtr) {
		cout << "Add:    " << AVLnodePtr << "\n"
			<< "Parent->" << AVLnodePtr->parent << "\n"
			<< "Val:    " << AVLnodePtr->value << "\n"
			<< "Avl:    " << AVLnodePtr->avlValue << "\n"
			<< "Left->  " << AVLnodePtr->left << "\n"
			<< "Right-> " << AVLnodePtr->right << "\n\n";

		doDumpTree(AVLnodePtr->left);
		doDumpTree(AVLnodePtr->right);
	}
}

//************************************************************************
// Method Name: leftHeavy,rightHeavy 
//
// Private 
//
// Purpose: Compares the subtrees of a AVLnode to see which is taller
//
// Arguments: address of a AVLnode
//
// Returns: true if (left/right) heavy 
//
//*************************************************************************
bool AVLTree::leftHeavy(AVLnode *AVLnodePtr)
{
	return height(AVLnodePtr->left)>height(AVLnodePtr->right);
}

bool AVLTree::rightHeavy(AVLnode *AVLnodePtr)
{
	return height(AVLnodePtr->right)>height(AVLnodePtr->left);

}