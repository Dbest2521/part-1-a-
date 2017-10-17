#include <stdio.h>

typedef struct GraphRep *GraphRep;

Graph newGraph();
int   isConnected(Graph, char *, char *);
void  disposeGraph(Graph);
//int   addEdge(Graph,char *,char *);
int   nVertices(Graph);
void  showGraph(Graph,int);

#endif
