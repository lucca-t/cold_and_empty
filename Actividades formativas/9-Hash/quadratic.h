/*
        Actividad Formativa 9: Quadratic Hash
        28 de noviembre de 2025
        Lucca Traslosheros Abascal
*/
#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <sstream>
#include <string>

template <class Key, class Value>
class Quadratic {
   private:
    unsigned int (*func)(const Key);
    unsigned int size;
    unsigned int count;

    Key* keys;
    Key initialValue;
    Value* values;

    long indexOf(const Key) const;

   public:
    Quadratic(unsigned int, Key, unsigned int (*f)(const Key));
    ~Quadratic();
    bool full() const;
    bool put(Key, Value);
    bool contains(const Key) const;
    Value get(const Key);
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f)(const Key)) {
	func = f;
	size = sze;
	initialValue = init;
	count = 0;
	keys = new Key[sze];
	if (keys == NULL) {
	    // Esta lleno
	}
	for (int i = 0; i < sze; i++) {
		keys[i] = "empty";
	}

	values = new Value[sze];
	if (values == NULL) {
		// Esta lleno
	}
	for (int i = 0; i < sze; i++) {
		values[i] = 0;
	}

}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	func = NULL;
	size = 0;
	count = 0;

	delete [] keys;
	keys = NULL;

	delete [] values;
	values = NULL;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    if (count == size) {
		return true;
	}
	return false;
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
    int hash = func(k) % size;

    for (int i = 0; i < size; i++) {
        int index = (hash + i * i) % size; // sondeo quadratico
        
        if (keys[index] == k) {
            return index;
        }
        
        // Si esta vacio entonces no existe
        if (keys[index] == initialValue) {
            return -1;
        }
    }
    
    return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {

	// Conseguir el hash inicial
	int hash = func(k) % size;

	// Si es la misma llave cambia el valor y ya
	if (keys[hash] == k) {
		values[hash] = v;
		return true;
	}

	if (keys[hash] == initialValue) {
		keys[hash] = k;
		values[hash] = v;
		count++;
		return true;
	}
    
	if (full()) {
		// Esta lleno
        return false;
	}
	// Usar index y guarda hash como inicio

    for (unsigned int i = 0; i < size; i++) {
        unsigned int index = (hash + i * i) % size; 

        // Si esta vacio insertamos
        if (keys[index] == initialValue) {
            keys[index] = k;
            values[index] = v;
            count++;
            return true;
        }

        // Si ya existe la misma llave, actualizamos
        if (keys[index] == k) {
            values[index] = v;
            return true;
        }
    }

	// Si no cupo es false
	return false;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const {
    
	int index = indexOf(k);
	if (index == -1) {
		return false;
	}
	return true;

}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
    Value v;
	if (!contains(k)) {
		// No existe, retornar valor por defecto de 0
        return 0;
	}
    
	int index = indexOf(k);
	v = values[index];
	
    return v;
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	for (int i = 0; i < size; i++) {
		keys[i] = "empty";
	}
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
    std::stringstream aux;

    for (unsigned int i = 0; i < size; i++) {
        if (keys[i] == initialValue){
            continue;
        }
        aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
    }
    return aux.str();
}
#endif /* QUADRATIC_H_ */
