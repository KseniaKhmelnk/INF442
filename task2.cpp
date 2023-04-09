#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Graph
{
    private:
    vector<vector<int>> adj;

public:
    Graph(int n)
    {
        adj.resize(n);
    }
    void add_edge(int from, int to)
    {
        adj[from].push_back(to);
    }
};
int main()
{
    /* initialize random seed: */
    srand (time(NULL));
    int n, p;
    cin >> n >> p; //number of the nodes and the probability
    Graph g(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != j && rand() >= p) g.add_edge(i, j);//edge is made
        }
    }
    return 0;
}