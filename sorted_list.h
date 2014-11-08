// Despa Diana-Alexandra 311CA

#ifndef __SORTEDLIST__H
#define __SORTEDLIST__H

#include "list.h"

template <typename T>
class SortedLinkedList: public LinkedList<T>
{
	public:
		
		/*Adauga un element x de tip T la lista, astfel incat lista sa fie 
		ordonata*/
		void addElement(T x)
		{
			struct Node<T> *p, *paux;
			
			if (this->pFirst == NULL || this->pFirst->value > x) {
				addFirst(x);
				return;
			}
			
			if (this->pLast->value < x) {
				addLast(x);
				return;
			}
			
			p = this->pFirst;
			while (p != NULL && p->value < x)
				p = p->next;
			if (p == NULL) {
				return;
			}
			
			if (p->value > x) {
				paux = new struct Node<T>;
				paux->value = x;
				paux->prev = p->prev;
				p->prev->next = paux;
				p->prev = paux;
				paux->next = p;
			}
		}
		
		/*Constructorul este acelasi ca cel din clasa "LinkedList"*/
		SortedLinkedList(): LinkedList<T>() {}
};

#endif
