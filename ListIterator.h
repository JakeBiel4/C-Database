#pragma once
#include"Node.h"
#include"LinkedList.h"
template<class T> class ListIterator {
private:
	Node<T>* start;
	Node<T>* current;
public:
	ListIterator(LinkedList<T>& ll);
	T* curr();
	void inc();
	void dec();
	void reset();
	bool has();
};
template<class T> ListIterator<T>::ListIterator(LinkedList<T>& ll) {
	start = ll.first();
	current = start;
}
template<class T> T* ListIterator<T>::curr() {
	if (!current) {
		return nullptr;
	}
	return &current->data;
}
template<class T> void ListIterator<T>::inc() {
	if (current) {
		current = current->next;
	}
}
template<class T> void ListIterator<T>::dec() {
	if (current) {
		current = current->prev;
	}
}
template<class T> void ListIterator<T>::reset() {
	current = start;
}
template<class T> bool ListIterator<T>::has() {
	return current != nullptr;
}
