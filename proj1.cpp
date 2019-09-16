/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 * IST - ASA 2018/2019
 *
 * proj1.cpp
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Bruno Meira (89421) and Vasco Faria (89559)
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */

#include <iostream>
#include <vector>
#include <list>
#include <limits>

#define UNVISITED 1
#define ONVISIT 	2
#define VISITED 	3

#define NIL -1

#define Min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct net {
	int routers_number;
	int connections_number;
	int sub_nets_number;
	int articulation_routers_number;
	long unsigned int max_routers_number;
	bool* articulation_routers;
	std::list<int>* sub_nets_ids;
	std::vector<int>* connections;
} net_t;

typedef struct analyze_args {
	int  visited;
	int* router_state;
	int* router_predecessor;
	int* router_depth;
	int* router_low;
} analyze_args_t;

typedef struct attack_args {
	int  visited;
	int* depth;
	int* low;
	std::vector<int>* routers;
	bool* inRouters;
} attack_args_t;

int readInt();
void print_results(net_t* net);

void analyze_net(net_t* net);
void visit_net(net_t* net, int router_src, analyze_args_t* args);

void attack_net(net* net);
void attack_router(net_t* net, attack_args_t* args, int router_src);

int main(int argc, char const *argv[]) {
	
	int r_src, r_dst;
	
	net_t* net = new net_t();

	net->routers_number       = readInt();
	net->connections_number   = readInt();

	net->connections          = new std::vector<int>[net->routers_number];
	net->articulation_routers = new bool[net->routers_number];
	net->sub_nets_ids         = new std::list<int>();

	net->sub_nets_number             = 0;
	net->max_routers_number          = 0;
	net->articulation_routers_number = 0;

	for (int connection = 0; connection < net->connections_number; connection++) {
		r_src = readInt();
		r_dst = readInt();
		net->connections[r_src-1].push_back(r_dst-1);
		net->connections[r_dst-1].push_back(r_src-1);
	}

	analyze_net(net);
	attack_net(net);

	print_results(net);

	delete[] net->connections;
	delete[] net->articulation_routers;
	delete   net->sub_nets_ids;
	delete   net;

	return 0;
}

int readInt() {
	int num = 0;
	char c;
	while(((c=getchar()) != '\n') && (c != ' ') && (c != EOF)) {
		if (c < '0' || c > '9') exit(1);
		num *= 10;
		num += (c - '0');
	}
	return num;
}

void print_results(net_t* net) {

	printf("%d\n", net->sub_nets_number);

	long unsigned int router_id;
	std::list<int>::iterator it = net->sub_nets_ids->begin();

	for (router_id = 0; router_id < net->sub_nets_ids->size() - 1; router_id++, it++)
			printf("%d ", *it + 1);

	if (net->sub_nets_ids->size() > 0)
		printf("%d\n", *it + 1);

	printf("%d\n", net->articulation_routers_number);

	printf("%lu\n", net->max_routers_number);
}

void analyze_net(net_t* net) {
	int router_id;
	
	analyze_args_t* args = new analyze_args_t();

	args->visited            = 0;
	args->router_state       = new int[net->routers_number];
	args->router_predecessor = new int[net->routers_number];
	args->router_depth       = new int[net->routers_number];
	args->router_low         = new int[net->routers_number];

	for (router_id = 0; router_id < net->routers_number; router_id++) {
		args->router_state[router_id]        = UNVISITED;
		args->router_predecessor[router_id]  = NIL;
		args->router_depth[router_id]        = NIL;
		args->router_low[router_id]          = NIL;
		net->articulation_routers[router_id] = false;
	}

	for (router_id = net->routers_number - 1; router_id >= 0; router_id--)
		if (args->router_state[router_id] == UNVISITED) {
			net->sub_nets_number++;
			visit_net(net, router_id, args);
			net->sub_nets_ids->push_front(router_id);
		}

	delete[] args->router_state;
	delete[] args->router_predecessor;
	delete[] args->router_depth;
	delete[] args->router_low;
	delete   args;
}

void visit_net(net_t* net, int router_src, analyze_args_t* args) {
	int router_childs = 0;

	args->router_state[router_src]    = ONVISIT;
	args->router_depth[router_src]    = args->visited;
	args->router_low[router_src]      = args->visited;
	args->visited++;

	for (int router_dst : net->connections[router_src]) {
		if (args->router_state[router_dst] == UNVISITED) {
			router_childs++;
			args->router_predecessor[router_dst] = router_src;

			visit_net(net, router_dst, args);

			args->router_low[router_src] = Min(args->router_low[router_src], args->router_low[router_dst]);

			if (args->router_predecessor[router_src] == NIL && router_childs > 1)
				if (net->articulation_routers[router_src] != true) {
					net->articulation_routers_number++;
					net->articulation_routers[router_src] = true;
				}

			if (args->router_predecessor[router_src] != NIL && args->router_low[router_dst] >= args->router_depth[router_src])
				if (net->articulation_routers[router_src] != true) {
					net->articulation_routers_number++;
					net->articulation_routers[router_src] = true;
				}
		}
		else if (router_dst != args->router_predecessor[router_src])
			args->router_low[router_src] = Min(args->router_low[router_src], args->router_depth[router_dst]);
	}

	args->router_state[router_src] = VISITED;
}

void attack_net(net* net) {

	attack_args_t *args = new attack_args_t();

	args->visited    = 0;
	args->depth      = new int[net->routers_number];
	args->low        = new int[net->routers_number];
	args->inRouters  = new bool[net->routers_number];
	args->routers    = new std::vector<int>();

	for (int router_id = 0; router_id < net->routers_number; router_id++) {
		args->depth[router_id] = std::numeric_limits<int>::max();
		args->inRouters[router_id] = false;
	}

	for (int router_id = 0; router_id < net->routers_number; router_id++)
		if (args->depth[router_id] == std::numeric_limits<int>::max() && !net->articulation_routers[router_id])
			attack_router(net, args, router_id);

	delete[] args->depth;
	delete[] args->low;
	delete[] args->inRouters;
	delete   args->routers;
	delete   args;
}

void attack_router(net_t* net, attack_args_t* args, int router_src) {
	int r;

	args->depth[router_src] = args->visited;
	args->low[router_src]   = args->visited;
	args->visited++;

	args->routers->push_back(router_src);
	args->inRouters[router_src] = true;

	for (int router_dst : net->connections[router_src])
		if (!net->articulation_routers[router_dst])
			if (args->depth[router_dst] == std::numeric_limits<int>::max() || args->inRouters[router_dst]) {
				if (args->depth[router_dst] == std::numeric_limits<int>::max())
					attack_router(net, args, router_dst);
				args->low[router_src] = Min(args->low[router_src], args->low[router_dst]);
			}

	if (args->depth[router_src] == args->low[router_src]) {
		if (args->routers->size() > net->max_routers_number)
			net->max_routers_number = args->routers->size();
		do {
			r = args->routers->back();
			args->routers->pop_back();
			args->inRouters[r] = false;
		} while(router_src != r);
	}
}

/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of proj1.cpp
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
