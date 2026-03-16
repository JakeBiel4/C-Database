#pragma once
template<class T> class Node {
public:
	T data;
	Node<T>* prev;
	Node<T>* next;
	Node();
};
template<class T> Node<T>::Node() {}
