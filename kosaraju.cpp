#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;

class Graph{
private:
    vector<vector<int>>  adj, adj_t;
    stack<int> order;
    vector<int> scc, scc_size;
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
        ++scc_size[component];
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
        n_scc = 0;
    }
    void add_edge(int from, int to){
        int n = adj.size();
        assert(from < n && from >= 0);
        assert(to < n && to >= 0);
        adj[from].push_back(to);
        adj_t[to].push_back(from);
    }
    void run(){
        int n = (int) adj.size();
        auto &seen = scc;
        for(int i = 0; i < n; ++i){
            if(!seen[i]) dfs(i);
        }
        while(!order.empty()){
            if(scc[order.top()] == -1){
                scc_size.push_back(0);
                dfs_t(order.top(), n_scc++); 
            }
            order.pop();
        }
    }
    int get_comp(int i){ return scc[i]; }
    int get_largest_scc(){
        int ans = 0;
        for(auto sz : scc_size){
            ans = max(ans, sz);
        }
        return ans;
    }
    void print_scc(){
        for(int i = 0; i < adj.size(); ++i){
            printf("%d: %d\n", i, scc[i]);
        }
    }
};

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> from(m), to(m);
    for(int i=0; i<m; ++i){
        cin >> from[i] >> to[i];
        // --from[i], --to[i]; // if not 0 indexed
    }
    // reindex IF NEEDED (bug if node is not in the edge list)
    
    // map<int,int> idx;
    // auto reindex = [&idx](int& v){
    //     if(!idx.count(v)) idx[v] = idx.size();
    //     v = idx[v];
    // };
    // for_each(from.begin(), from.end(), reindex);
    // for_each(to.begin(), to.end(), reindex);

    // cout << "Nodes after reindexing: " << idx.size() << endl;
    
    Graph grafo = Graph(n);

    // Graph grafo = Graph(n);
    
    for(int i = 0; i < m; ++i){
        grafo.add_edge(from[i], to[i]);
    }

    grafo.run();
    cout << "Nodes in largest SCC: " << grafo.get_largest_scc() << endl;
    // grafo.print_scc();
}
