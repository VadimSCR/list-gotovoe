#ifndef NODE_H_
#define NODE_H_


template<typename T>
class Node
{
	T data;
	Node* next;
public:
	Node(T, Node* = nullptr);
	~Node();

	// GETTERS
	const T& getData() const;
	Node* getNext() const;

	// FRIENDS
	template<typename FT>
	friend class List;

	template<typename FT>
	friend class CircularList;
};


template<typename T>
Node<T>::Node(T d, Node* nextNode)
	: data(d), next(nextNode) {}

template<typename T>
Node<T>::~Node() {}


// GETTERS
template<typename T>
const T& Node<T>::getData() const { return data; }

template<typename T>
Node<T>* Node<T>::getNext() const { return next; }

#endif // !NODE_H_

