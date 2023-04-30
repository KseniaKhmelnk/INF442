#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <map>
#include <queue>

using namespace std; 
class Graph{
public:
    int v;  // Number of vertices
    int e;  // Number of edges
    vector<int> *adj;
    Graph(int n_v, int n_e)
    {
        v = n_v;
        e = n_e;
        adj = new vector<int>[2 * v];
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    void bfs(int from, int to, vector<int> &dist, vector<int> &par);
    int findPath(int from, int to);
};

void Graph::bfs(int from, int to, vector<int> &dist, vector<int> &par)
{
    vector<bool> visited(v, 0);      
    queue<int> q; 
    q.push(from); 
    visited[from] = true;
    while(!q.empty())
    {
        int size = q.size();
        while(size--)
        {
            int node = q.front();
            q.pop();
            visited[node] = true;
            for(int next_node: adj[node])
            {
                if(!visited[next_node])
                {  
                    visited[next_node] = true; 
                    dist[next_node] = dist[node] + 1;
                    par[next_node] = node;
                    q.push(next_node);
                }
            }
        }
    }
}

int Graph::findPath(int from, int to)
{
    vector<int> dist(v, 0);
    vector<int> par(v);
    for(int i = 0; i < v; i++)
    {
        par[i] = i;
    }
    bfs(from, to, dist, par);
    int length = 0; 
    while(par[to] != to)
    {
        to = par[to];
        length++;
    }
    return length;
}

int main()
{
    int nodes, edges;
    cin >> nodes >> edges;
    Graph G(nodes, edges);
    // reindex IF NEEDED
    vector<int> from(edges), to(edges);
    for(int i = 0; i < edges ; ++i)
    {
        cin >> from[i] >> to[i];
    }
    map<int,int> idx;
    auto reindex = [&idx](int& v){
        if(!idx.count(v)) idx[v] = idx.size();
        v = idx[v];
    };
    for_each(from.begin(), from.end(), reindex);
    for_each(to.begin(), to.end(), reindex);

    cout << "Nodes after reindexing: " << idx.size() << endl;

    for(int i = 0; i < edges; ++i)
    {
        G.addEdge(from[i], to[i]);
    }
    //int **distance_matrix;
    for (int i = 0; i < nodes; i++)
    {
        cout << "Edge" << i << endl;
        for (int j = 0; j < nodes; j++) 
        {
            //dist_matrix[i][j] = G.findPath(i, j);
            cout << G.findPath(i, j) << " ";
        }
        cout << endl;
    }
    return 0;
}