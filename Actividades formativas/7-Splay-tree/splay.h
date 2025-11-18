/*
    Actividad Formativa 7: Splay Tree
    Lucca Traslosheros Abascal
    11/13/2025
*/

#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
    // Usar parent para que funcione de bottom
	Node<T> *left, *right, *parent;
public:
	Node(T);
	Node(T, Node<T>*, Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
class SplayTree {
private:
	Node<T> *root;

	void inorder(Node<T>*, std::stringstream&) const;
	void preorder(Node<T>*, std::stringstream&) const;
	
	void rot_left(Node<T>*);
	void rot_right(Node<T>*);
	void splay(Node<T>*);
	Node<T>* findNode(T);

public:
	SplayTree();
	void add(T);
	bool find(T);
	void remove(T);
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

// Rotacion a la izquierda
template <class T>
void SplayTree<T>::rot_left(Node<T> *x) {
	Node<T> *y = x->right;
	x->right = y->left;
	if (y->left != 0) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == 0) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// Rotacion a la derecha
template <class T>
void SplayTree<T>::rot_right(Node<T> *x) {
	Node<T> *y = x->left;
	x->left = y->right;
    
    // Checar si tiene algo
	if (y->right != 0) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent== 0) {
		root = y;
	} else if(x== x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

// Splay hace todo para llevar el nodo a la raiz usando rotaciones
template <class T>
void SplayTree<T>::splay(Node<T> *node) {
	while (node->parent != 0) {
		Node<T> *p = node->parent;
		Node<T> *g = p->parent;

		if (g == 0) {
			// Zig
			if (node == p->left) {
				rot_right(p);
			} else {
				rot_left(p);
			}
		} else {
			// Zig-Zig o Zig-Zag
			if (node == p->left && p == g->left) {
				rot_right(g);
				rot_right(p);
			} else if (node == p->right && p == g->right) {
				rot_left(g);
				rot_left(p);
			} else if (node == p->left && p == g->right) {
				rot_right(p);
				rot_left(g);
			} else {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	root = node;
}

template <class T>
void SplayTree<T>::add(T val) {
	Node<T> *y = 0;
	Node<T> *x = root;

	while (x != 0) {
		y = x;
		if (val < x->value) {
			x = x->left;
		} else if (val > x->value) {
			x = x->right;
		} else {
			splay(x);
			return;
		}
	}

	Node<T> *newNode = new Node<T>(val);
	newNode->parent = y;

	if (y == 0) {
		root = newNode;
	} else if (val < y->value) {
		y->left = newNode;
	} else {
		y->right = newNode;
	}

	splay(newNode);
}

template <class T>
Node<T>* SplayTree<T>::findNode(T val) {
	Node<T> *curr = root;
	Node<T> *last = 0;
	while (curr != 0) {
		last = curr;
		if (val == curr->value) {
			splay(curr);
			return curr;
		} else if (val < curr->value) {
			curr = curr->left;
		} else {
			curr = curr->right;
		}
	}
	if (last != 0) {
		splay(last);
	}
	return 0;
}

template <class T>
bool SplayTree<T>::find(T val) {
	Node<T> *node = findNode(val);
	if (node != 0 && node->value == val) {
		return true;
	}
	return false;
}

template <class T>
void SplayTree<T>::remove(T val) {
	Node<T> *node = findNode(val);

	if (node == 0 || node->value != val) {
		return;
	}

	Node<T> *L = node->left;
	Node<T> *R = node->right;

	delete node;

	if (L != 0) L->parent = 0;
	if (R != 0) R->parent = 0;

	if (L == 0) {
		root = R;
	} else {
		Node<T> *maxNode = L;
		while (maxNode->right != 0) {
			maxNode = maxNode->right;
		}

		root = L;
		splay(maxNode);

		root->right = R;
		if (R != 0) {
			R->parent = root;
		}
	}
}

template <class T>
void SplayTree<T>::inorder(Node<T> *node, std::stringstream &aux) const {
	if (node != 0) {
		if (node->left != 0) {
			inorder(node->left, aux);
			aux << " ";
		}
		aux << node->value;
		if (node->right != 0) {
			aux << " ";
			inorder(node->right, aux);
		}
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;
	aux << "[";
	if (root != 0) {
		inorder(root, aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
void SplayTree<T>::preorder(Node<T> *node, std::stringstream &aux) const {
	if (node != 0) {
		aux << node->value;
		if (node->left != 0) {
			aux << " ";
			preorder(node->left, aux);
		}
		if (node->right != 0) {
			aux << " ";
			preorder(node->right, aux);
		}
	}
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;
	aux << "[";
	if (root != 0) {
		preorder(root, aux);
	}
	aux << "]";
	return aux.str();
}

#endif