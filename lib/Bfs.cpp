/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * Bfs.cpp
 *
 * -------------------------------------------------------------------------------
 *
 * Made by: Vasco Faria
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
#define WHITE 1
#define GREY 2
#define BLACK 3

void bfs(Graph *g, int src) {
	/*src: 0 : V-1*/
	int color[g->getV()];
	int pred[g->getV()];
	int dist[g->getV()];
	std::queue<int> greyQ;
	int u;

	for (int i=0; i<g->getV(); i++) {
		color[i] = WHITE;
		pred[i] = -1;
		dist[i] = -1;
	}

	color[src] = GREY;
	dist[src] = 0;
	pred[src] = -1;
	greyQ.push(src);

	while (greyQ.size() > 0) {
		u = greyQ.front(); greyQ.pop();
		std::vector<int> vec = g->getAdjs(u);
		for (int v : vec) {
			if (color[v] == WHITE) {
				color[v] = GREY;
				dist[v] = dist[u]+1;
				pred[v] = u;
				greyQ.push(v);
			}
		}
		color[u] = BLACK;
	}
	/*
	for (int i=0; i < g->getV(); i++)
		std::cout << "c: " << color[i] << std::endl
			<< "p: " << pred[i] << std::endl
			<< "d: " << dist[i] << std::endl;*/
}

/* _______________________________________________________________________________
 * »»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»
 *
 * End of Bfs.cpp
 *
 * «««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««««
 */
