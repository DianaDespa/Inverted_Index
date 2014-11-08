// Despa Diana-Alexandra 311CA

#ifndef _ALGORITHM_H
#define _ALGORITHM_H

#include <string>
#include "hashtable.h"

class Algorithm
{
private:
	Hashtable<std::string, std::string> inv_index;
	
public:
	Algorithm(void);
	~Algorithm(void);
	/** Proceseaza o comanda PUT */
	void indexSite(const std::string &row);
	
	/** Proceseaza o comanda GET */
	void getSites(const std::string &row);
	
	/** Proceseaza o comanda SITE */
	void wordInSite(const std::string &row);
	
	/** Proceseaza fiecare comanda primita de la input, pana cand se intalneste EOF */
	void resolve();
};

#endif
