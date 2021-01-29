#ifndef CIRCULAR_LIST_H_
#define CIRCULAR_LIST_H_

#include "List.h"


template<typename T>
class CircularList : public List<T> {
	Node<T>* back();

public:
	CircularList();
	~CircularList();

	// MODIFIERS
	virtual void deleteFront() override;
	virtual void deleteAfter(Node<T>*) override;
	virtual void insertFront(const T&) override;
	virtual void insertAfter(Node<T>*, const T&) override;

	// FRIENDS
	template<typename OT>
	friend std::ostream& operator<<(std::ostream&, const CircularList<OT>&);
};

#endif // !CIRCULAR_LIST_H_


template<typename T>
inline CircularList<T>::CircularList() : List<T>() {}

template<typename T>
inline CircularList<T>::~CircularList() 
{
	for (Node<T>* temp = List<T>::start; temp; temp = List<T>::start)
		deleteFront();
}


// MODIFIERS
template<typename T>
void CircularList<T>::deleteFront() 
{
	if (List<T>::start)
	{
		if (List<T>::start->next == List<T>::start) 
			List<T>::start->next = nullptr;
		else
		{
			Node<T>* temp = back();
			if (temp->next) temp->next = List<T>::start->next;
		}
		List<T>::deleteFront();
	}
	else throw ListException<T>();
}

template<typename T>
void CircularList<T>::deleteAfter(Node<T>* node)
{
	if (node && node->next) 
	{
		if (List<T>::start->next == List<T>::start)
			deleteFront();
		else
		{
			if (node->next == List<T>::start)
			{
				Node<T>* temp = List<T>::start->next;
				List<T>::deleteAfter(node);
				List<T>::start = temp;
			}
			else List<T>::deleteAfter(node);
		}
	}
	else throw ListException<T>();
}

template<typename T>
void CircularList<T>::insertFront(const T& value)
{
	Node<T>* temp = back();
	List<T>::insertFront(value);
	if (temp) temp->next = List<T>::start;
}

template<typename T>
void CircularList<T>::insertAfter(Node<T>* node, const T& value)
{
	if (node && node->next)
	{
		Node<T>* start = List<T>::start;
		List<T>::start = node->next;

		insertFront(value);
		List<T>::start = start;
	}
	else throw ListException<T>();
}



// PRIVATE
template<typename T>
inline Node<T>* CircularList<T>::back()
{
	Node<T>* temp = List<T>::start;
	if (temp && temp->next)
		while (temp->next != List<T>::start)
			temp = temp->next;
	return temp;
}


// FRIENDS
template<typename T>
std::ostream& operator<<(std::ostream& out, const CircularList<T>& list)
{
	Node<T>* temp = list.getStart();
	if (temp)
		do {
			out << temp->getData() << " ";
			temp = temp->getNext();
		} while (temp != list.getStart());
	return out;
}