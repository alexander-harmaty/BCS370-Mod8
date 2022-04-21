// (c) 2013-2020, David Gerstl, all rights reserved
// For the use of my C++ students to use as a base to implement
// various programs needed for their data structures class.

// Class farmingdale::linkedList: General string linked List implementation
#include <iostream> // for ostream::operator<<
#include <string>
#include <deque>
#include "farmingdaleLinkedList.h"


#ifndef TEMPLATED_LINKEDLIST
int studentTest() {
	return 0;
}

// print a linkedList to a stream (e.g., std::cout)
void farmingdale::linkedList::printToStream(std::ostream& outputStream) const {

	llNode* myIter = head;
	while (0 != myIter) {
		if (myIter != head) {
			outputStream << ";";
		}
		outputStream << myIter->data;
		myIter = myIter->next;
	}
}

//default Ctor
farmingdale::linkedList::linkedList()
	:
	head(0),
	tail(0)
{}

//get Head
farmingdale::statusCode farmingdale::linkedList::getHead(std::string& returnedValue) const {

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
farmingdale::statusCode farmingdale::linkedList::getTail(std::string& returnedValue) const {

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
farmingdale::statusCode farmingdale::linkedList::insertAtHead(std::string addMe) {

	//Step 1: Allocate memory for a new node. Return FAILURE if that fails
	llNode* temp;
	try {
		temp = new llNode;
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
farmingdale::statusCode farmingdale::linkedList::insertAtTail(std::string addMe) {

	//Step 1: Allocate memory for a new node. Return FAILURE if that fails
	llNode* temp;
	try {
		temp = new llNode;
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
farmingdale::statusCode farmingdale::linkedList::removeAtHead(std::string& removedValue) {

	llNode* oldHead = head;

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
farmingdale::linkedList::~linkedList() {

	llNode* current = head;

	//Step 1: Traverse the linked list
	while (current != 0) {
		llNode* oldCurrent = current;
		current = current->next;

		//Step 2: Delete each node in turn
		delete oldCurrent;
	}
}

//operator== linkedList
bool farmingdale::linkedList::operator==(const linkedList& rhs) const {

	llNode* current = head;
	llNode* rhsCurrent = rhs.head;

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
bool farmingdale::linkedList::operator==(const std::deque<std::string>& rhs) const {

	llNode* current = head;
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



//FOR MOD 8: toggle comments in .h line 33 & 38

//Copy Ctor
farmingdale::linkedList::linkedList(const linkedList& copyMe)
	:
	head(0), tail(0)
{
	llNode* otherNode = copyMe.head;

	//Step 1: Traverse copyMe, in each iteration
	while (0 != otherNode) {

		//Step 2: Create a new node
		llNode* temp = new llNode;

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
farmingdale::statusCode farmingdale::linkedList::insertAfter(llNode* insertAfterMe, std::string stringToInsert) {

	//Step 1: create a new node, fail if we cannot create this node (set data)
	llNode* temp;
	try {
		temp = new llNode;
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
farmingdale::llNode* farmingdale::linkedList::search(std::string searchVal) const {
	//Step 1: traverse the list but stop when we find it
	llNode* current = head;
	while (current != 0) {
		if (current->data == searchVal)
			return current;
		current = current->next;
	}
	//Step 3: return null
	return NULL;
}

//removeAtTail()
farmingdale::statusCode farmingdale::linkedList::removeAtTail(std::string& returnedString) {

	//Step 1: if empty, return failure
	if (isEmpty())
		return FAILURE;

	//Step 2: do a traversal with trailCurrent (TC) until current=tail
	llNode* current = head;
	llNode* trailCurrent = 0;
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
farmingdale::statusCode farmingdale::linkedList::remove(llNode* removeMe) {

	//Step 1: Do a traversal with a trailCurrent. Stop when current == removeMe
	llNode* current = head;
	llNode* trailCurrent = 0;
	while (0 != current && current != removeMe) {
		trailCurrent = current;
		current = current->next;
	}

	//Step 2: if current is null, then removeMe is not in this LL --so return failure
	if (0 == current)
		return FAILURE;

	//Step 3: if removeMe is head, then remove the head
	if (removeMe == head) {
		llNode* oldHead = head;
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

//findAtPosition()
farmingdale::llNode* farmingdale::linkedList::findAtPosition(int iterator) const {

	//Step 1: traverse the list, stop when you've iterated nth times.
		//Stop if current is null
	llNode* current = head;
	int i = 0;
	while (current != 0 && i != iterator) {
		current = current->next;
		i++;
	}

	//Step 2: return current
	return current;
}
#else // TEMPLATED_LINKEDLIST

int studentTest() {
	return 0;
}
#endif // TEMPLATED_LINKEDLIST