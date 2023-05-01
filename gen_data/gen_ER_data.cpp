#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../kosaraju/kosaraju.hpp"

int main()
{
    /* initialize random seed: */
    srand (time(NULL));
    
    int n;
    double p_start, p_end, delta;
    
    std::cin >> n; //number of nodes
    std::cin >> p_start >> p_end; // start and end value of p 
    delta = (p_end - p_start)/1000; // 1000 runs uniformly over p 

    FILE *pFile;
    for(int sample = 1; sample < 10; ++sample){
        std::string fname = "csv/ER_" + std::to_string(n) + "_" + std::to_string(sample) + ".csv";
        pFile = std::fopen(fname.c_str(), "w");
        fprintf(pFile, "p,n_scc,largest_scc\n");
        for (double p = p_start; p < p_end; p += delta)
        { 
            Graph grafo(n);
            int count_edges = 0; //number of edges
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    //take a pair of nodes, and get a random number R. If R < P (probability), add an edge
                    if ((double) rand() / RAND_MAX < p)  grafo.add_edge(i, j), ++count_edges;
                }
            }
            grafo.run_kosaraju();
            fprintf(pFile, "%lf, %d, %d\n", p, grafo.get_n_scc(), grafo.get_largest_scc());
        }
        std::fclose(pFile);
    }
    return 0;
}
