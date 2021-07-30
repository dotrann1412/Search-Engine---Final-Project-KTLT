#ifndef _LinkedList_H
#define _LinkedList_H

struct Node
{
	char* data;
	int index;
	Node* next;
	Node* prev;
};

struct LinkedList
{
	Node* head;
	Node* tail;
	int size;
};

void initialize(LinkedList& list);

bool isEmpty(LinkedList& list);

Node* newNode(char* data, int index, Node* next, Node* prev);

void addHead(LinkedList& list, char* data, int index);

void addTail(LinkedList& list, char* data, int index);

void removeHead(LinkedList& list);

void removeTail(LinkedList& list);

void removeI(LinkedList& list, Node* x);

void removeAll(LinkedList& list);

#endif