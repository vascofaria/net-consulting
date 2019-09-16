/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * Tarjan.cpp
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Bruno Meira and Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */

#include "Tarjan.h"

struct tarjan_args {
	int visited = 0;
	int* d;
	int* low;
	std::vector<int> vertices;
};

static int contains(std::vector<int>* vertices, int vertex) {
	for (int v : (*vertices))
		if (v == vertex) return 1;
	return 0;
}

void scc_tarjan(Graph* graph, net* net, std::vector<int>* affectedVertices) {

	tarjan_args_t *args = new tarjan_args_t();
	args->d = new int[graph->getV()];
	args->low = new int[graph->getV()];

	for (int v = 0; v < graph->getV(); v++)
		args->d[v] = std::numeric_limits<int>::max();

	for (int u = 0; u < graph->getV(); u++)
		if (args->d[u] == std::numeric_limits<int>::max() && !contains(affectedVertices, u))
			tarjan_visit(graph, u, args, net, affectedVertices);

	delete[] args->d;
	delete[] args->low;
	delete args;
}

void tarjan_visit(Graph* graph, int u, tarjan_args_t* args, net_t* net, std::vector<int>* affectedVertices) {
	int v = -1;
	int w;

	args->d[u] = args->low[u] = args->visited;
	(args->visited)++;

	(args->vertices).push_back(u);

	std::vector<int>* adjacencyList = graph->getAdjacencies(u);
	for (int v : (*adjacencyList))
		if (!contains(affectedVertices, v))
			if (args->d[v] == std::numeric_limits<int>::max() || contains(&args->vertices, v)) {
				if (args->d[v] == std::numeric_limits<int>::max())
					tarjan_visit(graph, v, args, net, affectedVertices);
				args->low[u] = Min(args->low[u], args->low[v]);
			}

	if (args->d[u] == args->low[u]) {
		if ((args->vertices).size() > net->maxRoutersNumber)
			net->maxRoutersNumber = (args->vertices).size();
		w = v = (args->vertices).back();
		(args->vertices).pop_back();
		while(u != v) {
			v = (args->vertices).back();
			(args->vertices).pop_back();
			if (v > w) w = v;
		}
		net->subnetsIDs.push_back(w+1);
		(net->subnetsNumber)++;
	}
}


/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of Tarjan.cpp
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
