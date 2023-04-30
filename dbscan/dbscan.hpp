#include <iostream>
#include <vector>
#include "DSU.hpp"

const int NOISE = -1;
const int BORDER = 0;
const int CORE = 1;

class DBSCAN
{
  private:
    double eps = 0;
    int min_pts = 0; //y compris le centre du cluster
    
  public:
    int n_cluster = 0;
    std::vector<int> labels;
  
  private:
    void fit_bfs(double **distance_matrix, int total_pts);
    void fit_dsu(double **distance_matrix, int total_pts);

  public:
    DBSCAN(double n_eps, int n_min_pts):eps{n_eps}, min_pts{n_min_pts}{}
    std::vector<int> getNeighbors(int point, int total_pts, double** distance_matrix);
    void fit(double **distance_matrix, int total_pts, std::string algo="BFS");
};