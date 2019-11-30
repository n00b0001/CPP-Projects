/*  
 *  Header file of a generic linked list data structure implemented by Nathan Burrell.
 *  An exercise in familiarizing myself with C++ and pointer operations.
 *  Templated header functions must be implemented inline.
 */ 
 
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Template class declaration
template <typename T> class LList;

// Overloaded Operators
template <typename T> ostream& operator<< (ostream&, const LList<T>&);
template <typename T> bool operator== (const LList<T>&, const LList<T>&);

template <class T> 
class LList
{
private:

	int length;

public:
	
	Node<T> *head, *tail;
	explicit LList(): length(0), head(nullptr), tail(nullptr) {};
	LList(Node<T> n) : length(1), head(&n), tail(&n) {};
	friend ostream& operator<< <>(ostream& , const LList<T>&);
	friend bool operator== <>(const LList<T>&, const LList<T>&);
	void pushBack(T n);
	void pushFront (T n);
	Node<T>* popBack();
	Node<T>* popFront();
	int getLength() const { return length; }
	Node<T>* get(int pos);
	Node<T>* find(int &ix, T item);
	int findRemove(T item);
	int removeAll(T item);
	void empty();
};


// Prepares a LList for an output stream. Requires all elements of nodes
// in the list to have their own overload of operator<<.
template <typename T>
ostream& operator<< (ostream& out, const LList<T> &l) 
{
	// If the size is zero, the list is empty
	if (l.getLength() == 0)
	{
		out << "Empty List\n";
		return out;
	}
	// Otherwise
	int ix = 0;
	for (Node<T> *temp = l.head; temp != nullptr; temp = temp->next)
	{
		out << temp->value;
		(temp->next) ? out << ", " : out << "\n";
	}
	return out;
}

// Compares two lists by comparing the contents and order of their nodes.
// WARNING: If node.value is a pointer type, this will compare pointer addresses.
template <typename T>
bool operator== (const LList<T> &lhs, const LList<T> &rhs) 
{
	Node<T> *rtmp = rhs.head;
	Node<T> *ltmp = lhs.head;
	while (ltmp && rtmp) 
	{
		if (ltmp->value == rtmp->value) 
		{
			rtmp = rtmp->next;
			ltmp = ltmp->next;
		}
		else return false;
	}
	return true;
}

// Push methods add a new element to the list;
template <typename T>
void LList<T>::pushBack(T t) 
{
	Node<T> *n = new Node<T>(t);
	if (length == 0)
	{
		head = n;
	}
	if (length > 0)
	{
		tail->next = n;
		n->prev = tail;
	}
	tail = n;
	++length;
	return;
}

template <typename T>
void LList<T>::pushFront(T t) 
{
	Node<T> *n = new Node<T>(t);
	if (length == 0) 
		tail = n;
	if (length >= 1) 
	{
		n->next = head;
		n->next->prev = n;
	}
	head = n;
	++length;
	return;
}

// Pop methods remove an element from the front or back of the list
template <typename T>
Node<T>* LList<T>::popBack()
{
	if (length == 0) return nullptr;
	Node<T> *n = tail;
	tail = n->prev;
	tail->next = nullptr;
	--length;
	return n;
}

template <typename T>
Node<T>* LList<T>::popFront()
{
	if (length == 0) return nullptr;
	Node<T> *n = head;
	head = n->next;
	head->prev = nullptr;
	--length;
	return n;
}

// Returns the contents of the i'th node
// WARNING: calls to this function must contain checks for the nullptr
// return.
//
// TO DO: implement error handling and exception flags.
template <typename T>
Node<T>* LList<T>::get(int ix) 
{
	if ((ix >= length) || (ix < 0)) 
	{
		return nullptr;
	}
	Node<T> *n = head;
	for (int i = 0; i < ix; ++i) n = n->next;
	return n;
}

// NB: ALL OF THE FIND METHODS RELY ON THE USE OF OPERATOR== AND SHOULD
//     ONLY BE USED IF THE OPERATOR IS OVERLOADED FOR T

// Find and return the node containing an item in the list,
// as well as the index passed by reference.
// WARNING: Returns nullptr if no item found!!
template <typename T>
Node<T>* LList<T>::find(int &ix, T item) 
{
	Node<T> *n = head;
	
	for (ix = 0; ix < length; ++ix) 
	{
		if (n->value == item) return n;
		else n = n->next;
	}
	
	return nullptr;
}

// The remove functions make use of the C++ garbage collector to reclaim memory
// that is no longer used by the program.  Once a node can no longer be reached by
// traversing the list from the head or tail, it is flagged for reclamation.
// Therefore, the remove functions must ensure proper nullification or reassignment
// of pointers to removed nodes.

// Find and remove the FIRST occurrence of item (Uses find() to complete in O(n) time)
// returns if item is not found, as well as after successfully removing the item
template <typename T>
int LList<T>::findRemove(T item) 
{
	int findIndx = 0;
	Node<T> *n = this->find(findIndx, item);
	// if the item was not found, return 0
	if (n == nullptr) return 0;
	// the item was found, reassign some pointers to exclude n from list
	else
	{
		Node<T> *pv = n->prev;
		Node<T> *nx = n->next;
		pv->next = nx;
		nx->prev = pv;
		if (--length == 0)
		{
			head = nullptr;
			tail = nullptr;
		}
		return 1;
	}
}

// Find and remove all occurrences of item in O(n) time. (Does not use find() function)
// Returns the number of items removed (0 if none)
template <typename T>
int LList<T>::removeAll(T item) 
{
	Node<T> *n = head;
	int found = 0;
	
	// head->prev and tail->next must be NULL
	while (n != nullptr)
	{
		// Check to remove n'th node
		if (n->value == item) 
		{
			// Check for special cases first
			// n is only item in list (tail and head)
			if ((n->next == nullptr) && (n->prev == nullptr))
			{
				head = nullptr;
			}
			// n is head but not tail
			else if (n->prev == nullptr) 
			{
				head = n->next;
				head->prev = nullptr;
			}
			// n is tail but not head
			else if (n->next == nullptr) 
			{
				tail = n->prev;
			}
			// n has valid pointers to next and prev
			else
			{
				n->next->prev = n->prev;
				n->prev->next = n->next;
			}
			--length;
			++found;
		}
		//  This should be a nullptr if n->next is tail
		n = n->next;
	}
	// Empty list if head is null (removed all items)
	if (head == nullptr) tail == nullptr;
	return found;
}

// Empty a list
template <typename T>
void LList<T>::empty()
{
	head = nullptr;
	tail = nullptr;
	length = 0;
}
