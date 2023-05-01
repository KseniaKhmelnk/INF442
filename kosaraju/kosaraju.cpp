#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cassert>
#include <algorithm>
#include <climits>
#include "kosaraju.hpp"

// Kosaraju's implementation
void Graph::dfs(int cur_node){
    auto &seen = scc;
    seen[cur_node] = -1;
    for(auto neighbor : adj[cur_node]){
        if(!seen[neighbor]){
            dfs(neighbor);
        }
    } 
    order.push(cur_node);
}

void Graph::dfs_t(int cur_node, int component){
    scc[cur_node] = component;
    ++scc_size[component];
    for(auto neighbor : adj_t[cur_node]){
        if(~scc[neighbor]) continue;
        dfs_t(neighbor, component);
    }
}
void Graph::run_kosaraju(){
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

// Generate distance matrix
void Graph::bfs(int from, std::vector<std::vector<int>> &dmatrix)
{
    int n = adj.size();
    std::vector<bool> visited(n);      
    std::queue<std::pair<int,int>> q; 
    q.push({from, 0}); 
    while(!q.empty())
    {

        auto [node, distance] = q.front();
        q.pop();
        visited[node] = true;
        for(int next_node: adj[node])
        {
            if(!visited[next_node])
            {  
                dmatrix[from][next_node] = distance + 1;
                q.push({next_node, distance + 1});
            }
        }
    }
}

std::vector<std::vector<int>> Graph::distance_matrix()
{
    int n = adj.size();
    std::vector<std::vector<int>> dmatrix(n, std::vector<int>(n, INT_MAX));

    for(int from = 0; from < n; from++)
    {
        bfs(from, dmatrix);
    }

    return dmatrix;
}

// INPUT
Graph::Graph(int n){
    adj.resize(n);
    adj_t.resize(n);
    scc.resize(n);
    n_scc = 0;
}

void Graph::add_edge(int from, int to){
    int n = adj.size();
    assert(from < n && from >= 0);
    assert(to < n && to >= 0);
    adj[from].push_back(to);
    adj_t[to].push_back(from);
}


// OUTPUT
int Graph::get_scc(int i){ return scc[i]; }
int Graph::get_n_scc() { return n_scc; }
int Graph::get_largest_scc(){
    int ans = 0;
    for(auto sz : scc_size){
        ans = std::max(ans, sz);
    }
    return ans;
} 
void Graph::print_all_scc(){
    for(int i = 0; i < adj.size(); ++i){
        printf("%d: %d\n", i, scc[i]);
    }
}