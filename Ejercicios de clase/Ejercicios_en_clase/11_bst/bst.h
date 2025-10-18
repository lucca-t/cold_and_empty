/*
 * bst.h
 *
 *  Created on: 30/10/2015
 *      Author: clase
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include "exception.h"
#include <iostream>
#include <cstring>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* succesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;

	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) {
	value = val;
	left = NULL;
	right = NULL;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) {
	value = val;
	left = le;
	right = ri;
}

template <class T>
void TreeNode<T>::add(T val) {
	if (val != value) {
		if (val < value) {
			if (left == NULL) {
				TreeNode<T> * nuevo_nodo = new TreeNode<T>(val);
				if (nuevo_nodo == 0) {
					throw OutOfMemory();
				}
				left = nuevo_nodo;
			} else {
				left->add(val);
			}
		} else {
			if (right == NULL) {
				TreeNode<T> * nuevo_nodo = new TreeNode<T>(val);
				if (nuevo_nodo == 0) {
					throw OutOfMemory();
				}
				right = nuevo_nodo;
			} else {
				right->add(val);
			}
		}
	} 
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	}

	if (val < value) {
		if (left == NULL) {
			return false;
		} 
		return left->find(val);
	} else {
		if (right == NULL) {
			return false;
		}
		return right->find(val);
	}
}

template <class T>	
TreeNode<T>* TreeNode<T>::succesor() {
	// Buscar el mayor de los menores
	if (left != NULL) {
		TreeNode<T> * sucesor = left;
		if (left->right == NULL) {
			left = left->left;
			sucesor->left = NULL;
			return sucesor;
		}
		TreeNode<T> * ancestro = sucesor;
		while (sucesor->right != NULL) {
			ancestro = sucesor;
			sucesor = sucesor->right;
		}
		if (sucesor->left != NULL) {
			ancestro->right = sucesor->left;
			sucesor->left = NULL;
		} else {
			ancestro->right = NULL;
		}
		return sucesor;

	} else { // Si no hay rama izquierda, buscar el menor de los mayores

	}
	return 0;
}

template <class T>
void TreeNode<T>::remove(T val) {
	if (val < value) {
		if (left->value == val) {
			if (left->left == NULL && left->right == NULL) { //Es hoja
				delete left->left;
				left = NULL;
			} else { //Es rama
				TreeNode<T> * victima = left;
				TreeNode<T> * sucesor = left->succesor();
				sucesor->left = victima->left;
				sucesor->right = victima->right;
				victima->left = NULL;
				victima->right = NULL;
				left = sucesor;
				delete victima;
			}
		} else {
			left->remove(val);
		}
	} else {
		// hoja
		if (right->value == val) {
			if(right->left == NULL && right->right == NULL) {
				delete right;
				right = NULL;
			// rama
			} else {
				right ->remove(val);

			}
		} else {
			right->remove(val);
		}

		// hoja
		// 
	}
}

template <class T>
void TreeNode<T>::removeChilds() {
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string inorder() const;
	std::string preorder() const;
};

template <class T>
BST<T>::BST() : root(0) {
	root = NULL;
}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root == NULL) {
		TreeNode<T> * nuevo_nodo = new TreeNode<T>(val);
		if (nuevo_nodo == NULL) {
			throw OutOfMemory();
		}
		root = nuevo_nodo;
	} else {
		root->add(val);
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (!root->find(val)) {
		throw NoSuchElement();
	}
	if (root->left == NULL && root->right == NULL) {
		delete root;
		root = NULL;
	} else {
		if (root->value == val) {
			TreeNode<T> * sucesor = root->succesor();
			sucesor->left = root->left;
			sucesor->right = root->right;
			root->left = NULL;
			root->right = NULL;
			delete root;
			root = sucesor;
		} else {
			root->remove(val);
		}
	}
}

template <class T>
void BST<T>::removeAll() {
}

template <class T>
bool BST<T>::find(T val) const {
	return root->find(val);
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* BST_H_ */
