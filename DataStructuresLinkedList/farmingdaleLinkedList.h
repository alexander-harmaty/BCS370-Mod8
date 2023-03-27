// (c) 2013-2020 David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// dynamic arrays, exceptions and operator overloading, and templates


// Class farmingdale::stack: General std::string stack implementation based on array. 
// We will add dynamic arrays (for unlimited size), templates (to allow multiple types) etc.

// note: This is not thread safe--there are no mutexes or locks on the indexes.

// like #pragma once but more portable
#ifndef H_FARMINGDALELINKEDLIST
#define H_FARMINGDALELINKEDLIST


// Note to students. It's OK to #include in a library header (inside the guards). 
// but DO NOT add a "using" directive inside a library header
#include <string>
#include <deque>
#include "farmingdaleStatus.h"

// See https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019
// for some notes on what we're doing here.
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// Two consts for student messages
const std::string TEMPLATED_HEADER_FILE = (std::string(__FILE__).substr(std::string(__FILE__).find_last_of("\\/") + 1));
const int TEMPLATED_HEADER_LINE = (__LINE__ + 3);
// Please set these before you start on the relevant project: 
// Uncomment this to test a templated version of the stack code.
#define TEMPLATED_LINKEDLIST

// another consts for student messages
const int TEMPLATED_HEADER_SECOND_SET_OF_LINKED_LIST_METHODS = (__LINE__ + 2);
// Uncomment this to enable the tests for the methods in Module 8 (the second set of tests)
#define SECOND_SET_OF_LINKED_LIST_METHODS

#ifndef TEMPLATED_LINKEDLIST
// This code section is for the initial [non-templated] version of the code.
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	struct llNode;
	class linkedList;
}


// a node of my ll
struct farmingdale::llNode {
	std::string data;
	llNode* next;
};

// Each method has a notation next to it indicating the Module in which you will program it.
// M7 = we will implement in Module 7, M8 = implement in Module 8
class farmingdale::linkedList {
private:
	llNode* head; // first node
	llNode* tail; // last node
public:
	linkedList(); // M7 // default ctor

	// Rule of threes
	linkedList(const linkedList&); // M8 // copy ctor
	~linkedList(); // M7 // dtor
	// not a reference paramter because we use copy/swap
	const linkedList& operator=(linkedList); //M8 // assignment operator

	// accessors
	inline bool isEmpty() const
	{
		//we can check either if head is 0, or if tail is 0
		return (0 == head);
	};// M7 // write inline

	statusCode getHead(std::string&) const; // M7
	statusCode getTail(std::string&) const; // M7
	bool operator==(const linkedList&) const; // M7 (I write in the videos) // base comparison operator
	bool operator==(const std::deque<std::string>&) const; //M7 (I write in the videos)
														   // print a linkedList to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream) const; // M7 (I write in the videos)
	llNode* search(std::string) const; // M8
	bool contains(std::string findMe) const; // M8 // write inline using search
	llNode* findAtPosition(int) const; // M8 // 0 = first item, 1 == second ....

	// mutators
	statusCode insertAtHead(std::string); // M7
	statusCode removeAtHead(std::string&); // M7
	statusCode insertAtTail(std::string); // M7
	statusCode insertAfter(llNode*, std::string); // M8
	statusCode removeAtTail(std::string&); // M8
	statusCode remove(llNode*); // M8  
	statusCode remove(std::string removeMe); // M8 // write inline



};
// Write the following here as outside inline functions: (all M7)
// operator!= linkedList,linkedList
inline bool operator!=(const farmingdale::linkedList& lhs, const farmingdale::linkedList& rhs) {
	return (!(rhs == lhs));
}
// operator!= linkedList,std::deque
inline bool operator!=(const farmingdale::linkedList& lhs, const std::deque<std::string>& rhs) {
	return (!(lhs == rhs));
}
// operator!= std::deque,linkedList
inline bool operator!=(const std::deque<std::string>& lhs, const farmingdale::linkedList& rhs) {
	return (!(rhs == lhs));
}
// operator== std::deque,linkedList
inline bool operator==(const std::deque<std::string>& lhs, const farmingdale::linkedList& rhs) {
	return (rhs == lhs);
}

inline std::ostream& operator<<(std::ostream& theStream, const farmingdale::linkedList& theLinkedList) {
	theLinkedList.printToStream(theStream);
	return theStream;
}

#else 
// This code section is for the initial [non-templated] version of the code.
namespace farmingdale {
	// Note: namespaces are additive, so you can add new elements to this namespace in other files or later
	template <class CL> struct llNode;
	template <class CL> class linkedList;
}


// a node of my ll
template <class CL> struct farmingdale::llNode {
	CL data;
	llNode<CL>* next;
};

// Each method has a notation next to it indicating the Module in which you will program it.
// M7 = we will implement in Module 7, M8 = implement in Module 8
template <class CL> class farmingdale::linkedList {
private:
	llNode<CL>* head; // first node
	llNode<CL>* tail; // last node
public:
	linkedList(); // M7 // default ctor

	// Rule of threes
	linkedList(const linkedList<CL>&); // M8 // copy ctor
	~linkedList(); // M7 // dtor
	// not a reference paramter because we use copy/swap
	const linkedList& operator=(linkedList<CL>); //M8 // assignment operator

	// accessors
	inline bool isEmpty() const
	{
		//we can check either if head is 0, or if tail is 0
		return (0 == head);
	};// M7 // write inline

	statusCode getHead(CL&) const; // M7
	statusCode getTail(CL&) const; // M7
	bool operator==(const linkedList<CL>&) const; // M7 (I write in the videos) // base comparison operator
	bool operator==(const std::deque<CL>&) const; //M7 (I write in the videos)
														   // print a linkedList to a stream (e.g., std::cout)
	void printToStream(std::ostream& outputStream) const; // M7 (I write in the videos)
	llNode<CL>* search(CL) const; // M8

	inline bool contains(CL findMe) {

		//Step 1: call search -- and see if it returns null
		if (0 == search(findMe))
			return true;
		else return false;
	} // M8 // write inline using search

	llNode<CL>* findAtPostion(int) const; // M8 // 0 = first item, 1 == second ....

	// mutators
	statusCode insertAtHead(CL); // M7
	statusCode removeAtHead(CL&); // M7
	statusCode insertAtTail(CL); // M7
	statusCode insertAfter(llNode<CL>*, CL); // M8
	statusCode removeAtTail(CL&); // M8
	statusCode remove(llNode<CL>*); // M8  

	inline statusCode remove(CL removeMe) {

		//Step 1: first call search(string)
		llNode<CL>* removeNode = search(removeMe);

		//Step 2: if search succeeds, call remove (node*)
		if (0 == removeNode) {
			return FAILURE;
		}
		return (remove(removeNode));
	} // M8 // write inline



};

// Write the following here as outside inline functions: (all M7)
// operator!= linkedList,linkedList
template <class CL> inline bool operator!=(const farmingdale::linkedList<CL>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (!(rhs == lhs));
}

// operator!= linkedList,std::deque
template <class CL> inline bool operator!=(const farmingdale::linkedList<CL>& lhs, const std::deque<CL>& rhs) {
	return (!(lhs == rhs));
}

// operator!= std::deque,linkedList
template <class CL> inline bool operator!=(const std::deque<CL>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (!(rhs == lhs));
}

// operator== std::deque,linkedList
template <class CL> inline bool operator==(const std::deque<CL>& lhs, const farmingdale::linkedList<CL>& rhs) {
	return (rhs == lhs);
}

template <class CL> inline std::ostream& operator<<(std::ostream& theStream, const farmingdale::linkedList<CL>& theLinkedList) {
	theLinkedList.printToStream(theStream);
	return theStream;
}



// print a linkedList to a stream (e.g., std::cout)
template <class CL> void farmingdale::linkedList<CL>::printToStream(std::ostream& outputStream) const {

	llNode<CL>* myIter = head;
	while (0 != myIter) {
		if (myIter != head) {
			outputStream << ";";
		}
		outputStream << myIter->data;
		myIter = myIter->next;
	}
}

//default Ctor
template <class CL> farmingdale::linkedList<CL>::linkedList()
	:
	head(0),
	tail(0)
{}

//get Head
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::getHead(CL& returnedValue) const {

	//Step 1: If the list is empty, return FAILURE
	if (isEmpty()) {
		return FAILURE;
	}

	//Step 2: Put the head's data value into returnedValue
	returnedValue = head->data;

	//Step 3: Return SUCCESS
	return SUCCESS;
}

//get Tail
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::getTail(CL& returnedValue) const {

	//Step 1: If the list is empty, return FAILURE
	if (isEmpty()) {
		return FAILURE;
	}

	//Step 2: Put the tail's data value into returnedValue
	returnedValue = tail->data;

	//Step 3: Return SUCCESS
	return SUCCESS;
}

//insert At Head
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::insertAtHead(CL addMe) {

	//Step 1: Allocate memory for a new node. Return FAILURE if that fails
	llNode<CL>* temp;
	try {
		temp = new llNode<CL>;
	}
	catch (std::bad_alloc) {
		return FAILURE;
	}

	//Step 2: Assign addMe to the data field of the new node
	temp->data = addMe;

	//Step 3: Always set the next field of the new node to head
	temp->next = head;

	//Step 4: Make head point to our new node
	head = temp;

	//Step 5: If tail is null, then set tail to point to the new node
	if (0 == tail) {
		tail = temp;
	}

	//Step 6: Return SUCCESS
	return SUCCESS;
}

//insert At Tail
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::insertAtTail(CL addMe) {

	//Step 1: Allocate memory for a new node. Return FAILURE if that fails
	llNode<CL>* temp;
	try {
		temp = new llNode<CL>;
	}
	catch (std::bad_alloc) {
		return FAILURE;
	}

	//Step 2: Assign addMe to the data field of the new node
	temp->data = addMe;

	//Step 3: Set the next field of the new node to ... 0
	temp->next = 0;

	//Step 4a: If tail is not NULL,
	if (NULL != tail) {
		//Step 4b: set the tails next field to point to the new node.
		tail->next = temp;
	}

	//Step 5: Set tail to point to new node
	tail = temp;

	//Step 6a: if head is NULL,
	if (NULL == head) {
		//Step 6b: head should point to the new node.
		head = temp;
	}

	//Step 7: Return SUCCESS
	return SUCCESS;
}

//remove At Head
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::removeAtHead(CL& removedValue) {

	llNode<CL>* oldHead = head;

	//Step 1: If the list is empty, then we fail
	if (isEmpty()) {
		return FAILURE;
	}

	//Step 2: If the list is not empty, then put data from head into removedValue
	removedValue = head->data;

	//Step 3: Make head into current head's next
	head = head->next;

	//Step 4: If head is null, tail should be made null too
	if (NULL == head) {
		tail = 0;
	}

	//Step 5: delete the old head
	delete oldHead;

	//Step 6: return SUCCESS
	return SUCCESS;
}

//Dtor
template <class CL> farmingdale::linkedList<CL>::~linkedList() {

	llNode<CL>* current = head;

	//Step 1: Traverse the linked list
	while (current != 0) {
		llNode<CL>* oldCurrent = current;
		current = current->next;

		//Step 2: Delete each node in turn
		delete oldCurrent;
	}
}

//operator== linkedList
template <class CL> bool farmingdale::linkedList<CL>::operator==(const linkedList<CL>& rhs) const {

	llNode<CL>* current = head;
	llNode<CL>* rhsCurrent = rhs.head;

	//Step1: Do a parallel traversal
	while (0 != current && 0 != rhsCurrent) {
		//Step 2: during the traversal, 
			//if current data and rhs's data are not the same, return FALSE
		if (current->data != rhsCurrent->data)
			return false;
		current = current->next;
		rhsCurrent = rhsCurrent->next;
	}

	//Step 3: if both current and rhsCurrent are null, then return true
	if (NULL == current && NULL == rhsCurrent) {
		return true;
	}

	//Step 4: return false
	return false;
}

//operator== deque
template <class CL> bool farmingdale::linkedList<CL>::operator==(const std::deque<CL>& rhs) const {

	llNode<CL>* current = head;
	std::deque<std::string>::const_iterator rhsIterator = rhs.begin();

	//Step 1: do a parallel traversal
	while (0 != current && rhs.end() != rhsIterator) {
		//Step 2: if at any step, the data differs, returnfalse
		if (current->data != *rhsIterator) {
			return false;
		}
		current = current->next;
		++rhsIterator;
	}

	//Step 3: if both are done after the traversal, then return true
	if (0 == current && rhs.end() == rhsIterator) {
		return true;
	}

	//Step 4: return false
	return false;
}

//Copy Ctor
template <class CL> farmingdale::linkedList<CL>::linkedList(const linkedList& copyMe)
	:
	head(0), tail(0)
{
	llNode<CL>* otherNode = copyMe.head;

	//Step 1: Traverse copyMe, in each iteration
	while (0 != otherNode) {

		//Step 2: Create a new node
		llNode<CL>* temp = new llNode<CL>;

		//Step 3: copy the content of the node from the traversal
		temp->data = otherNode->data;

		//Step 4: add new node to the end of us
		temp->next = 0;

		//if we exist, add to our tail
		if (0 != tail) {
			tail->next = temp;
		}
		else {
			head = temp;
		}

		tail = temp;
		otherNode = otherNode->next;
	}
}

//insertAfter()
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::insertAfter(llNode<CL>* insertAfterMe, CL stringToInsert) {

	//Step 1: create a new node, fail if we cannot create this node (set data)
	llNode<CL>* temp;
	try {
		temp = new llNode<CL>;
	}
	catch (std::bad_alloc) {
		return FAILURE;
	}
	temp->data = stringToInsert;

	//Step 2: stitch the new node in between insertAfterMe and its successor
	 //take the next field of the new node, and put the successor there
	temp->next = insertAfterMe->next;
	//make new node the successor of insertAfterMe
	insertAfterMe->next = temp;

	//Step 3: if insertAfterMe was the tail, we are the new tail
	if (insertAfterMe == tail)
		tail = temp;

	//Step 4: return successs
	return SUCCESS;
}

//search(std::String)
template <class CL> farmingdale::llNode<CL>* farmingdale::linkedList<CL>::search(CL searchVal) const {
	//Step 1: traverse the list but stop when we find it
	llNode<CL>* current = head;
	while (current != 0) {
		if (current->data == searchVal)
			return current;
		current = current->next;
	}
	//Step 3: return null
	return NULL;
}

//removeAtTail()
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::removeAtTail(CL& returnedString) {

	//Step 1: if empty, return failure
	if (isEmpty())
		return FAILURE;

	//Step 2: do a traversal with trailCurrent (TC) until current=tail
	llNode<CL>* current = head;
	llNode<CL>* trailCurrent = 0;
	while (0 != current && current != tail) {
		trailCurrent = current;
		current = current->next;
	}

	//Step 3a: if there was a single node, then set head and tail to null
	if (0 == trailCurrent)
		head = 0;
	else {
		//Step 3b: otherwise, switch out current from the ll. (make TC's into 0)
		trailCurrent->next = 0;
	}
	tail = trailCurrent;

	//Step 4: get the string from current 
	returnedString = current->data;

	//Step 5: delete current
	delete current;

	//step 6: return success
	return SUCCESS;
}

//remove(*)
template <class CL> farmingdale::statusCode farmingdale::linkedList<CL>::remove(llNode<CL>* removeMe) {

	//Step 1: Do a traversal with a trailCurrent. Stop when current == removeMe
	llNode<CL>* current = head;
	llNode<CL>* trailCurrent = 0;
	while (0 != current && current != removeMe) {
		trailCurrent = current;
		current = current->next;
	}

	//Step 2: if current is null, then removeMe is not in this LL --so return failure
	if (0 == current)
		return FAILURE;

	//Step 3: if removeMe is head, then remove the head
	if (removeMe == head) {
		llNode<CL>* oldHead = head;
		if (isEmpty()) {
			return FAILURE;
		}
		head = head->next;
		if (NULL == head) {
			tail = 0;
		}
		delete oldHead;
	}

	//Step 4: if current is an interior node (or tail), switch out current
	if ((current != head && current != tail) || current == tail) {
		//trailCurrent's new successor will be current's current successor
		trailCurrent->next = current->next;
	}

	//Step 5: if tail was current, tail will become trailCurrent
	if (current == tail)
		tail = trailCurrent;

	//Step 6 : delete current
	delete current;

	//Step 7: return
	return SUCCESS;
}

//findAtPosition() RENAMED TO findAtPostion BECAUSE OF TEST CODE BUG
template <class CL> farmingdale::llNode<CL>* farmingdale::linkedList<CL>::findAtPostion(int iterator) const {

	//Step 1: traverse the list, stop when you've iterated nth times.
		//Stop if current is null
	llNode<CL>* current = head;
	int i = 0;
	while (current != 0 && i != iterator) {
		current = current->next;
		i++;
	}

	//Step 2: return current
	return current;
}




#endif // TEMPLATED_LINKEDLIST


#endif // H_FARMINGDALELINKEDLIST