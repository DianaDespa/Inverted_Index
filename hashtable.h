// Despa Diana-Alexandra 311CA

#ifndef __HASHTABLE__H
#define __HASHTABLE__H

#include "list.h"
#include "sorted_list.h"

// factor de incarcare
#define RATIO 0.7
 
template<typename Tk, typename Tv> class elem_info {
	public:
		Tk key;
		SortedLinkedList<Tv> *value;

		// supraincarcarea operatorului de atribuire
		void operator=(const elem_info& x)
		{
			key = x.key;
			value = x.value;
		}
};

template<typename Tkey, typename Tvalue> class Hashtable {
	private:
		LinkedList<elem_info<Tkey, Tvalue> > *H;
		int HMAX, size;
		unsigned int (*hash) (Tkey);

	public:
		
		//Constructor cu parametri
		Hashtable(int hmax, unsigned int (*h)(Tkey))
		{
			HMAX = hmax;
			hash = h;
			size = 0;
			H = new LinkedList<elem_info<Tkey, Tvalue> >[HMAX];
		}
		
		//Constructor fara parametri
		Hashtable()
		{
			;
		}
		
		//Destructor
		~Hashtable()
		{
			for (int i=0; i< HMAX; i++){
				//Se golesc toate listele din hashtable
				while (!H[i].isEmpty()) {
					//Se dezaloca memoria pentru listele de cuvinte 
					delete H[i].pFirst->value.value;
					H[i].removeFirst();
				}
			}
			delete []H;
		}
		
		// Adauga site-ul (value) cu o anumita cheie (key) la hashtable
 		void put(Tkey key, Tvalue value)
 		{
 			if (!hasKey(key)) {
 				size++;
 				
 				/** Daca factorul de incarcare este depasit, se redimensioneaza
 				hashtable-ul. */
 				if ((float)size / HMAX > RATIO) 
 					resize();
 			}
 			
 			struct Node<elem_info<Tkey, Tvalue> > *p;
            SortedLinkedList<Tvalue> *list;
			
			unsigned int hkey = hash(key) % HMAX;
			p = H[hkey].pFirst;
			
			// Se verifica daca si unde se afla cheia in hashtable.
			while (p != NULL) {
				if (p->value.key == key)
					break;	
				p = p->next;
			}
			
            // Daca exista cheia, site-ul se adauga la lista corespunzatoare    		
			if (p != NULL) {
				list = p->value.value;
				list->addElement(value);
				p->value.value = list;
			}
			
			/** Altfel, se adauga cheia in hashtable, cu lista care ii 
			corespunde formata dintr-un singur site */ 
			else {
				elem_info<Tkey, Tvalue> info;
				list = new SortedLinkedList<Tvalue>;
				list->addFirst(value);
				info.key = key;
				info.value = list;
				H[hkey].addLast(info);
			}
		}
		
		// Intoarce lista de site-uri de la cheia key
		SortedLinkedList<Tvalue> *get(Tkey key)
		{
			struct Node<elem_info<Tkey, Tvalue> > *p;
			unsigned int hkey = hash(key) % HMAX;
			p = H[hkey].pFirst;
			
			while (p != NULL){
				if (p->value.key == key)
					break;
				p = p->next;
			}
			
			if (p != NULL)
				return p->value.value;
			else
				return NULL;
		}
		
		// Verifica daca exista cheia key in hashtable
		bool hasKey(Tkey key)
		{
			struct Node<elem_info<Tkey, Tvalue> > *p;

			unsigned int hkey = hash(key) % HMAX;
			p = H[hkey].pFirst;

			while (p != NULL) {
				if (p->value.key == key)
					break;
				p = p->next;
			}

			return (p != NULL);
		}
		
		// Verifica daca exista site-ul value in lista cheii key
		bool hasValue(Tkey key, Tvalue value) 
		{
			SortedLinkedList<Tvalue> *list = get(key);
			if (list != NULL) {
				Node<Tvalue> *p = list->pFirst;
				while (p != NULL) {
					if (p->value == value) 
						return 1;
					p = p->next;
				}
				return 0;
			}
			return 0;
		}
		
		// Redimensioneaza hashtable-ul
		void resize()
		{
			struct Node<elem_info<Tkey, Tvalue> > *p;
			
			HMAX = HMAX * 2;
			
			LinkedList <elem_info<Tkey, Tvalue> > *temp;
			temp = new LinkedList<elem_info<Tkey, Tvalue> > [HMAX];
			elem_info<Tkey, Tvalue> info;
			unsigned int hkey;
			
			/** Se copiaza toate elementele hashtable-ului H intr-un hashtable 
			temporat temp, avand grija ca ele sa fie inserate pe pozitiile 
			corespunzatoare cu noua valoare a lui HMAX. */
			
			for (int i = 0; i < HMAX / 2; i++) {
				p = H[i].pFirst;
				while (p != NULL) {
					hkey = hash(p->value.key) % HMAX;
					info.key = p->value.key;
					info.value = p->value.value;
					temp[hkey].addLast(info);
					p = p->next;
				}
			}
			
			// H este inlocuit cu temp
			delete []H;
			H = temp;
		}
};
 
#endif
