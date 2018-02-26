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

int generateRandom(vs& v) {
	return rand() % v.size();
}

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

void getString(vs& adj, vs& noun, vs& verb, vs& adv, vs& anim) {
	
	ofstream outfile;
	outfile.open("word_files/tenthousandwords.txt");

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