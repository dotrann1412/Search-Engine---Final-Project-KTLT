#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "LinkedList.h"

void initialize(LinkedList& list)
{
	list.head = nullptr;
	list.tail = nullptr;
	list.size = 0;
}

bool isEmpty(LinkedList& list)
{
	return (list.head == nullptr);
}

Node* newNode(char* data, int index, Node* next, Node* prev)
{
	Node* node = new Node;
	node->data = new char[strlen(data) + 1];
	strcpy(node->data, data);
	node->index = index;
	node->next = next;
	node->prev = prev;
	return node;
}

void addHead(LinkedList& list, char* data, int index)
{
	if (isEmpty(list)) {
		Node* addNode = newNode(data, index, nullptr, nullptr);
		list.head = addNode;
		list.tail = addNode;
	}
	else {
		Node* addNode = newNode(data, index, list.head, nullptr);
		list.head->prev = addNode;
		list.head = addNode;
	}
	list.size++;

}

void addTail(LinkedList& list, char* data, int index)
{
	if (isEmpty(list)) {
		Node* adNode = newNode(data, index, list.head, list.tail);
		list.head = adNode;
		list.tail = adNode;
	}
	else {
		Node* adNode = newNode(data, index, nullptr, list.tail);
		list.tail->next = adNode;
		list.tail = adNode;
	}
	list.size++;

}


void removeHead(LinkedList& list)
{
	if (isEmpty(list)) return;
	if (list.head->next == nullptr)
	{
		delete list.head->data;
		delete list.head;
		initialize(list);
		return;
	}

	Node* cur = list.head;
	list.head = list.head->next;
	list.head->prev = nullptr;
	delete cur->data;
	delete cur;
	list.size--;
}

void removeTail(LinkedList& list)
{
	if (isEmpty(list)) return;
	if (list.tail->prev == nullptr)
	{
		delete list.tail->data;
		delete list.tail;
		initialize(list);
		return;
	}

	Node* cur = list.tail;
	list.tail = list.tail->prev;
	list.tail->next = nullptr;
	delete cur->data;
	delete cur;
	list.size--;
}

void removeI(LinkedList& list, Node* x)
{
	if (isEmpty(list)) return;
	if (x->prev == nullptr) {
		removeHead(list);
		return;
	}
	if (x->next == nullptr) {
		removeTail(list);
		return;
	}
	x->prev->next = x->next;
	delete x->data;
	delete x;
	list.size--;
}

void removeAll(LinkedList& list)
{
	if (isEmpty(list)) return;

	Node* cur = list.head;
	while (cur) {
		Node* next = cur->next;
		delete cur->data;
		delete cur;
		cur = next;
	}
	initialize(list);
}
