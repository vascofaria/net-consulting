/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * NetBreaks.cpp
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */

#include "NetBreaks.h"

int netBreaks(Graph* graph, net_t* net) {
	int breakersNumber=0;
	for (int v=0; v < graph->getV(); v++)
		attackRouter(graph, v, net, &breakersNumber);
	return breakersNumber;
}

void attackRouter(Graph* graph,  int u, net_t* net, int* breakersNumber) {

	net_t* trial_net = new net_t();
	std::vector<int> affectedVertex;
	affectedVertex.push_back(u);
	scc_tarjan(graph, trial_net, &affectedVertex);

	if (trial_net->subnetsNumber > net->subnetsNumber) {
		net->breakersVertices.push_back(u);
		(*breakersNumber)++;
	}

	delete trial_net;
}

int biggestNet(Graph* graph, net_t* net) {
	net_t* trial_net = new net_t();
	scc_tarjan(graph, trial_net, &net->breakersVertices);
	int maxRoutersNumber = trial_net->maxRoutersNumber;
	delete trial_net;
	return maxRoutersNumber;
}

/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of NetBreaks.cpp
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
