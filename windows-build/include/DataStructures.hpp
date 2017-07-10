/*My personal project of a library that includes different types of template container structures.
  Basically a rework of C++'s  STL.

  It is an open source project and so if you feel like contributing to it(testing, fixing and/or adding new stuff) just send me an
  email with the subject "data structures gist contribution" listing what you did or want to do and I'll have it added with due
  credit (just check my profile for the email address).

  Biblioteca criada para o uso de diferentes tipos abstratos de dados dinâmicos,
  partindo do conceito de listas encadeadas para posterior reuso em projetos.

  Classes implementadas e testadas até a última revisão:
  Node
  Stack
  Queue
  LinkedList

  Classes ainda não testadas:
  KeyNode
  BSTree
  AVLTree

  Classes a implementar:
  PriorityQueue
  RBTree
  BTree

  Gabriel Alves,
  São Carlos - SP, 2017.
*/

#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

template<class T>
class Node {
public:
	T value;
	Node* next;
	Node* previous;
	Node() :next(this), previous(this) {};
	Node(const T val) : value(val), next(this), previous(next) {};
	~Node() { next = nullptr; previous = nullptr; }
};

template<class T>
class Stack {
protected:
	Node<T> header;
	int size;

public:
	Stack() :size(0) {};
	~Stack() { this->clear(); };

	void push(const T, bool&);
	bool pop(T&);

	bool isEmpty() const { return (header.next == &header) ? true : false; };
	int getSize() const { return this->size; };
	Node<T>* peek() const { return this->header.next; };

	void clear();

};

template<class T>
void Stack<T>::push(const T element, bool& check) {
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->next = &header;
	aux->previous = header.previous;
	header.previous->next = aux;
	header.previous = aux;
	size++;
	check = true;
}

template<class T>
bool Stack<T>::pop(T& element) {
	if (!this->isEmpty()) {
		element = header.previous->value;
		Node<T> *aux = header.previous;
		header.previous = aux->previous;
		aux->previous = &header;
		delete(aux);
		size--;
		return true;
	}
	return false;
}

template<class T>
inline void Stack<T>::clear() {
	T temp;
	while (this->pop(temp));
}

template<class T>
class Queue {
private:
	Node<T> header;
	int size;

public:
	Queue() :size(0) {};
	~Queue() { this->clear(); };

	void enqueue(const T, bool&);
	bool dequeue(T&);

	bool isEmpty() const { bool check = (header.next == &header) ? true : false; return check; };
	int getSize() const { return this->size; };
	Node<T>* getFront() const { return this->header.next; };
	Node<T>* getBack() const { return this->header.previous; };

	T operator[](int);

	void clear();

};

template<class T>
void Queue<T>::enqueue(const T element, bool& check) {
	check = false;
	Node<T> *aux = new Node<T>;
	aux->value = element;
	aux->next = &header;
	aux->previous = header.previous;
	header.previous->next = aux;
	header.previous = aux;
	size++;
	check = true;
}


template<class T>
bool Queue<T>::dequeue(T& element) {
	if (!this->isEmpty()) {
		element = header.next->value;
		Node<T>* aux = header.next;
		header.next = aux->next;
		aux->next->previous = &header;
		delete aux;
		size--;
		return true;
	}
	return false;
}

template<class T>
void Queue<T>::clear() {
	T temp;
	while (this->dequeue(temp));
}

template<class T>
T Queue<T>::operator[](int index) {
	Node<T>* temp = this->getFront();
	while (index > 0 && temp != this->getBack()){
		temp = temp->next;
		index--;
	}
	return temp->value;
}

template<class T>
class LinkedList {

private:
	Node<T> header;
	Node<T>* current;
	int size;

public:
	LinkedList() : current(&this->header), size(0) {};
	~LinkedList() { this->clear(); }

	bool toFirst(); // retorna verdadeiro se a lista estiver vazia.
	bool toNext(); // retorna verdadeiro se passar para o último elemento da lista.

	bool isEmpty() const { return (this->header.next == &this->header) ? true : false; };

	void insertItem(T);
	void getCurrent(T& element) { element = this->current->value; };
	bool find(T);
	void removeCurrent();
	int getSize() const { return this->size; };

	void clear();

	T operator[](int);

};

template<class T>
bool LinkedList<T>::toFirst() {
	this->current = this->header.next;
	return this->current == &this->header;
}

template<class T>
bool LinkedList<T>::toNext() {
	if (!this->isEmpty()) {
		this->current = this->current->next;
		if (this->current == &this->header){
			this->current = this->current->next;
		}
	}
	return this->current->next == &this->header;
}

template<class T>
void LinkedList<T>::insertItem(T element) {
	Node<T>* newNode = new Node<T>;
	newNode->value = element;
	newNode->next = this->current->next;
	newNode->previous = this->current;
	newNode->next->previous = newNode;
	this->current->next = newNode;
	this->toNext();
	this->size++;
}

template<class T>
void LinkedList<T>::removeCurrent() {
	if (!this->isEmpty()) {
		Node<T>* aux = this->current;
		aux->previous->next = aux->next;
		aux->next->previous = aux->previous;
		this->current = aux->previous;
		delete aux;
		this->size--;
	}
}

template<class T>
bool LinkedList<T>::find(T element) {
	this->toFirst();

	while (this->current->value != element)
		this->toNext();

	if (this->current->value == element){
		return true;
	}
	return false;

}

template<class T>
void LinkedList<T>::clear() {
	this->toFirst();
	while (!this->toNext())
		this->removeCurrent();
}

template<class T>
T LinkedList<T>::operator[](int index) {
	this->toFirst();
	while (index > 0 && !this->toNext())
		index--;
	return this->current->value;
}

template<class T>
class KeyNode {
public:
	int key;
	T data;
	KeyNode* right;
	KeyNode* left;

	KeyNode() :right(this), left(this) {};
	KeyNode(const T val, int keyVal) : data(val), key(keyVal), right(this), left(right) {};
	KeyNode(const KeyNode<T>&);
	~KeyNode() { right = nullptr; left = nullptr; }
};

template<class T>
KeyNode<T>::KeyNode(const KeyNode<T>& copyNode) {
	this->key = copyNode->key;
	this->data = copyNode->data;
	this->right = copyNode->right;
	this->left = copyNode->left;
}

template<class T>
class BSTree {
protected:
	KeyNode<T>* root;

	void insert(KeyNode<T>*, int, T, bool&);
	KeyNode<T>* find(KeyNode<T>*, int) const;
	void remove(KeyNode<T>*, bool&);

public:
	BSTree() : root(nullptr) {};
	~BSTree() { this->purge(root); };

	void insert(int, T, bool&);
	KeyNode<T>* find(int) const;
	void remove(int, bool&);

	bool isEmpty() const { return (this->root == nullptr) ? true : false; };
	KeyNode<T>* getMax(KeyNode<T>*) const;
	KeyNode<T>* getMin(KeyNode<T>*) const;

	void purge(KeyNode<T>*);

};

template<class T>
void BSTree<T>::insert(int key, T data, bool& ok) {
	insert(this->root, key, data, ok);
}

template<class T>
void BSTree<T>::insert(KeyNode<T>* leaf, int key, T data, bool& ok) {
	if (leaf == nullptr) {
		leaf = new KeyNode<T>;
		leaf->key = key;
		leaf->data = data;
		leaf->right = nullptr;
		leaf->left = nullptr;
		ok = true;
	}
	else if (key == leaf->key){
		ok = false;
	}else if (key > leaf->key){
		insert(leaf->right, key, data, ok);
	}else if (key < leaf->key){
		insert(leaf->left, key, data, ok);
	}
}

template<class T>
KeyNode<T>* BSTree<T>::find(int key) const {
	return find(this->root, key);
}

template<class T>
KeyNode<T>* BSTree<T>::find(KeyNode<T>* leaf, int key) const {
	if (leaf == nullptr){
		return nullptr;
	}else if (key == leaf->key){
		return leaf;
	}else if (key < leaf->key){
		return find(leaf->left, key);
	}else if (key > leaf->key){
		return find(leaf->right, key);
	}
}

template<class T>
KeyNode<T>* BSTree<T>::getMax(KeyNode<T>* leaf) const {
	if (leaf->right == nullptr){
		return leaf->right;
	}else{
		return getMax(leaf->right);
	}
}

template<class T>
KeyNode<T>* BSTree<T>::getMin(KeyNode<T>* leaf) const {
	if (leaf->left == nullptr){
		return leaf->left;
	}else{
		return getMin(leaf->left);
	}
}

template<class T>
void BSTree<T>::remove(int key, bool& ok) {
	ok = false;

	if ((!this->isEmpty()) && (this->find(root, key) != nullptr)){
		this->remove(find(root, key), ok);
	}
}

template<class T>
void BSTree<T>::remove(KeyNode<T>* leaf, bool& ok) {
	//Case 1: leaf node
	if (leaf->right == nullptr && leaf->left == nullptr) {
		delete leaf;
	}

	//Case 2: branch node with 1 leaf node
	else if (leaf->right == nullptr) {
		KeyNode<T>* aux = leaf;
		leaf = leaf->left;
		delete aux;
	}
	else if (leaf->left == nullptr) {
		KeyNode<T>* aux = leaf;
		leaf = leaf->right;
		delete aux;
	}

	//Case 3: branch node with 2 leaf nodes
	else {
		KeyNode<T>* aux = getMax(leaf->left);
		leaf->key = aux->key;
		leaf->data = aux->data;
		delete aux;
	}

	ok = true;
}

template<class T>
void BSTree<T>::purge(KeyNode<T>* leaf) {
	if(!this->isEmpty()){
		if (leaf->left != nullptr){
			purge(leaf->left);
		}

		if (leaf->right != nullptr){
			purge(leaf->right);
		}

		delete leaf;
	}
}

template<class T>
class AVLTree {
private:
	KeyNode<T>* root;

	void rebalance_ins(KeyNode<T>*);
	void rebalance_rem(KeyNode<T>*);

	void rotateLL(KeyNode<T>*, KeyNode<T>*);
	void rotateRR(KeyNode<T>*, KeyNode<T>*);
	void rotateRL(KeyNode<T>*, KeyNode<T>*, KeyNode<T>*);
	void rotateLR(KeyNode<T>*, KeyNode<T>*, KeyNode<T>*);

	KeyNode<T>* find(KeyNode<T>*, int) const;
	void insert(KeyNode<T>*, int, T, bool&);
	void remove(KeyNode<T>*, bool&);

public:
	AVLTree() : root(nullptr) {};
	~AVLTree() { this->purge(root); };

	int getHeight(KeyNode<T>*) const;
	int getBF(KeyNode<T>* subtree) const { return getHeight(subtree->right) - getHeight(subtree->left); }

	KeyNode<T>* getParentNode(KeyNode<T>*, int) const;
	KeyNode<T>* getMax(KeyNode<T>*) const;
	KeyNode<T>* getMin(KeyNode<T>*) const;

	bool isBalanced(KeyNode<T>*) const;
	bool isEmpty() const { return (this->root == nullptr) ? true : false; };

	KeyNode<T>* find(int) const;
	void insert(int, T, bool&);
	void remove(int, bool&);

	void purge(KeyNode<T>*);

};

template<class T>
int AVLTree<T>::getHeight(KeyNode<T>* subtree) const {
	// Case 1: empty subtree

	if (subtree == nullptr){
		return 0;
	}

	//Case 2: height equals to 1 + greatest value between left and right branches

	int maxHeight = (getHeight(subtree->left) >= getHeight(subtree->right)) ? getHeight(subtree->left) : getHeight(subtree->right);

	return 1 + maxHeight;
}

template<class T>
KeyNode<T>* AVLTree<T>::getParentNode(KeyNode<T>* leaf, int childkey) const{
	//Searches for leaf node's parent, considering the leaf node is already in the tree

	if (childkey != this->root->key) {
		if (childkey == leaf->left->key || childkey == leaf->right->key){
			return leaf;
		}else{
			if (childkey > leaf->key){
				return getParentNode(leaf->right, childkey);
			}	else if (childkey < leaf->key){
				return getParentNode(leaf->left, childkey);
			}
		}
	}

	return nullptr;
}

template<class T>
KeyNode<T>* AVLTree<T>::getMax(KeyNode<T>* leaf) const {
	if (leaf->right == nullptr){
		return leaf->right;
	}else{
		return getMax(leaf->right);
	}
}

template<class T>
KeyNode<T>* AVLTree<T>::getMin(KeyNode<T>* leaf) const {
	if (leaf->left == nullptr){
		return leaf->left;
	}else{
		return getMin(leaf->left);
	}
}

template<class T>
bool AVLTree<T>::isBalanced(KeyNode<T>* subtree) const{
	if (subtree == nullptr){
		return true;
	}else{
		if (getBF(subtree) < -1 || getBF(subtree) > 1){
			return false;
		}
		return isBalanced(subtree->right) && isBalanced(subtree->left);
	}
}

template<class T>
void AVLTree<T>::rotateLL(KeyNode<T>* x, KeyNode<T>* y) {
	x->left = y->right;
	y->right = x;
}

template<class T>
void AVLTree<T>::rotateRR(KeyNode<T>* x, KeyNode<T>* y) {
	x->right = y->left;
	y->left = x;
}

template<class T>
void AVLTree<T>::rotateLR(KeyNode<T>* x, KeyNode<T>* y, KeyNode<T>* z) {
	this->rotateRR(y, z);
	this->rotateLL(x, z);
}

template<class T>
void AVLTree<T>::rotateRL(KeyNode<T>* x, KeyNode<T>* y, KeyNode<T>* z) {
	this->rotateLL(y, z);
	this->rotateRR(x, z);
}

template<class T>
void AVLTree<T>::rebalance_ins(KeyNode<T>* leaf) {
	//Proceed to check if the tree has been unbalanced
	if (!isBalanced(this->root)) {
		//If it is, search for the first unbalanced node from the bottom node "leaf"
		KeyNode<T>* BalNode = getParentNode(this->root, leaf->key);
		KeyNode<T>* tempX = leaf;
		KeyNode<T>* tempY;

		//The other 2 temp nodes will be used in the coming rotation cases
		while (isBalanced(BalNode) && getParentNode(this->root, BalNode->key) != nullptr) {
			tempY = tempX;
			tempX = BalNode;
			BalNode = getParentNode(this->root, BalNode->key);
		}
		//Check which of the rotation cases will be needed and rotate the nodes
			//Case 1: Left-Left Rotation
			if (BalNode->left == tempX && tempX->left == tempY){
				this->rotateLL(BalNode, tempX);
			}

			//Case 2: Right-Right Rotation
			else if (BalNode->right == tempX && tempX->right == tempY){
				this->rotateRR(BalNode, tempX);
			}

			//Case 3: Left-Right Rotation
			else if (BalNode->left == tempX && tempX->right == tempY){
				this->rotateLR(BalNode, tempX, tempY);
			}

			//Case 4: Right-Left Rotation
			else if (BalNode->right == tempX && tempX->left == tempY){
				this->rotateRL(BalNode, tempX, tempY);
			}
	}
}

template<class T>
void AVLTree<T>::rebalance_rem(KeyNode<T>* BalNode){
	//Check if the tree is unbalanced
	if (!isBalanced(this->root)) {
		//If it is, search for the first unbalanced node from the parent of the one that was removed
		while (isBalanced(BalNode) && getParentNode(this->root, BalNode->key) != nullptr)
			BalNode = getParentNode(this->root, BalNode->key);
		//Now find another 2 nodes from the tallest subtree
		KeyNode<T>* tempX = (getHeight(BalNode->left) > getHeight(BalNode->right)) ? BalNode->left : BalNode->right;
		KeyNode<T>* tempY = (getHeight(tempX->left) > getHeight(tempX->right)) ? tempX->left : tempX->right;
		//Check which of the rotation cases will be needed and rotate the nodes
			//Case 1: Left-Left Rotation
			if (BalNode->left == tempX && tempX->left == tempY){
				this->rotateLL(BalNode, tempX);
			}

			//Case 2: Right-Right Rotation
			else if (BalNode->right == tempX && tempX->right == tempY){
				this->rotateRR(BalNode, tempX);
			}

			//Case 3: Left-Right Rotation
			else if (BalNode->left == tempX && tempX->right == tempY){
				this->rotateLR(BalNode, tempX, tempY);
			}

			//Case 4: Right-Left Rotation
			else if (BalNode->right == tempX && tempX->left == tempY){
				this->rotateRL(BalNode, tempX, tempY);
			}

	}
}

template<class T>
KeyNode<T>* AVLTree<T>::find(int key) const {
	return find(this->root, key);
}

template<class T>
KeyNode<T>* AVLTree<T>::find(KeyNode<T>* leaf, int key) const {
	if (leaf == nullptr){
		return nullptr;
	}else if (key == leaf->key){
		return leaf;
	}else if (key < leaf->key){
		return find(leaf->left, key);
	}else if (key > leaf->key){
		return find(leaf->right, key);
	}
}

template<class T>
void AVLTree<T>::insert(int key, T data, bool& ok) {
	insert(this->root, key, data, ok);
}

template<class T>
void AVLTree<T>::insert(KeyNode<T>* leaf, int key, T data, bool& ok){
	//Same insertion procedure as the unbalanced version
	if (leaf == nullptr) {
		leaf = new KeyNode<T>;
		leaf->key = key;
		leaf->data = data;
		leaf->right = nullptr;
		leaf->left = nullptr;
		ok = true;
	}
	else if (key == leaf->key){
		ok = false;
	}else if (key > leaf->key){
		insert(leaf->right, key, data, ok);
	}else if (key < leaf->key){
		insert(leaf->left, key, data, ok);
	}

	//If insertion is successful, check if tree needs balancing
	if (ok){
		this->rebalance_ins(leaf);
	}
}

template<class T>
void AVLTree<T>::remove(int key, bool& ok) {
	ok = false;

	if ((!this->isEmpty()) && (this->find(root, key) != nullptr)){
		this->remove(find(root, key), ok);
	}
}

template<class T>
void AVLTree<T>::remove(KeyNode<T>* leaf, bool& ok) {
	KeyNode<T>* pNode;

	//Case 1: leaf node
	if (leaf->right == nullptr && leaf->left == nullptr) {
		pNode = getParentNode(this->root, leaf->key);
		delete leaf;
	}

	//Case 2: branch node with 1 leaf node
	else if (leaf->right == nullptr) {
		KeyNode<T>* aux = leaf;
		leaf = leaf->left;
		pNode = getParentNode(this->root, aux->key);
		delete aux;
	}
	else if (leaf->left == nullptr) {
		KeyNode<T>* aux = leaf;
		leaf = leaf->right;
		pNode = getParentNode(this->root, aux->key);
		delete aux;
	}

	//Case 3: branch node with 2 leaf nodes
	else {
		KeyNode<T>* aux = getMax(leaf->left);
		leaf->key = aux->key;
		leaf->data = aux->data;
		remove(aux, ok);
	}

	if (this->isEmpty()){
		ok = true;
	} else {
		//After removal, not only the parent node may be unbalanced, but the ancestors too
		if (pNode != nullptr) {
			do {
				this->rebalance_rem(pNode);
				pNode = getParentNode(this->root, pNode->key);
			} while (!this->isBalanced(root));
		}
		ok = true;
	}
}

template<class T>
void AVLTree<T>::purge(KeyNode<T>* leaf) {
	if (!this->isEmpty()) {
		if (leaf->left != nullptr){
			purge(leaf->left);
		}

		if (leaf->right != nullptr){
			purge(leaf->right);
		}

		delete leaf;
	}
}

template<class T>
class PriorityQueue {};

template<class T>
class RBTree {};

template<class T>
class BTree{};

#endif
