/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * Graph.h
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Bruno Meira and Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */


#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Net.h"

class Graph {
private:
	int _v;
	int _e=0;
	std::vector<int>* _edges;

public:
/* »»»»»»»»»»»»»»»»»»»»»»»»»»»»»» CONSTRUCTOR «««««««««««««««««««««««««««««««««««« */
	Graph(int v);

/* »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»» DESTRUCTOR «««««««««««««««««««««««««««««««««««« */
	~Graph();

/* »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»» GETTERS «««««««««««««««««««««««««««««««««««««« */
	int getE() const;
	int getV() const;
	std::vector<int>* getAdjacencies(int v) const;

/* »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»» FUNCTIONS ««««««««««««««««««««««««««««««««««««« */
	void addEdge(int source, int destination);

};

#endif /* GRAPH_H */

/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of Graph.h
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
