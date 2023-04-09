#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph{
private:
    vector<vector<int>>  adj, adj_t;
    stack<int> order;
    vector<int> scc;
    int n_scc;

    void dfs(int cur_node){
        auto &seen = scc;
        seen[cur_node] = -1; 
        for(auto neighbor : adj[cur_node]){
            if(!seen[neighbor]){
                dfs(neighbor);
            }
        } 
        order.push(cur_node);
    }

    void dfs_t(int cur_node, int component){
        scc[cur_node] = component;
        for(auto neighbor : adj_t[cur_node]){
            if(~scc[neighbor]) continue;
            dfs_t(neighbor, component);
        }
    }

public:
    Graph(int n){
        adj.resize(n);
        adj_t.resize(n);
        scc.resize(n);
    }
    void add_edge(int from, int to){
        adj[from].push_back(to);
        adj_t[to].push_back(from);
    }
    void identify(){
        int n = (int) adj.size();
        auto &seen = scc;
        for(int i = 0; i < n; ++i){
            if(!seen[i]) dfs(i);
        }
        while(!order.empty()){
            dfs_t(order.top(), ++n_scc); 
            order.pop(); 
        }
    }
    int get_comp(int i){ return scc[i]; }
    int get_scc(){ return n_scc; }
};

int main(){
    int n, m;
    cin >> n >> m;
    Graph grafo = Graph(n);
    for(int i = 0; i < n; ++i){
        int from, to;
        cin >> from >> to;
        grafo.add_edge(from, to);
    }
    grafo.identify();
    cout << grafo.get_scc() << endl;
}