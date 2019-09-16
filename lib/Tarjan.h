/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * Tarjan.h
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Bruno Meira and Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */


#ifndef TARJAN_H
#define TARJAN_H

#include <limits>
#include <vector>
#include "Graph.h"
#include "Net.h"

#define Min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct tarjan_args tarjan_args_t;

void scc_tarjan(Graph* graph, net_t* net, std::vector<int>* breakersVertices);
void tarjan_visit(Graph* graph, int u, tarjan_args_t* args, net_t* net, std::vector<int>* breakersVertices);

#endif /* TARJAN_H */

/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of Tarjan.h
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
