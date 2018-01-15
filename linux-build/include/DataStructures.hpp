/*
  My personal project of a library that includes different types of template container structures.
  Basically a rework of C++'s  STL.

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

#endif
