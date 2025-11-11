#pragma once
#ifndef LinkedList_h
#define LinkedList_h


template <typename T>
struct Node {
	T* data;
	Node* next = nullptr;
	unsigned int position;
};


template <typename T>
class LinkedList {

private:

	Node* Head<T> = nullptr;
	Node* Tail<T> = nullptr;

	size_t ElementSize = 0;

	unsigned int elementCount = 0;
	int maxElementCount = 0;

	unsigned int memoryUsed = 0;
	unsigned int capacity = 0;

	void Update() {

		Node<T>* startingPoint = Head;
		int newElementCount = 0;

		for (;;) {

			newElementCount++;

			if (startingPoint->next == nullptr) break;
			startingPoint = startingPoint->next;
		}


		elementCount = newElementCount;
	}

public:

	LinkedList(int maxElements, int capacity) {
		
		elementSize = sizeof(Node<T>);
		capacity = (maxElements * elementSize) + capacity;

		Node<T>* newNode = new Node<T>;
		Head = newNode;
		Tail = newNode;

		Update();
	}

	void Insert(int Position, &T data) {
		
	}

	Node<T>* Get(int position) {

	}

};

#endif