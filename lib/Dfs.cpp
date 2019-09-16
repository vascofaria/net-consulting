/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * Dfs.cpp
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */

#include <iostream>
#include <vector>
#include <set>
#include <cstdio>
#include <limits>

#define WHITE 1
#define GREY 2
#define BLACK 3

#define Min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct args {
	int* colors;
	int* pred;
	int* d;
	int* f;
	int time=1;
} dfs_args;

typedef struct a {
	int* colors;
	int* pred;
	int* depth;
	int* low;
	int visited=1;
	std::vector<int> artPoints;
} dfs_tarjan_args;


typedef struct bridge_args {
	int visited=0;
	int* colors;
	int* depth;
	int* low;
	std::set<int>* artPoints;
} bridge_args_t;

typedef struct tarjan_args {
	int visited = 0;
	int* d;
	int* low;
	std::vector<int> vertices;
} tarjan_args_t;

typedef struct net {
	int subnetsNumber=0;
	int maxRoutersNumber=0;
	std::vector<int> subnetsIDs;
	std::vector<int> breakersVertices;
} net_t;


int readUInt();

void bridge(std::vector<int>* edges, int verticesNumber);
void bridge_visit(std::vector<int>* edges, bridge_args_t* args, int* sub_net_id, int u, int v);

int contains(std::vector<int>* vertices, int vertex);
void scc_tarjan(std::vector<int>* edges, int verticesNumber, net* net, std::set<int>* affectedVertices);
void tarjan_visit(std::vector<int>* edges, int u, tarjan_args_t* args, net_t* net, std::set<int>* affectedVertices);

void dfs_tarjan(std::vector<int>* edges, int verticesNumber);
void dfs_tarjan_visit(std::vector<int>* edges, dfs_tarjan_args* args, int u);

void dfs(std::vector<int>* edges, int verticesNumber);
void dfs_visit(std::vector<int>* edges, dfs_args* args, int u);

int main() {

	int source, destination, i;
	int verticesNumber = readUInt();
	int edgesNumber = readUInt();

	std::vector<int>* edges = new std::vector<int>[verticesNumber];

	for (i=0; i < edgesNumber; i++) {
		source = readUInt()-1;
		destination = readUInt()-1;
		edges[source].push_back(destination);
		edges[destination].push_back(source);
	}

	bridge(edges, verticesNumber);

	return 0;
}

int readUInt() {
	int num=0;
	char c;
	while(((c=getchar()) != '\n') && (c != ' ') && (c != EOF)) {
		if (c < '0' || c > '9') exit(-1);
		num *= 10;
		num += (c-'0');
	}
	return num;
}

void bridge(std::vector<int>* edges, int verticesNumber) {
	int sccNumbers=0, sub_net_id;
	bridge_args_t* args = new bridge_args_t();
	args->colors = new int[verticesNumber];
	args->depth = new int[verticesNumber];
	args->low = new int[verticesNumber];
	args->artPoints = new std::set<int>();
	std::vector<int>* sub_nets_ids = new std::vector<int>();

	for (int u=0; u<verticesNumber; u++) {
		args->colors[u] = WHITE;
		args->depth[u] = -1;
		args->low[u] = -1;
	}

	for (int u=0; u<verticesNumber; u++) {
		if (args->colors[u] == WHITE) {
			sccNumbers++;
			sub_net_id=u;
			bridge_visit(edges, args, &sub_net_id, u, u);
			sub_nets_ids->push_back(sub_net_id);
		}
	}


	net_t* net = new net_t();
	scc_tarjan(edges, verticesNumber, net, args->artPoints);

	printf("============================================\n");
	printf("SUBNETS_IDS: ");
	for (int v : *sub_nets_ids)
		printf(" %d", v+1);
	putchar('\n');

	printf("================================\nBRIDGES:");
	for (int v : *args->artPoints)
		printf(" %d", v+1);
	printf("\n=================================\n");
	printf("SCC/SUBNETS NUMBER: %d\n==============================\n", sccNumbers);
	printf("MAXROUTERSNUMBER: %d\n", net->maxRoutersNumber);

	delete[] args->low;
	delete[] args->depth;
	delete[] args->colors;
	delete args->artPoints;
	delete args;
	delete sub_nets_ids;
}

void bridge_visit(std::vector<int>* edges, bridge_args_t* args, int* sub_net_id, int u, int v) {
	args->colors[v] = GREY;
	args->depth[v] = args->low[v] = args->visited++;

	for (int w : edges[v]) {
		if (args->colors[w] == WHITE) {
			if (*sub_net_id < w)
				*sub_net_id = w;
			bridge_visit(edges, args, sub_net_id, v, w);
			args->low[v] = Min(args->low[v], args->low[w]);
			if (args->low[w] == args->depth[w]) {
				if (edges[v].size()>1)
					args->artPoints->insert(v);
				if (edges[w].size()>1)
					args->artPoints->insert(w);
			}
		} else if (w != u)
				args->low[v] = Min(args->low[v], args->depth[w]);
	}
}




int contains(std::vector<int>* vertices, int vertex) {
	for (int v : (*vertices))
		if (v == vertex) return 1;
	return 0;
}

void scc_tarjan(std::vector<int>* edges, int verticesNumber, net* net, std::set<int>* affectedVertices) {

	tarjan_args_t *args = new tarjan_args_t();
	args->d = new int[verticesNumber];
	args->low = new int[verticesNumber];

	for (int v = 0; v < verticesNumber; v++)
		args->d[v] = std::numeric_limits<int>::max();

	for (int u = 0; u < verticesNumber; u++)
		if (args->d[u] == std::numeric_limits<int>::max() && affectedVertices->find(u) == affectedVertices->end())
			tarjan_visit(edges, u, args, net, affectedVertices);

	delete[] args->d;
	delete[] args->low;
	delete args;
}

void tarjan_visit(std::vector<int>* edges, int u, tarjan_args_t* args, net_t* net, std::set<int>* affectedVertices) {
	int v = -1;
	int w;

	args->d[u] = args->low[u] = args->visited;
	(args->visited)++;

	(args->vertices).push_back(u);

	for (int v : edges[u])
		if (affectedVertices->find(u) == affectedVertices->end())
			if (args->d[v] == std::numeric_limits<int>::max() || contains(&args->vertices, v)) {
				if (args->d[v] == std::numeric_limits<int>::max())
					tarjan_visit(edges, v, args, net, affectedVertices);
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


































void dfs_tarjan(std::vector<int>* edges, int verticesNumber) {
	int sccNumber=0;

	dfs_tarjan_args* args = new dfs_tarjan_args();
	args->colors = new int[verticesNumber];
	args->pred = new int[verticesNumber];
	args->depth = new int[verticesNumber];
	args->low = new int[verticesNumber];

	for (int u=0; u<verticesNumber; u++) {
		args->colors[u] = WHITE;
		args->pred[u] = -1;
		args->depth[u] = -1;
		args->low[u] = -1;
	}

	for (int u=0; u<verticesNumber; u++)
		if (args->colors[u] == WHITE) {
			sccNumber++;
			dfs_tarjan_visit(edges, args, u);
		}


	for (int i = 0; i < verticesNumber; i++) {
		printf("============VERTICE=======\n");
		printf("COLOR: %s\n", (args->colors[i]==WHITE ? "white" : "black"));
		printf("PRED: %d\n", args->pred[i]);
		printf("DEPTH: %d\n", args->depth[i]);
		printf("LOW: %d\n", args->low[i]);
	}

	printf("================================\nBRIDGES:");
	for (int v : args->artPoints)
		printf(" %d", v+1);
	printf("\n=================================\n");
	printf("SCC/SUBNETS NUMBER: %d\n==============================\n", sccNumber);

	delete[] args->colors;
	delete[] args->pred;
	delete[] args->depth;
	delete[] args->low;
	delete args;
}

void dfs_tarjan_visit(std::vector<int>* edges, dfs_tarjan_args* args, int u) {
	bool isArtPoint = false;
	args->colors[u] = GREY;
	args->depth[u] = args->visited;
	args->low[u] = args->visited;
	args->visited++;
	printf("=========U:%d=======\n", u);
	for (int v : edges[u]) {
		printf("V: %d\n", v);
		if (args->colors[v] == WHITE) {
			printf("WHITE\n");
			args->pred[v] = u;
			dfs_tarjan_visit(edges, args, v);
			args->low[v] = Min(args->low[u], args->low[v]);
			printf("LOW de %d e %d\n", v, args->low[v]);
			if (args->low[u] >= args->depth[v] && args->pred[u] == v) {
				printf("ART\n");
				isArtPoint=true;
			}
		} else if (args->colors[v] == GREY) {
			printf("GREY\n");
			args->low[u] = Min(args->low[u], args->depth[v]);
			if (args->low[u] >= args->depth[v] && args->pred[u] == v) {
				printf("ART\n");
				isArtPoint=true;
			}
		}
	}

	if (isArtPoint && edges[u].size()>1)
		args->artPoints.push_back(u);

	args->colors[u] = BLACK;
}

void dfs(std::vector<int>* edges, int verticesNumber) {
	dfs_args* args = new dfs_args();
	args->colors = new int[verticesNumber];
	args->pred = new int[verticesNumber];
	args->d = new int[verticesNumber];
	args->f = new int[verticesNumber];

	for (int i=0; i<verticesNumber; i++) {
		args->colors[i] = WHITE;
		args->pred[i] = -1;
		args->d[i] = -1;
		args->f[i] = -1;
	}

	for (int u=0; u<verticesNumber; u++)
		if (args->colors[u] == WHITE)
			dfs_visit(edges, args, u);

	for (int i = 0; i < verticesNumber; i++) {
		printf("============VERTICE=======\n");
		printf("COLOR: %s\n", (args->colors[i]==WHITE ? "white" : "black"));
		printf("PRED: %d\n", args->pred[i]);
		printf("D: %d\n", args->d[i]);
		printf("F: %d\n", args->f[i]);
	}


	delete[] args->colors;
	delete[] args->pred;
	delete[] args->d;
	delete[] args->f;
	delete args;
}

void dfs_visit(std::vector<int>* edges, dfs_args* args, int u) {
	args->colors[u] = GREY;
	args->d[u] = args->time;
	args->time++;
	for (int v : edges[u])
		if (args->colors[v] == WHITE) {
			args->pred[v] = u;
			dfs_visit(edges, args, v);
		}

	args->colors[u] = BLACK;
	args->f[u] = args->time;
	args->time++;
}
/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of Dfs.cpp
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
