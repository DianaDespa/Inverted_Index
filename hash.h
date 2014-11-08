// Despa Diana-Alexandra 311CA

#ifndef __HASH__H
#define __HASH__H

/** Functia de hash */
unsigned int hashFunction(std::string key)
{
	unsigned int hash = 5381;

	for (unsigned i=0;i<key.size();i++)
		hash = ((hash << 5) + hash) + (int)key[i];

	return hash;
}

#endif
