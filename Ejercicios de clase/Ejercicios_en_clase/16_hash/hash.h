/*
        Actividad Formativa 9: Hash
        25 de noviembre de 2025
        Lucca Traslosheros Abascal
*/
#ifndef HASH_H_
#define HASH_H_

#include <sstream>
#include <string>

#include "exception.h"

template <class Key, class Value>
class HashTable {
   private:
    unsigned int (*func)(const Key);
    unsigned int size;
    unsigned int count;

    Key* keys;
    Key initialValue;
    Value* values;

    long indexOf(const Key) const;

   public:
    HashTable(unsigned int, Key, unsigned int (*f)(const Key));
    ~HashTable();
    bool full() const;
    bool put(Key, Value);
    bool contains(const Key) const;
    Value get(const Key);
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
HashTable<Key, Value>::HashTable(unsigned int sze, Key init, unsigned int (*f)(const Key)) {
	func = f;
	size = sze;
	initialValue = init;
	count = 0;
	keys = new Key[sze];
	if (keys == NULL) {
		throw OutOfMemory();
	}
	for (int i = 0; i < sze; i++) {
		keys[i] = "empty";
	}

	values = new Value[sze];
	if (values == NULL) {
		throw OutOfMemory();
	}
	for (int i = 0; i < sze; i++) {
		values[i] = 0;
	}

}

template <class Key, class Value>
HashTable<Key, Value>::~HashTable() {
	func = NULL;
	size = 0;
	count = 0;

	delete [] keys;
	keys = NULL;

	delete [] values;
	values = NULL;
}

template <class Key, class Value>
bool HashTable<Key, Value>::full() const {
    if (count == size) {
		return true;
	}
	return false;
}

template <class Key, class Value>
long HashTable<Key, Value>::indexOf(const Key k) const {

	int hash = func(k) % size;

	// Si es el inicial esta vacio
	if (keys[hash] == initialValue ) {
		return -1;
	}
	// usar como index
	int index = hash;

	// checar el primero
	if (keys[index] == k ){
		return index;
	}
	index ++;

	while (index != hash && (keys[index] == initialValue))  {
		if (keys[index] == k) {
			return index;
		}
		index = (index + 1) % size;
	}
	return -1;

}

template <class Key, class Value>
bool HashTable<Key, Value>::put(Key k, Value v) {

	// hashaerla alv
	int hash = func(k) % size;
	// si no cabe moverle
	if (keys[hash] == k) {
		values[hash] = v;
		return true;
	}

	if (full()) {
		throw Overflow();
	}

	if (keys[hash] == initialValue) {
		keys[hash] = k;
		values[hash] = v;
		count++;
		return true;
	}

	// Usar index y guarda hash como inicio
	int index = hash;
	index ++;

	while (index != hash) {
		if (keys[index] == initialValue) {
			keys[index] = k;
			values[index] = v;
			count++;
			return true;	
		}
		// sondeo lineal
		index = (index + 1) % size;
	}
	// si no cupo false alv
	return false;
}

template <class Key, class Value>
bool HashTable<Key, Value>::contains(const Key k) const {
    
	int index = indexOf(k);
	if (index == -1) {
		return false;
	}
	return true;

}

template <class Key, class Value>
Value HashTable<Key, Value>::get(const Key k) {
    Value v;
	if (!contains(k)) {
		throw NoSuchElement();
	}
	int index = indexOf(k);
	v = values[index];
	
    return v;
}

template <class Key, class Value>
void HashTable<Key, Value>::clear() {
	for (int i = 0; i < size; i++) {
		keys[i] = "empty";
	}
}

template <class Key, class Value>
std::string HashTable<Key, Value>::toString() const {
    std::stringstream aux;

    for (unsigned int i = 0; i < size; i++) {
        aux << "[ " << i << ", " << keys[i] << ", " << values[i] << "]\n";
    }
    return aux.str();
}
#endif /* HASH_H_ */
