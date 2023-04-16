#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

struct Edge{  
    int u; // first vertice, from
    int v; // second vertice, to
    
    Edge(int n_u, int n_v);

    friend ostream& operator<<(ostream& os, const Edge& edge);
};

Edge::Edge(int n_u, int n_v) : u{n_u}, v{n_v} {};

ostream&  operator<<(ostream&os, const Edge& edge){
    os << edge.u << " "  << edge.v;
    return os;
}

void print(vector<Edge> graph){
    for (auto edge : graph) cout << edge << endl;
}
int main()
{
    /* initialize random seed: */
    //srand (time(NULL));
    FILE * pFile;
    pFile = fopen ("graph.txt","w");
    int n, p;
    vector<Edge> edgeList;
    cin >> n >> p; //number of the nodes and the probability
    int count_edges = 0; //number of edges
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            //take a pair of nodes, and get a random number R. If R < P (probability), add an edge
            if (i != j && rand() < p)  edgeList.push_back(Edge(i, j)), count_edges++;
        }
    }
    //write in file all the edges
    fprintf(pFile, "%d %d\n", n, count_edges);
    for (auto edge: edgeList)  fprintf(pFile, "%d %d\n", edge.u, edge.v);
    fclose (pFile);
    return 0;
}
