//****************************************************************************
// Program Name: Crazy Word Creator
// Files: AVLTree.cpp, AVLTree.h, BSTree.cpp, BSTree.h,
//		  generate_words.cpp, tenthousandwords.txt, analyze_trees.cpp,
//		  adjectives.txt, adverbs.txt, animals.txt, nouns.txt, verbs.txt
// Author: Brice Allard
// Email: briceallard@gmail.com
// Description:
// 	Part 1:
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

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef map<string, int> wordMap;
typedef map<string, wordMap>::iterator it;
typedef vector<string> vs;

void fillVector(vs&, string);
int generateRandom(vs&);
string getWord(vs&, vs&, vs&, vs&, vs&);
void getString(vs&, vs&, vs&, vs&, vs&);

int main() {
	vs adjectives;
	vs nouns;
	vs verbs;
	vs adverbs;
	vs animals;

	fillVector(adjectives, "word_files/adjectives.txt");
	fillVector(nouns, "word_files/nouns.txt");
	fillVector(verbs, "word_files/verbs.txt");
	fillVector(adverbs, "word_files/adverbs.txt");
	fillVector(animals, "word_files/animals.txt");

	getString(adjectives, nouns, verbs, adverbs, animals);

	system("PAUSE");
	return 0;
}

//************************************************************************
// Function Name:	fillVector
// Parameter:		vector<string>, string filename (for reading)
// Returns:			void
// Description:
//		Gathers and loads information read in from the input file 
//		(filename) into a vector.
//************************************************************************
void fillVector(vs& v, string filename) {
	ifstream infile;
	infile.open(filename);

	string line;

	if (!infile) {
		cout << "Error opening file" << '<' << filename << '>' << endl;
		exit(0);
	}
	
	while (!infile.eof()) {
		infile >> line;
		v.push_back(line);
	}
	
	infile.close();
}

//************************************************************************
// Function Name:	generateRandom
// Parameter:		vector<string>
// Returns:			int
// Description:
//		Generates a random number based on the size of the vector passed
//		in (remains within boundary limits of vector size)
//************************************************************************
int generateRandom(vs& v) {
	return rand() % v.size();
}

//************************************************************************
// Function Name:	getWord
// Parameter:		vector<string> x5
// Returns:			string
// Description:
//		Grabs random word from vector based on random generator
//		(Can consist of Adjectives, Nounds, Verbs, Adverbs, or Animals)
//		and builds a string combining 3-5 of the words generated
//************************************************************************
string getWord(vs& adj, vs& noun, vs& verb, vs& adv, vs& anim) {
	int random = rand() % 5 + 1;
	string word = "";

	switch (random)	{		
	// Adjective Adjective Animal
	case 1 :
		word += adj[generateRandom(adj)];
		word += " ";
		word += adj[generateRandom(adj)];
		word += " ";
		word += anim[generateRandom(anim)];
		return word;
		
	// Adjective Noun Verb Animal
	case 2:
		word += adj[generateRandom(adj)];
		word += " ";
		word += noun[generateRandom(noun)];
		word += " ";
		word += verb[generateRandom(verb)];
		word += "ing ";
		word += anim[generateRandom(anim)];
		return word;

	// Adverb Adjective Animal
	case 3:
		word += adv[generateRandom(adv)];
		word += " ";
		word += adj[generateRandom(adj)];
		word += " ";
		word += anim[generateRandom(anim)];
		return word;

	// Noun Verb Animal
	case 4:
		word += noun[generateRandom(noun)];
		word += " ";
		word += verb[generateRandom(verb)];
		word += "ing ";
		word += anim[generateRandom(anim)];
		return word;

	// Adverb Adjective Verb Animal
	case 5:
		word += adv[generateRandom(adv)];
		word += " ";
		word += adj[generateRandom(adj)];
		word += " ";
		word += verb[generateRandom(verb)];
		word += "ing ";
		word += anim[generateRandom(anim)];
		return word;

	// Doesn't properly generate random number
	default:
		cout << "Error determining which order to generate." << endl;
		return word;
	}
}

//************************************************************************
// Function Name:	getString
// Parameter:		vector<string> x5
// Returns:			void
// Description:
//		Outputs random strings generated from above function into
//		outfile. Each string is input and verified in a MAP to ensure
//		no duplicates.
//************************************************************************
void getString(vs& adj, vs& noun, vs& verb, vs& adv, vs& anim) {
	
	ofstream outfile;
	outfile.open("tenthousandwords.txt");

	wordMap wm;
	it iter;

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10000; i++) {
		string data = getWord(adj, noun, verb, adv, anim);

		if (wm.find(data) == wm.end()) {
			wm[data] = 1;
			outfile << data << endl;
		}
		else
			i--;
	}
}
