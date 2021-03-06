// AVL TREE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

template<class T>
class AVLNode {
public:
	AVLNode() {
		left = right = nullptr;
		balance = 0;
	}
	AVLNode(const T& el, AVLNode *l = nullptr, AVLNode *r = nullptr) {
		key = el; left = l; right = r;
		balance = 0;
	}
	T key;
	AVLNode *left, *right;
	int balance;
};

template<class T>
class AVLTree {
public:
	AVLTree() { root = nullptr; }

	void insert(const T& key) { insert(root, key); }

	void snapShot(std::ostream& out) {
		out << "TreeForm[";
		snapShot(out, root);
		out << "]" << std::endl;
	}
private:
	AVLNode<T>* root;

	void rightRotation(AVLNode<T>* &node) {
		AVLNode<T>* left = node->left;

		node->left = left->right;
		left->right = node;
		node = left;
	}

	void leftRotation(AVLNode<T>* &node) {
		AVLNode<T>* right = node->right;

		node->right = right->left;
		right->left = node;
		node = right;
	}

	bool insert(AVLNode<T>* &node, const T& key) {
		if (node == nullptr) {
			node = new AVLNode<T>(key);
			return true;
		}
		else if (key > node->key) {
			if (insert(node->right, key) == true) {
				node->balance++;
			}
			if (node->balance == 0) {
				return false;
			}
			else if (node->balance == 1) {
				return true;
			}
			else if (node->balance == 2) {
				if (node->right->balance == -1) {
					rightRotation(node->right);
					leftRotation(node);
					if (node->right->right == nullptr) {	// case where we have an even triangle formed
						node->balance = 0;
						node->left->balance = 0;
						node->right->balance = 0;
					}
					else if (node->left->right == nullptr) {	// case where we have more nodes on the right
						node->balance = 1;
						node->left->balance = -1;
						node->right->balance = 0;
					}
					else {									// case where we have more nodes on the left
						node->balance = -1;
						node->left->balance = 0;
						node->right->balance = 1;
					}
				}
				else {
					leftRotation(node);
					node->left->balance = 0;
					node->balance = 0;
				}
				return false;
			}
		}
		else {
			if (insert(node->left, key)) {
				node->balance--;
			}
			if (node->balance == 0) {
				return false;
			}
			else if (node->balance == 1) {
				return true;
			}
			else if (node->balance == 2) {
				if (node->left->balance == -1) {
					leftRotation(node->left);
					rightRotation(node);
					if (node->left->left == nullptr) {
						node->balance = 0;
						node->right->balance = 0;
						node->left->balance = 0;
					}
					else if (node->right->left == nullptr) {
						node->balance = 1;
						node->right->balance = -1;
						node->left->balance = 0;
					}
					else {
						node->balance = -1;
						node->right->balance = 0;
						node->left->balance = 1;
					}
				}
				else {
					rightRotation(node);
					node->right->balance = 0;
					node->balance = 0;
				}
				return false;
			}
		}
	}

	void snapShot(std::ostream& out, AVLNode<T> *p) {
		out << '\"' << p->key << '\"';
		if (p->left != nullptr || p->right != nullptr) {
			out << '[';
			if (p->left == nullptr)
				out << "\"\"";
			else
				snapShot(out, p->left);
			out << ',';
			if (p->right == nullptr)
				out << "\"\"";
			else
				snapShot(out, p->right);
			out << ']';
		}
	}
};

int main() {
	AVLTree<int> x;

	x.insert(12);
	x.insert(8);
	x.insert(6);
	x.insert(10);
	x.insert(14);

	std::ofstream out("tree.txt");
	x.snapShot(out);

	x.insert(16);
	x.snapShot(out);

	out.close();

	return 0;
}


