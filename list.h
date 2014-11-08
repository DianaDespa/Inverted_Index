// Despa Diana-Alexandra 311CA

#ifndef __LIST__H
#define __LIST__H

#include <stdio.h>
#include <iostream>
 
template <typename T>
struct Node {
public:

	T value;
	Node<T> *next;
	Node<T> *prev;
};

template <typename T>
class LinkedList{

public:
	Node<T> *pFirst, *pLast;
		
	//Constructor
	LinkedList()
	{		
		pFirst = pLast = NULL;
	}

	//Destructor
	~LinkedList()
	{
		while (!isEmpty()) {
			removeFirst();
		}
	}

	/** Adauga un nod cu valoarea == value la inceputul listei */
	void addFirst(T value)
	{
		Node<T> *paux;
		paux = new Node<T>;
		paux->value = value;
		paux->next = pFirst;
		paux->prev = NULL;
		if (pFirst == NULL)
			pLast = paux;
		else
			pFirst->prev = paux;
		pFirst = paux;
	}

	/** Adauga un nod cu valoarea == value la sfarsitul listei */
	void addLast(T value)
	{	
		Node<T> *paux;
		paux = new Node<T>;
		paux->value = value;
		paux->next = NULL;
		paux->prev = pLast;
		if (pFirst == NULL)
			pFirst = paux;
		else
			pLast->next = paux;
		pLast = paux;
	}

	/** Elimina elementul de la inceputul listei si intoarce valoarea acestuia*/
	T removeFirst()
	{
		T x;
		if (pFirst == NULL){
			printf("Lista e vida!\n");
			return x;
		}
		
		x = pFirst->value;
		if (pFirst == pLast) {
			delete pFirst;
			pFirst = pLast = NULL;
		} else {
			Node<T> *px;
			px = pFirst;
			pFirst->next->prev = NULL;
			pFirst = pFirst->next;
			delete px;
		}
		return x;
	}

	/** Elimina elementul de la sfarsitul listei listei si intoarce valoarea acestuia*/
	T removeLast()
	{
		T x;
		if (pFirst == NULL){
			printf("Lista e vida!\n");
			return x;
		}
		
		x = pLast->value;
		if (pFirst == pLast) {
			delete pFirst;
			pFirst = pLast = NULL;
		} else {
			Node<T> *px;
			px = pLast;
			pLast->prev->next = NULL;
			pLast = pLast->prev;
			delete px;
		}
		return x;
	}
	
	/** Intoarce 1 daca lista este vida, 0 altfel*/
	bool isEmpty()
	{
		return (pFirst == NULL);
	}
	
	/** Supraincarcarea operatorului de atribuire pentru liste */
	void operator=(const LinkedList& list)
	{
		while(!isEmpty())
			removeLast();
		Node<T> *paux = list.pFirst;
		while (paux != NULL) {
			addLast(paux->value);
			paux = paux->next;
		}
	}
};
 
#endif
