/*  
 *  A simple generic node data structure implemented by Nathan Burrell.
 *  Contains pointers to next and previous nodes for use in linked lists, stacks, queues, etc. 
 *  Pointers do not have to be initialized (ie. a prev pointer would not be used in a 
 *  stack or singly linked list)
 */

#include <iostream>

using namespace std;
 
template <typename T> struct Node;
template <typename T> ostream& operator<< (ostream&, const Node<T>&);

template <typename T>
struct Node {
	Node<T> *next, *prev;
	T value;
	Node (): next(nullptr), prev(nullptr) {}; // Avoid using blank constructor due to templating issues
	Node(T val) : value(val), next(nullptr), prev(nullptr) {};
	friend ostream& operator<< <>(ostream& , const Node<T>&);
};

template <typename T>
ostream& operator<< (ostream& out, const Node<T> &n) 
{
	out << n.value;
	return out;
}
