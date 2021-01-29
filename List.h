#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "Node.h"
#include "ListException.h"



template<typename T>
class List
{
	size_t listSize;
protected:
	Node<T>* start;
public:
	List();
	virtual ~List();

	// GETTERS
	Node<T>* getStart() const;

	// SIZE
	size_t size() const;

	// MODIFIERS
	virtual void deleteFront();
	void deleteBack();
	virtual void deleteAfter(Node<T>*);
	virtual void insertFront(const T&);
	void insertBack(const T&);
	virtual void insertAfter(Node<T>*, const T&);
	
	// FRIENDS
	template<typename OT>
	friend std::ostream& operator<<(std::ostream&, const List<OT>&);
};


template<typename T>
List<T>::List() : start(nullptr), listSize(0) {}

template<typename T>
List<T>::~List() { while (start) deleteFront(); }


// SIZE
template<typename T>
size_t List<T>::size() const { return listSize; }


// GETTERS
template<typename T>
Node<T>* List<T>::getStart() const { return start; }


// MODIFIERS
template<typename T>
void List<T>::deleteFront() 
{
	if (start) 
	{
		Node<T>* temp = start->next;
		delete start;

		start = temp;
		listSize--;
	}
	else throw ListException<T>();
}

template<typename T>
void List<T>::deleteBack() 
{
	if (start) 
	{
		if (start->next) 
		{
			Node<T>* temp = start;
			register size_t cnt = 1;
			while (temp->next && ++cnt < listSize)
				temp = temp->next;

			delete temp->next;
			temp->next = nullptr;
		}
		else delete start;
		listSize--;
	}
	else throw ListException<T>();
}

template<typename T>
void List<T>::deleteAfter(Node<T>* node) 
{
	if (node && node->next) 
	{
		Node<T>* temp = node->next;
		node->next = node->next->next;
		delete temp;
		listSize--;
	}
	else throw ListException<T>();
}

template<typename T>
void List<T>::insertFront(const T& value) 
{ 
	start = new Node<T>(value, start); 
	listSize++;
}

template<typename T>
void List<T>::insertBack(const T& value) 
{
	if (start) 
	{
		Node<T>* temp = start;
		while (temp->next) temp = temp->next;

		temp->next = new Node<T>(value, nullptr);
	}
	else start = new Node<T>(value, nullptr);
	listSize++;
}

template<typename T>
void List<T>::insertAfter(Node<T>* node, const T& value) 
{
	if (node) 
	{
		node->next = new Node<T>(value, node->next);
		listSize++;
	}
	else throw ListException<T>();
}


// FRIENDS
template<typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) 
{
	Node<T>* temp = list.start;
	while (temp) 
	{
		out << temp->getData() << " ";
		temp = temp->getNext();
	}
	return out;
}

#endif // !LIST_H_
