/*  
 *  An implementation of a linked list data structure written by Nathan Burrell.  
 *  An exercise to re-familiarize myself with C++ and pointer operations, while providing a
 *  relatively robust and generic data structure;
 */ 

#include "LList.h"
#include <iostream>
#include <string>

using namespace std;

LList<T>::add(Node<T>* n) {
	if (length == 0) {
		head = n;
		tail = n;
		length++;
		return;
	}
	else {
		tail->next = n;
		n->prev = tail;
		tail = n;
		length++;
		return;
	}
}

LList<T>::addFront(Node<T>* n) {
	if (length == 0) {
		head = n;
		tail = n;
		length++;
		return;
	}
	else {
		head->prev = n;
		n->next = head;
		head = n;
		length++;
		return;
	}
}

// Returns the contents of the i'th node
T LList<T>::get(int pos) {
	if ((pos > length-1) || (pos < 0)) {
		cout << "Invalid position passed to LList::get";
		return NULL;
	}
	Node* n = head;
	for (int i=0; i<pos; ++i) {
		n = n->next;
	}
	return n->value;
}

// Find and return the position of an item in the list
// Returns -1 if no item found
int LList<T>::find(T item) {
	Node* n = head;
	int pos = 0;
	(n->value == item) ? return pos;
	}
	for (int i=0; i<length; ++i) {
		Node* nx = n->next;
		pos++;
		(nx->value == item) ? return pos;
	}
	return -1;
}

// Find and remove the first occurrence of item
// returns -1 if item is not found, the position of the item in the list if found
int LList<T>::findRemove(T item) {
	Node* n = head;
	int pos = 0;
	if (n->value == item) {
		head = n->next;
		head->prev = NULL;
		length--;
		return pos;
	}
	for (int i=0; i<this.length; ++i) {
		Node* nx = n->next;
		pos++;
		if (nx->value == item) {
			Node* temp = nx->next;
			n->next = temp;
			temp->prev = n;
			length--;
			return pos;
		}
		n = nx;

	}
	return -1;
}

// Find and remove all occurrences of item
// Returns the number of items removed
int LList<T>::findRemoveAll(T item) {
	Node* n = head;
	int found = 0;
	if (n->value == item) {
		head = head->next;
		head->prev = NULL;
		length--;
		found++;
	}
	for (int i=0; i<length; ++i) {
		Node* nx = n->next;
		if (nx->value == item) {
			Node* temp = nx->next;
			n->next = temp;
			temp->prev = n;
			length--;
			found++;
		}
		n = nx;
	}
	return found;
}
/*
// Return a string representation of the list's elements
// Requires all elements of the list to have their own string representation.
std::ostream& operator<< (std::ostream& os, LList const& l);
	ostringstream listStrStrm;
	for( node<T> n = head; n != NULL; n=n.next) {
		listStrStrm << n.value << " ";
	}
	listStrStrm << "\n";
	return listStrStrm.str();
}
*/
