#include <iostream>
#include <vector>
#include <stack>
#include <cassert>
#include <algorithm>
using namespace std;
// testing implementation : problem-example bellow
// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/components-of-graph-2b95e067/
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
    void identify(){
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
};

int main(){
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> from(m), to(m), air_quality(n);
    for(auto& val : air_quality) cin >> val;
    for(int i=0; i<m; ++i){
        cin >> from[i] >> to[i];
        from[i]--, to[i]--;
    }

    int l=1, r=1e9;
    while(l<r){
        int x = (l+r+1)/2;
        bool ok = 0;

        int n_graph = 0;
        vector<int> used(n);
        for(int i=0; i<n; ++i) if(air_quality[i] >= x) ++n_graph, used[i] = 1;
        Graph grafo(n);
        for(int i=0; i<m; ++i){
            if(used[from[i]] && used[to[i]]){
                grafo.add_edge(from[i], to[i]);
            }
        }
        grafo.identify();
        ok = (grafo.get_largest_scc() >= k);
        
        if(ok) l = x;
        else r = x-1;
    }
    cout << l << endl;
}
