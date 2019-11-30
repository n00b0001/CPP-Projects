// LList Tester

#include "LList.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

/*  
 *  Populates a list of lists (inner lists of type <int>) from input. Input
 *  must be formatted as follows: a list of integers seperated by spaces and
 *  delimited by newlines. A single newline character ends input.
 *  WARNING: return value may be an empty list.
 */ 
LList<LList<int>> createTestLists (istream &in)
{
	in.exceptions(istream::failbit|istream::eofbit);
	// List to populate
	LList<LList<int>> retList;
	
	// Read non-empty line read from input
	string lineString;
	try
	{
		while (getline(in, lineString))
		{
			// Check for empty line
			if (lineString.empty())
			{
				cout << "End of input detected, closing input.\n";
				break;
			}
			else
			{
				// Tokenize a line of input
				istringstream tokens(lineString);
				LList<int> line;
				string nStr;
				while(tokens >> nStr)
				{
					string::size_type sz;
					try
					{
						int n = stoi(nStr, &sz);
						cout << n << " ";
						line.pushBack(n);
					}
					catch (invalid_argument)
					{
						cout << "N/A ";
					}
				}
				retList.pushBack(line);
				cout << "\n";
			}
		}
	}
	catch (ios_base::failure)
	{
		// IO error
		if (in.bad()) cerr << "Input error!\n";
		// Unexpected eof (improper input format)
		else if (in.eof()) cerr << "ERROR: Unexpected end of file (no empty line)\n";
		else cerr << "ERROR: Format error\n\n";
	}
	
	return retList;
}

// Test generic LList by creating lists of integers and applying various tests on them.
// Test pointers and function overloads on generic (ie. templated) objects.
int main(int argc, char** argv) {
	bool isFileInput = false;
	LList<LList<int>> listOfLists;
	
/*	
	// Testing on single list read from cin.
	LList<int> oneList;
	cout << "Please enter a list of integers, seperated by spaces:  ";
	string line;
	getline(cin, line);
	istringstream iss(line);
	int n;
	while (iss >> n)
	{
		cout << n << "x";
		oneList.addBack(n);
		cout << oneList;
		cout << "Returned from addBack\n";
	}
	cout << "\nList created.\n";
	
	cout << oneList;
*/

	// Detect input file (must be last argument)
	if (argc > 1)
	{
		ifstream iFile;
		iFile.exceptions(ifstream::failbit);
		try
		{
			iFile.open(argv[argc - 1]);
			if (iFile.is_open()) isFileInput = true;
		} catch (ifstream::failure e)
		{
			cerr<< "Exception in fstream: " << e.what() << endl;
			cout << "No input file found, switching to user input.\n";
			cout << "Input list elements, seperated by spaces.\n";
			cout << "Enter each list on a seperate line.\n";
		}
		if (isFileInput)
		{
			cout << "Opening file: " << argv[argc - 1] << endl;
			listOfLists = createTestLists(iFile);
		}
		else
		{
			
			cout << "Input list elements, seperated by spaces.\n";
			cout << "Enter each list on a seperate line.\n";
			listOfLists = createTestLists(cin);
		}
		iFile.close();
	}
	else
	{
		cout << "Input list elements, seperated by spaces.\n";
		cout << "Enter each list on a seperate line.\n";
		listOfLists = createTestLists(cin);
	}

	// This is a pointer to the current node in listOfLists
	Node <LList<int>> *test;
	
	// Print List sizes to test read and store operations.
	cout << "Printing list lengths:\n";
	cout << "listOfLists size: " << listOfLists.getLength() << endl;
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		cout << testList.getLength() << endl;
	}
	// Print listOfLists recursively
	cout << "\nPrinting listOfLists: \n";
	cout << listOfLists << endl;
	
	// Whenever changes are made to lists, the 
	// Node<LList<int>>.value must be reassigned

	// Add values to lists
	int newHead = 5;
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		testList.pushFront(newHead);
		test->value = testList;
	}
	cout << "Pushed " << newHead << " to front of list\n";
	cout << listOfLists << endl;
	cout << "There are " << listOfLists.getLength() << " lists, of lengths:\n";
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		cout << testList.getLength() << endl;
	}
	
	// Search for and index values in lists
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		Node<int> *eighth = testList.get(7);
		int findIx = -1;
		Node<int> *posThree = testList.find(findIx, 3);
		if (eighth != nullptr)
			cout << "eighth element is " << eighth->value;
		else cout << "The list is less than eight nodes long";
		if (posThree != nullptr)
			cout << " and the position of 3 is " << findIx << endl;
		else cout << " and 3 was not found in the list.\n";
	}
	cout << listOfLists << endl;
	
	// Remove some values from lists
	test = listOfLists.head;
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		if (testList.findRemove(3))
			cout << "Removed 3\n";
		else cout << "3 not found\n";
		test->value = testList;
	}
	
	int removeVal = 5;
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		int result = testList.removeAll(removeVal);
		cout << "Result of removing all " << removeVal << "'s was " << result << endl;
		test->value = testList;
	}
	cout << listOfLists << endl;
	
	// Pop from head or tail
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		LList<int> testList = test->value;
		Node<int> *front = testList.popFront();
		Node<int> *back = testList.popBack();
		if (front != nullptr)
		{
			cout << "Popped " << front->value << " from head and "
				<< "popped " << back->value << " from tail.\n";
		}
		else cout << "Empty list\n";
		test->value = testList;
	}
	cout << listOfLists << endl;
	
	// Empty some lists
	cout << "Emptying all lists\n";	
	for (test = listOfLists.head; test != nullptr; test = test->next)
	{
		test->value.empty();
	}
	cout << listOfLists << endl;
	
	return 0;
}
