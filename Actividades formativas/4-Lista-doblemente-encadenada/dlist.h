/*
 * dlist.h
 * Actividad Formativa 4: Lista doble ligada
 * 07/10/2025
 * Lucca Traslosheros Abascal
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>
#include <stdexcept>

template <class T> class DList;

template <class T>
class DLink {
private:
    DLink(T);
    DLink(T, DLink<T>*, DLink<T>*);

    T           value;
    DLink<T> *previous;
    DLink<T> *next;

    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), 
previous(prev), next(nxt) {}

template <class T>
class DList {
public:
    DList();
    ~DList();
    bool empty() const;
    void clear();

    // tarea
    void insertion(T val);
    std::string toStringForward() const;
    std::string toStringBackward() const;
    int search(T val) const;
    void update(int index, T val);
    void deleteAt(int index);

private:
    DLink<T> *head;
    DLink<T> *tail;
    int       size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
    clear();
}

template <class T>
bool DList<T>::empty() const {
    return size == 0;
}

template <class T>
void DList<T>::clear() {
    DLink<T> *current = head;
    DLink<T> *nextNode;
    while (current != 0) {
        nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
void DList<T>::insertion(T val) {
    DLink<T> *newLink = new DLink<T>(val);

    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *pointr = head;
    aux << "[";
    while (pointr != 0) {
        aux << pointr->value;
        if (pointr->next != 0) {
            aux << ", ";
        }
        pointr = pointr->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
    std::stringstream aux;
    DLink<T> *pointr = tail;
    aux << "[";
    while (pointr != 0) {
        aux << pointr->value;
        if (pointr->previous != 0) { 
            aux << ", ";
        }
        pointr = pointr->previous;
    }
    aux << "]";
    return aux.str();
}

template <class T>
int DList<T>::search(T val) const {
    DLink<T> *pointr = head;
    int index = 0;
    while (pointr != 0) {
        if (pointr->value == val) {
            return index;
        }
        pointr = pointr->next;
        index++;
    }
    return -1;
}

template <class T>
void DList<T>::update(int index, T val) {
    if (index < 0 || index >= size) {
        return; // checar si es valido
    }
	// iterar hasta encontrarlo
    DLink<T> *pointr = head;
	int idx = 0;
    while (idx != index) {
        pointr = pointr->next;
		idx++;
    }
    pointr->value = val;
}

template <class T>
void DList<T>::deleteAt(int index) {
    if (index < 0 || index >= size) {
        return; // checar si es valido
    }

    DLink<T> *pointr;
    if (index == 0) {
        // para borrar al principio
        pointr = head;
        head = pointr->next;
        if (head != 0) {
            head->previous = 0;
        } else { // por si la lista queda vacia
            tail = 0;
        }
    } else {
        // checar si es al final
        pointr = head;
        for (int i = 0; i < index; i++) {
            pointr = pointr->next;
        }
        pointr->previous->next = pointr->next;
        if (pointr->next == 0) {
            // borrar del final
            tail = pointr->previous;
        } else {
            // ajustar el apuntador del proximo si esta en medio
            pointr->next->previous = pointr->previous;
        }
    }
    delete pointr;
    size--;
}

#endif /* DLIST_H_ */