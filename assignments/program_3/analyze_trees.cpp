//****************************************************************************
// Program Name: Crazy Word Creator
// Files: AVLTree.cpp, AVLTree.h, BSTree.cpp, BSTree.h,
//		  generate_words.cpp, tenthousandwords.txt, analyze_trees.cpp,
//		  adjectives.txt, adverbs.txt, animals.txt, nouns.txt, verbs.txt
// Author: Brice Allard
// Email: briceallard@gmail.com
// Description:
//	Part 1:
//	- creates 10000 crazy words without duplicates
//	- each crazy words consist of 3-5 word parts
//	- each crazy words consist of adjectives, nouns, animals
//	- created words are stored in a file
//	Part 2:
//	- compare the performance of AVL Tree and Binary Search Tree
//	- adjectives, adverbs, animals, nouns, verbs are inserted
//	  then, read the word parts from the list of 10000 crazy words
//	- search for each word parts in both trees
//	  then count the number of comparisons made
//	  at the same time, identify the type of the word part
//	  then finally displays the summary
//****************************************************************************

#include "BSTree.h"
#include "AVLTree.h"
#include <chrono>

using namespace std;

void fillAVLTree(AVLTree&, BSTree&);
void _fillAVLTree(AVLTree&, string, string);
void _fillBSTree(BSTree&, string, string);
int getAVLComp(AVLTree&);
int getBSTComp(BSTree&);
void compareTree(AVLTree&, BSTree&, string);

int main(int argc, char **argv) {
	AVLTree A;
	BSTree B;

	if (argc < 2) {
		cout << "You must have input files.\n"
			<< "Usage: analyze.exe filename.txt\n";
		exit(0);
	}

	//comparison file
	string filename = argv[1];

	//start timer
	auto start = chrono::high_resolution_clock::now();

	fillAVLTree(A, B);
	A.graphVizOut("AVLTree_viz.txt");
	B.graphVizOut("BSTree_viz.txt");
	compareTree(A, B, filename);

	//end timer
	auto finish = chrono::high_resolution_clock::now();
	chrono::duration<double> elapsed = finish - start;

	//output runtime information
	cout << "Elapsed time: " << elapsed.count() << "s\n\n";

	system("PAUSE");
	return 0;
}

//************************************************************************
// Function Name:	fillAVLTree
// Parameter:		AVLTree&, BSTree&
// Returns:			void
// Description:
//		Compilation of all input files for calling _fillAVLTree 
//		& _fillBSTree with data to read in from input files
//************************************************************************
void fillAVLTree(AVLTree& A, BSTree& B) {
	cout << "AVL Tree -\n";
	_fillAVLTree(A, "word_files/adjectives.txt", "adj");
	_fillAVLTree(A, "word_files/adverbs.txt", "adv");
	_fillAVLTree(A, "word_files/animals.txt", "ani");
	_fillAVLTree(A, "word_files/nouns.txt", "nouns");
	_fillAVLTree(A, "word_files/verbs.txt", "verbs");

	cout << "BS Tree - \n";
	_fillBSTree(B, "word_files/adjectives.txt", "adj");
	_fillBSTree(B, "word_files/adverbs.txt", "adv");
	_fillBSTree(B, "word_files/animals.txt", "ani");
	_fillBSTree(B, "word_files/nouns.txt", "nouns");
	_fillBSTree(B, "word_files/verbs.txt", "verbs");
}

//************************************************************************
// Function Name:	_fillAVLTree
// Parameter:		AVLTree&, filename (for reading) & string type
// Returns:			void
// Description:
//		Fills AVL Tree with data read in from input files
//************************************************************************
void _fillAVLTree(AVLTree& A, string fn, string type) {
	ifstream infile;
	infile.open(fn);

	string data;
	int count = 0;
	
	if (!infile) {
		cout << "Error opening file." << endl;
		exit(0);
	}

	while(!infile.eof()) {
		infile >> data;
		A.insert(data, type);
		count++;
	}

	if (type == "adj")
		cout << "Adjectives loaded: " << count << endl;
	else if (type == "adv")
		cout << "Adverbs loaded: " << count << endl;
	else if (type == "ani")
		cout << "Animals loaded: " << count << endl;
	else if (type == "nouns")
		cout << "Nouns loaded: " << count << endl;
	else if (type == "verbs")
		cout << "Verbs loaded: " << count << endl;

	infile.close();
}

//************************************************************************
// Function Name:	_fillBSTree
// Parameter:		BSTree&, filename (for reading) & string type
// Returns:			void
// Description:
//		Fills BS Tree with data read in from input files
//************************************************************************
void _fillBSTree(BSTree& B, string filename, string type) {
	ifstream infile;
	infile.open(filename);

	string data;
	int count = 0;

	if (!infile) {
		cout << "Error opening file." << endl;
		exit(0);
	}

	while (!infile.eof()) {
		infile >> data;
		B.insert(data, type);
		count++;
	}

	if (type == "adj")
		cout << "Adjectives loaded: " << count << endl;
	else if (type == "adv")
		cout << "Adverbs loaded: " << count << endl;
	else if (type == "ani")
		cout << "Animals loaded: " << count << endl;
	else if (type == "nouns")
		cout << "Nouns loaded: " << count << endl;
	else if (type == "verbs")
		cout << "Verbs loaded: " << count << endl;

	infile.close();
}

//************************************************************************
// Function Name:	getAVLComp
// Parameter:		AVLTree&
// Returns:			int AVLComparison
// Description:
//		returns the number of comparisons made while searching in the AVL
//************************************************************************
int getAVLComp(AVLTree& A) {
	return A.getComparison();
}

//************************************************************************
// Function Name:	getBSComp
// Parameter:		BSTree&
// Returns:			int BSComparison
// Description:
//		returns the number of comparisons made while searching in the BST
//************************************************************************
int getBSTComp(BSTree& B) {
	return B.getComparison();
}

//************************************************************************
// Function Name:	compareTree
// Parameter:		AVLTree&, BSTree&, filename (for reading)
// Returns:			void
// Description:
//		Compares the amount of comparisons from each BST and AVL
//		in order to determine which is more efficient
//************************************************************************
void compareTree(AVLTree& A, BSTree& B, string filename) {
	ifstream infile;
	infile.open(filename);

	string key;
	int BSTComp = 0;
	int AVLComp = 0;

	if (!infile) {
		cout << "No file found to compare with." << endl;
		exit(0);
	}

	while (!infile.eof()) {
		infile >> key;
		A.search(key);
		B.search(key);
	}

	AVLComp += A.getComparison();
	BSTComp += B.getComparison();

	cout << "\nTotal Comparisons -"
		<< "\nBST Comparisons = " << BSTComp
		<< "\nAVL Comparisons = " << AVLComp 
		<< "\nNumber of Adjectives = " << B.getAdjCount()
		<< "\nNumber of Adverbs = " << B.getAdvCount()
		<< "\nNumber of Nounds = " << B.getNounsCount()
		<< "\nNumber of Verbs = " << B.getVerbsCount()
		<< "\n";
}
