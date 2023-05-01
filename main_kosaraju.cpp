#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "kosaraju/kosaraju.hpp"

using namespace std;

const bool IDX_0 = true; // if nodes ids start from 1 and not 0 
const bool REINDEX = true; // if nodes ids are not in range [0, n-1] ou [1, n]

int main(){
    int n, m;
    cin >> n >> m;

    vector<int> from(m), to(m);
    for(int i=0; i<m; ++i){
        cin >> from[i] >> to[i];
        if(IDX_0) --from[i], --to[i];
    }

    if(REINDEX){ 
        map<int,int> idx;
        auto reindex = [&idx](int& v){
            if(!idx.count(v)) idx[v] = idx.size();
            v = idx[v];
        };
        for_each(from.begin(), from.end(), reindex);
        for_each(to.begin(), to.end(), reindex);

        cout << "Number of nodes after reindexing: " << idx.size() << endl;
    }
    Graph grafo = Graph(n);
    
    for(int i = 0; i < m; ++i){
        grafo.add_edge(from[i], to[i]);
    }

    grafo.run_kosaraju();
    cout << "Nodes in largest SCC: " << grafo.get_largest_scc() << endl;
    cout << "Number of SCC's: " << grafo.get_n_scc() << endl;
    // grafo.print_all_scc();
}
