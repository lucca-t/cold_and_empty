/*
Lucca Traslosheros Abascal
Actividad 5 Formativa
17/10/2025

*/



#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <queue>
#include <vector>

template <class T> class BST;

template <class T>
class TreeNode {
private:
    T value;
    TreeNode *left, *right;

public:
    TreeNode(T);
    void add(T);
    int height() const;
    bool ancestors(T, std::stringstream &) const;
    int whatlevelamI(T, int) const;
    void preorder(std::stringstream &) const;
    void inorder(std::stringstream &) const;
    void postorder(std::stringstream &) const;
    void levelorder(std::stringstream &) const;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(nullptr), right(nullptr) {}

template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left == nullptr)
            left = new TreeNode<T>(val);
        else
            left->add(val);
    } else if (val > value) {
        if (right == nullptr)
            right = new TreeNode<T>(val);
        else
            right->add(val);
    }
}

template <class T>
int TreeNode<T>::height() const {
    int leftH = (left == nullptr ? 0 : left->height());
    int rightH = (right == nullptr ? 0 : right->height());
    return 1 + (leftH > rightH ? leftH : rightH);
}

template <class T>
bool TreeNode<T>::ancestors(T val, std::stringstream &ss) const {
    if (val == value)
        return true;

    if (val < value && left != nullptr) {
        if (left->ancestors(val, ss)) {
            ss << value << " ";
            return true;
        }
    } else if (val > value && right != nullptr) {
        if (right->ancestors(val, ss)) {
            ss << value << " ";
            return true;
        }
    }
    return false;
}

template <class T>
int TreeNode<T>::whatlevelamI(T val, int level) const {
    if (val == value)
        return level;
    if (val < value && left != nullptr)
        return left->whatlevelamI(val, level + 1);
    if (val > value && right != nullptr)
        return right->whatlevelamI(val, level + 1);
    return 0;
}

template <class T>
void TreeNode<T>::preorder(std::stringstream &ss) const {
    ss << value << " ";
    if (left != nullptr) left->preorder(ss);
    if (right != nullptr) right->preorder(ss);
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &ss) const {
    if (left != nullptr) left->inorder(ss);
    ss << value << " ";
    if (right != nullptr) right->inorder(ss);
}

template <class T>
void TreeNode<T>::postorder(std::stringstream &ss) const {
    if (left != nullptr) left->postorder(ss);
    if (right != nullptr) right->postorder(ss);
    ss << value << " ";
}

template <class T>
void TreeNode<T>::levelorder(std::stringstream &ss) const {
    std::queue<const TreeNode<T>*> q;
    q.push(this);
    while (!q.empty()) {
        const TreeNode<T>* node = q.front();
        q.pop();
        ss << node->value << " ";
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
    }
}


// ================= BST ===================

template <class T>
class BST {
private:
    TreeNode<T>* root;

public:
    BST();
    bool empty() const;
    void add(T);
    int height() const;
    std::string visit() const;
    std::string ancestors(T) const;
    int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(nullptr) {}

template <class T>
bool BST<T>::empty() const {
    return root == nullptr;
}

template <class T>
void BST<T>::add(T val) {
    if (root == nullptr)
        root = new TreeNode<T>(val);
    else
        root->add(val);
}

template <class T>
int BST<T>::height() const {
    if (root == nullptr)
        return 0;
    return root->height();
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream ss;
    if (root == nullptr) return "";

    std::stringstream pre, in, post, lvl;
    root->preorder(pre);
    root->inorder(in);
    root->postorder(post);
    root->levelorder(lvl);

    ss << "[" << pre.str().substr(0, pre.str().size() - 1) << "]\n";
    ss << "[" << in.str().substr(0, in.str().size() - 1) << "]\n";
    ss << "[" << post.str().substr(0, post.str().size() - 1) << "]\n";
    ss << "[" << lvl.str().substr(0, lvl.str().size() - 1) << "]";
    return ss.str();
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream ss;
    ss << "[";
    if (root != nullptr) {
        std::stringstream temp;
        if (root->ancestors(val, temp)) {
            // Revertir el orden de los ancestros (de child-to-root a root-to-child)
            std::vector<T> ancestorsList;
            T ancestor;
            while (temp >> ancestor) {
                ancestorsList.push_back(ancestor);
            }
            // Imprimir en orden inverso
            for (int i = ancestorsList.size() - 1; i >= 0; i--) {
                ss << ancestorsList[i];
                if (i > 0) ss << " ";
            }
        }
    }
    ss << "]";
    return ss.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    if (root == nullptr)
        return 0;
    return root->whatlevelamI(val, 1);
}

#endif
