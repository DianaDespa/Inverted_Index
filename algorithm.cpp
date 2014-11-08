// Despa Diana-Alexandra 311CA

#include <string>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "hash.h"
#include "algorithm.h"

// capacitate initiala de intrari pentru hashtable
#define VMAX 10

using namespace std;

/** Functia "intersect" intoarce lista rezultata in urma intersectiei 
elementelor celor doua liste ale caror adrese sunt date ca parametrii.*/

SortedLinkedList<std::string> intersect(SortedLinkedList<std::string> *l1, 
										SortedLinkedList<std::string> *l2)
{
	Node<std::string> *p1, *p2;
	SortedLinkedList<std::string> list;
	p1 = l1->pFirst;
	p2 = l2->pFirst;
	
	while (p1 != NULL && p2 != NULL) {
		if (p1->value < p2->value) {
			p1 = p1->next;
		} else if (p1->value > p2->value) {
			p2 = p2->next;
		} else {
		/** Daca se gaseste un element comun, el este adaugat la lista ce 
		reprezinta intersectia. */
			list.addLast(p1->value);
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return list;
}

Algorithm::Algorithm(void)
	: inv_index(VMAX, hashFunction)
{	
}

Algorithm::~Algorithm(void)
{
}


void Algorithm::indexSite(const std::string &row)
{
	char *row_tok = strdup(row.c_str());
	char *command = strtok(row_tok," ");
	if (strcmp(command,"PUT") != 0)
	{
		free(row_tok);
		return;
	}
	
	char *site = strtok(NULL," ");
	char *word = strtok(NULL," ");
	while (word)
	{
		/** Se adauga site-ul la hashtable, avand drept cheie un cuvant. */
		inv_index.put(word, site);
		word = strtok(NULL," ");
	}
	free(row_tok);
}

void Algorithm::getSites(const std::string &row)
{
	char *row_tok = strdup(row.c_str());
	char *command = strtok(row_tok," ");
	if (strcmp(command,"GET") != 0)
	{
		free(row_tok);
		return;
	}
	
	char *word = strtok(NULL," ");
	SortedLinkedList<std::string> *l1, *l2, aux;
	struct Node<std::string> *p;
	
	/** l1 si l2 retin adresele listelor de site-uri din hashtable care au 
	drept chei cuvintele din interogare. */
	l1 = inv_index.get(word);
	
	/** Daca una dintre liste este vida, nu mai are sens intersectia. */
	if (l1 == NULL) {
		cout << "SITE_NOT_FOUND\n";
		free(row_tok);
		return;
	}
	
	word = strtok(NULL," ");
	while (word)
	{
		l2 = inv_index.get(word);
		
		/** Se iau in considerare si cazurile in care ultimul element al primei
		liste este strict mai mic decat primul element al celei de-a doua sau 
		primul element al primei liste este strict mai mare decat ultimul 
		element al celei de-a doua. Astfel, listele sunt disjuncte, deci 
		intersectia lor este vida. */
		
		if (l2 == NULL || l1->pLast->value < l2->pFirst->value || 
			l2->pLast->value < l1->pFirst->value) {
			cout << "SITE_NOT_FOUND\n";
			free(row_tok);
			return;
		}
		
		aux = intersect(l1, l2);
		
		/** Daca intersectia este vida, inseamna ca nu a fost gasit un site 
		care sa contina toti termenii interogarii. */
		if (aux.isEmpty()) {
			cout << "SITE_NOT_FOUND\n";
			free(row_tok);
			return;
		}
		word = strtok(NULL," ");
		
		l1 = &aux;
	}
	
	p = l1->pFirst;
	while (p != NULL) {
		cout << p->value << " ";
		p = p->next;
	}
	
	cout << endl;
	free(row_tok);
}

void Algorithm::wordInSite(const std::string &row)
{
	char *row_tok = strdup(row.c_str());
	char *command = strtok(row_tok," ");
	if (strcmp(command,"SITE") != 0)
	{
		free(row_tok);
		return;
	}
	
	char *site = strtok(NULL," ");
	char *word = strtok(NULL," ");
	bool found = 1;
	
	/** Se parseaza interogarea cat timp site-ul se gaseste la cheia word. */
	while (word && found)
	{
		found = inv_index.hasValue(word, site);
		word = strtok(NULL," ");
	}
	
	if (found)
		cout << "WORD_FOUND";
	else
		cout << "WORD_NOT_FOUND";
	cout << endl;
	free(row_tok);
}

void Algorithm::resolve()
{
	string row;
	while ( std::cin.good() )
	{
		std::getline(std::cin,row);
		//nu iau in considerare linii cu mai putin de 3 caractere
		if (row.size() < 3)
			continue;
		switch(row[0])
		{
		//PUT
		case 'P':
			indexSite(row);
			break;
		//GET
		case 'G':
			getSites(row);
			break;
		//SITE
		case 'S':
			wordInSite(row);
			break;
		default:
			cout << "Invalid option" << endl;
		}
	}
}
