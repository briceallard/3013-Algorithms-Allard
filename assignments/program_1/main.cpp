/* 
Brice Allard
01/23/2018
Program 1
OrderedSert
*/

#include <iostream>
#include <ctime>

using namespace std;

//Create a container for our list data
struct node {
	int data;
	node* next;
};

/**
* Class: intLinkedList
* Purpose:
*     Implements a singly linked list that holds integers.
* Methods:
*     void  frontSert(int x)
*     node* find(int key)
*     node* remove(int key)
*     void  print()
*/
class intLinkedList {
private:
	node * Head;
public:
	intLinkedList() {
		Head = NULL;
	}
	void frontSert(int x) {
		//empty list case
		if (!Head) {
			Head = new node;
			Head->data = x;
			Head->next = NULL;
		}
		else {//not empty list
			node* T = new node;
			T->data = x;
			T->next = Head;
			Head = T;
		}
	}

	void orderedSert(int x) {
		if (!Head)
			frontSert(x);
		else {
			node* prev = Head;
			node* temp = new node;
			temp->data = x;

			if (prev->data > temp->data)
			{
				temp->next = prev;
				Head = temp;
			}
			else
			{
				while (prev->next != NULL && prev->next->data < temp->data)
				{
					prev = prev->next;
				}
				temp->next = prev->next;
				prev->next = temp;
			}
		}
	}

	node* Find(int key) {
		node* temp = Head;
		while (temp) {
			if (temp->data == key) {
				return temp;
			}
			temp = temp->next;
		}
		return NULL;
	}

	void Remove(int key) {
		node* result = Find(key);
		if (result) {
			node* temp = Head;
			while (temp->next != result) {
				temp = temp->next;
			}
			temp->next = result->next;
			delete result;
		}
	}

	void print() {
		node* p = Head;
		while (p) {
			cout << p->data << endl;
			p = p->next;
		}
	}
};

int main() {
	// seed random number generator
	srand(8734587);

	// ummmm
	//cout << "Hello World!\n";

	// declare instance of intLinkedList turning
	// a class definition into an "object"
	intLinkedList mylist;

	//Load 10 random ints into our list
	for (int i = 0; i<10; i++) {
		mylist.orderedSert(rand() % 100);
	}

	//print the list
	mylist.print();

	//find some value
	//cout << mylist.Find(99) << endl;

	//remove some value 
	//mylist.Remove(58);

	//print the list again
	//mylist.print();

	system("pause");
}
