#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "../kosaraju/kosaraju.hpp"
#include "../dbscan/dbscan.hpp"

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

    // lazy casting
    vector<vector<int>> dmatrix = grafo.distance_matrix();
    double** distance_matrix = new double*[n];
    for(int i = 0; i < n; ++i){
        distance_matrix[i] = new double[n];
        for(int j = 0; j < n; ++j){
            distance_matrix[i][j] = dmatrix[i][j]; 
        }
    }
    cout << "dmatrix generated! " << endl;

    // DBSCAN PARAMETERS 
    double minPts = 4;
    double eps_start = 1, eps_end = 10, delta = 1;
    int n_samples = 100;

    // file generating (mean of all iterations)
    FILE *pFile;
    std::string fname = "csv/dmatrix.csv";
    pFile = std::fopen(fname.c_str(), "w");
    fprintf(pFile, "eps,n_cluster,largest_cluster,n_noise\n");
    for (double eps = eps_start; eps < eps_end; eps += delta){
        double n_cluster = 0.0, largest_cluster = 0.0, n_noise = 0.0;
        for(int sample = 0; sample < n_samples; ++sample){
            DBSCAN clustering(eps, minPts);
            clustering.fit(distance_matrix, n, "BFS");
            n_cluster += clustering.get_n_cluster();
            largest_cluster += clustering.get_largest_cluster();
            n_noise += clustering.get_n_noise();
        }
        fprintf(pFile, "%lf, %lf, %lf, %lf\n", eps, n_cluster/n_samples, largest_cluster/n_samples, n_noise/n_samples);
    }
    std::fclose(pFile);
}
