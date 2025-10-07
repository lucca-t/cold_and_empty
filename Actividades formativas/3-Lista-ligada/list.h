/*
 *  Actividad Formativa 3: Lista-Ligada
 *  Created on: 03/10/2025
 *  	Author: Lucca Traslosheros Abascal
 * 
 */

#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;

template <class T>
class Link {
private:
	Link(T);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	~List();
	void insertion(T);
	int search(T);
	void update(int, T);
	void deleteAt(int);
	std::string toString() const;

private:
	Link<T> *head;
	int 	size;
	void clear();
};

template <class T>
List<T>::List() : head(0), size(0) {}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;
	// p itera para borrar
	// q temporario para aguantar valor
	
	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::insertion(T val) {
    // nuevo link para el nuevo valor
	Link<T> *newLink, *p;
    // asignar valor
	newLink = new Link<T>(val);
    // si esta vacio agregar al principio (como addfirst() )
	if (head == 0) {
		head = newLink;
    // si ya hay una lista, el p checa la lista para agregar al final
	} else {
		p = head;
        // checar hasta llegar al final
		while (p->next != 0) {
			p = p->next;
		}
        // agregar nuevo link
		p->next = newLink;
	}
	size++;
}

template <class T>
int List<T>::search(T val) {
	Link<T> *p;
	int pos = 0;
    // checar toda la lista hasta llegar al valor
    // retornar posicion
	p = head;
	while (p != 0) {
		if (p->value == val) {
			return pos;
		}
		p = p->next;
		pos++;
	}
    // si no la encontro retornar -1 
	return -1;
}

template <class T>
void List<T>::update(int index, T val) {
	Link<T> *p;
	int pos = 0;
    // indice fuera del rango de la lista ligada
	if (index < 0 || index >= size) {
		return;
	}
    // checar toda la lista hasta llegar a la posicion
	p = head;
	while (pos != index) {
		p = p->next;
		pos++;
	}
	p->value = val;
}

template <class T>
void List<T>::deleteAt(int index) {
	Link<T> *p, *q;
    // indice fuera del rango de la lista
	if (index < 0 || index >= size) {
		return;
	}
    // p temporario para mover head
	if (index == 0) {
		p = head;
		head = p->next;
		delete p;
	} else {
		p = head;
		int pos = 0;
		while (pos != (index - 1)) {
			p = p->next;
			pos++;
		}
		q = p->next;
		p->next = q->next;
		delete q;
	}
	size--;
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

#endif /* LIST_H_ */