#pragma once
#include"Node.h"
#include"Comparator.h"
#include<iostream>
using namespace std;
template<class T> class LinkedList {
private:
	Node<T>* hptr;
	Node<T>* cptr;
	Node<T>* tptr;
	Node<T>* nptr;
	Node<T>* pptr;
	int index;
public:
	LinkedList();
	LinkedList(T array[]);
	void add(T newNode);
	void remove(int i);
	T& get(int i);
	Node<T>* first();
	Node<T>* last();
	int size();
	void addAll(LinkedList<T> list);
	bool contains(T value);
	void sort(Comparator<T>& comp);
};
template<class T> LinkedList<T>::LinkedList() {
	hptr = nullptr;
	cptr = nullptr;
	tptr = nullptr;
	nptr = nullptr;
	pptr = nullptr;
	index = 0;
}
template<class T> LinkedList<T>::LinkedList(T array[]) {
	hptr = nullptr;
	cptr = nullptr;
	tptr = nullptr;
	nptr = nullptr;
	pptr = nullptr;
	index = 0;
	for (int i = 0; i < sizeof(array); i++) {
		this->add(array[i]);
	}
}
template<class T> void LinkedList<T>::add(T newNode) {
	Node<T>* node = new Node<T>;
	node->data = newNode;
	node->next = nullptr;
	node->prev = nullptr;
	if (hptr == nullptr) {
		hptr = node;
		tptr = node;
	}
	else {
		node->prev = tptr;
		tptr->next = node;
		tptr = node;
	}
	index++;
}
template<class T> void LinkedList<T>::remove(int i) {
	cptr = hptr;
	if (i <= index) {
		int base = 0;
		while (base < i) {
			cptr = cptr->next;
			base++;
		}
		pptr = cptr->prev;
		pptr->next = cptr->next;
		nptr = cptr->next;
		nptr->prev = cptr->prev;
		index--;
	}
	else {
		cout << "IndexOutOfBoundsException:" << endl;
		cout << "Index: " << index << " Value: " << i << endl;
	}
}
template<class T> T& LinkedList<T>::get(int i) {
	if (i < 0 || i >= index) {
		cout << "IndexOutOfBoundsException:" << endl;
		cout << "Index: " << index << " Value: " << i << endl;
		exit(1);
	}
	cptr = hptr;
	int base = 0;
	while (base < i && cptr != nullptr) {
		cptr = cptr->next;
		base++;
	}
	return cptr->data;
}
template<class T> Node<T>* LinkedList<T>::first() {
	return hptr;
}
template<class T> Node<T>* LinkedList<T>::last() {
	return tptr;
}
template<class T> int LinkedList<T>::size() {
	return index;
}
template<class T> void LinkedList<T>::addAll(LinkedList<T> list) {
	Node<T>* aptr = list.hptr;
	while (aptr != nullptr) {
		this->add(aptr->data);
		aptr = aptr->next;
	}
}
template<class T> bool LinkedList<T>::contains(T value) {
	cptr = hptr;
	while (cptr != nullptr) {
		if (cptr->data == value) {
			return true;
		}
		else {
			cptr = cptr->next;
		}
	}
	return false;
}
template<class T> void LinkedList<T>::sort(Comparator<T>& comp) {
	for (int i = 0; i < index - 1; i++) {
		int swaps = 0;
		cptr = hptr;
		while (cptr->next != nullptr) {
			if (comp.compare(cptr->data, cptr->next->data) > 0) {
				T hold = cptr->data;
				cptr->data = cptr->next->data;
				cptr->next->data = hold;
				swaps++;
			}
			cptr = cptr->next;
		}
		if (swaps == 0) {
			break;
		}
	}
}
