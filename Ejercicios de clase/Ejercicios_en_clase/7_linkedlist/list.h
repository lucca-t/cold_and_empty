/*
 * linkedlist.h
 *
 *  Created on: 05/08/2015
 *      Author: pperezm
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <string>
#include <sstream>
#include "exception.h"

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) {
	value = val;
	next = NULL;
}

template <class T>
Link<T>::Link(T val, Link* nxt) {
	value = val;
	next = nxt;
}

template <class T>
Link<T>::Link(const Link<T> &source) {
	value = source.value;
	next = source.next;
}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();

	void addFirst(T) ;
	void add(T) ;
	T    getFirst() const ;
	T    removeFirst() ;
	int  length() const;
	T    get(int) const  ;
	bool contains(T) const;
	bool empty() const;
	void clear();
	std::string toString() const;
	void operator= (const List&) ;

	void addBefore(ListIterator<T>&, T)  ;
	void addAfter(ListIterator<T>&, T)  ;
	T    removeCurrent(ListIterator<T>&)  ;

	bool set(int, T) ;
	int  indexOf(T) const;
	int  lastIndexOf(T) const;
	T    remove(int) ;
	bool removeFirstOcurrence(T);
	bool removeLastOcurrence(T);

private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List(){
	head = NULL;
	size = 0;
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	if (head == NULL) {
		return true;
	}
	return false;
}

template <class T>
int List<T>::length() const {
	return size;
}

template <class T>
bool List<T>::contains(T val) const {
	if (empty()) {
		return false;
	}
	
	Link<T> * nodo_actual = head;
	
	while (nodo_actual->next != NULL) {
		if (nodo_actual->value == val) {
			return true;
		}
		nodo_actual = nodo_actual->next;
	}
	
	return false;
}

template <class T>
T List<T>::getFirst() const  {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

template <class T>
void List<T>::addFirst(T val)  {
	//Crear el nuevo nodo
	Link<T> * nuevo_nodo = new Link<T>(val);

	//Validar que haya memoria disponible
	if (nuevo_nodo == NULL) {
		throw OutOfMemory();
	}

	//Si la lista está vacía, head apunta al nuevo nodo
	if (empty()) {
		head = nuevo_nodo;
	} else {
		//Si la lista no está vacía, apunta el next del nuevo al head
		nuevo_nodo->next = head;
		//apunta el head hacia el nuevo
		head = nuevo_nodo;
	}
	size++;

}

template <class T>
void List<T>::add(T val)  {
	if (empty()) {
		addFirst(val);
	} else {
		Link<T> *nuevo_nodo = new Link<T>(val);
		if (nuevo_nodo == NULL) {
			throw OutOfMemory();
		}

		Link<T> *nodo_final = head;

		while (nodo_final->next != NULL){
			nodo_final = nodo_final->next;
		}
		nodo_final->next = nuevo_nodo;
		size++;
	}
}

template <class T>
T List<T>::removeFirst()  {
	if (empty()) {
		throw NoSuchElement();
	}
	
	Link<T> *
	 nodo_victima = head;
	T result = nodo_victima->value;
	head = nodo_victima->next;
	
	nodo_victima->next = NULL;
	delete nodo_victima;
	size --;
	return result;

}

template <class T>
T List<T>::get(int index) const   {
	
	if (index < 0 || index >= size) {
		throw IndexOutOfBounds();
	}
	Link<T> *nodo_actual = head;

	for(int i = 0; i < index; i ++ ) {
		nodo_actual = nodo_actual->next;
	}

	return nodo_actual->value;
}

template <class T>
void List<T>::clear() {
	
	Link<T> *nodo_actual = head;

	while (nodo_actual != NULL) {
		Link<T> *nodo_victima = nodo_actual;
		nodo_actual = nodo_actual->next;

		nodo_victima->next = NULL;
		delete nodo_victima;

	}
	head = NULL;
	size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
List<T>::List(const List<T> &source)  {
	head = NULL;
	size = 0;
	Link <T> *nodo_actual = source.head;
	while (nodo_actual != NULL) {
		add(nodo_actual->value);
		nodo_actual = nodo_actual->next;
		
	}
}

template <class T>
void List<T>::operator=(const List<T> &source)  {
	clear();
	head = NULL;
	size = source.size;
	Link <T> *nodo_actual = source.head;
	while (nodo_actual != NULL) {
		add(nodo_actual->value);
		nodo_actual = nodo_actual->next;
		
	}

	size = source.size;
}

template <class T>
void List<T>::addBefore(ListIterator<T> &itr, T val)   {
	
	Link<T> *newLink;
	
	// check if it's the correct list
	if (this != itr.theList) {
		throw IllegalAction();
	}
	// make new node and check if there's memory
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}


	//so if we're adding before
	// [2, 3, 4]
	// 

	//middle
	if(itr.previous != 0){// pointing to valid node currently
		//point current to link
		//point current to new
		newLink-> next = itr.current;
		itr.previous->next = newLink;
		itr.previous = itr.previous->next;
		size++;
	}
	else{//not at the middle and not not in the beginning
		addFirst(val);
		itr.previous = head;
		itr.current = itr.previous->next;
	}
}

template <class T>
void List<T>::addAfter(ListIterator<T> &itr, T val)   {
	// check if out of range
	// iterate thru list

	Link<T> *newLink;
	
	// check if it's the correct list
	if (this != itr.theList) {
		throw IllegalAction();
	}
	// make new node and check if there's memory
	newLink = new Link<T>(val);
	if (newLink == 0) {
		throw OutOfMemory();
	}

	//middle
	if(itr.current != 0){// pointing to valid node currently
		//point current to link
		//point current to new
		newLink-> next = itr.current->next;
		itr.current->next = newLink;
		size++;
	}
	else if( itr.previous != 0){//not at the beginning and not in the middle
		itr.previous->next = newLink;
		newLink->next = NULL;
		size++;
	}
	else{//not at the middle and not not in the beginning
		addFirst(val);
		itr.current = head;
		itr.previous = 0;
	}

}

template <class T>
T List<T>::removeCurrent(ListIterator<T> &itr)   {
	T val;
	// check if it's the correct list
	if (this != itr.theList) {
		throw IllegalAction();
	}
	if (itr.current == 0) {
		throw NoSuchElement();
	}
	//middle
	if(itr.previous != 0) {// set previoux next equal to current next
		itr.previous->next = itr.current->next;
	}else {//set next as head
		head = itr.current->next;
	}

	val = itr.current->value;
	delete itr.current;
	itr.current = 0;
	size--;
	//std::cout << "remove current = " << ((itr.current != 0)? itr.current->value : 0) << " previous: " << ((itr.previous != 0)? itr.previous->value : 0) << std::endl;
	return val;
}


template <class T>
bool List<T>::set(int index, T val)  {
	return false;
}

template <class T>
int List<T>::indexOf(T val) const {
	return -1;
}

template <class T>
int List<T>::lastIndexOf(T val) const {
	return -1;
}

template <class T>
T List<T>::remove(int index)  {
	return 0;
}

template <class T>
bool List<T>::removeFirstOcurrence(T val) {
	return false;
}

template <class T>
bool List<T>::removeLastOcurrence(T val) {
	return false;
}

template <class T>
class ListIterator {
public:
	ListIterator(List<T>*);
	ListIterator(const ListIterator<T>&);

	bool begin();
	bool end();
	T&   operator() () ;
	bool operator++ ();
	void operator= (T) ;

private:
	Link<T> *current;
	Link<T> *previous;
	List<T> *theList;

	friend class List<T>;
};

template <class T>
ListIterator<T>::ListIterator(List<T> *aList) : theList(aList) {
	begin();
}

template <class T>
ListIterator<T>::ListIterator(const ListIterator<T> &source) : theList(source.theList) {
	begin();
}

template <class T>
bool ListIterator<T>::begin() {
	previous = 0;
	current = theList->head;
	return (current != 0);
}

template <class T>
T& ListIterator<T>::operator() ()  {
	if (current == 0) {
		throw NoSuchElement();
	}
	return current->value;
}

template <class T>
bool ListIterator<T>::end() {
	if (current == 0) {
		if (previous != 0) {
			current = previous->next;
		}
	}
	return (current == 0);
}

template <class T>
bool ListIterator<T>::operator++ () {
	if (current == 0) {
		if (previous == 0) {
			current = theList->head;
		} else {
			current = previous->next;
		}
	} else {
		previous = current;
		current = current->next;
	}
	return (current != 0);
}

template <class T>
void ListIterator<T>::operator= (T val)  {
	if (current == 0) {
		throw NoSuchElement();
	}
	current->value = val;
}

#endif /* LINKEDLIST_H_ */
