#include <vector>
#include <cmath>
#include <iostream>
#include "DSU.hpp"

#define UNCLASSIFIED -1
#define NOISE -2
#define SUCCESS 0
#define FAILURE -3

using namespace std;

struct Point{  
    int x; // first coordinate
    int y; // second coordinate 
    int label; //label
    int ID; //id of every point
    
    Point(int n_x, int n_y, int n_ID);
    double calculateDistance(const Point& pointTarget);
};

Point::Point(int n_x, int n_y, int n_ID)
{
    x = n_x;
    y = n_y;
    label = UNCLASSIFIED;
    ID = n_ID;
}

class DBSCAN
{
  private:
    double eps = 0;
    int min_pts = 0;
    DSU *disjoint_set = nullptr;

    vector<int> fit_bfs(double **distance_matrix, int total_pts);
    vector<int> fit_dsu(double **distance_matrix, int total_pts);

  public: 
    DBSCAN(double n_eps, double n_minPts);
    vector<int> getNeighbors(int point, int total_pts, double** distance_matrix);
    vector<int> fit(double **distance_matrix, int total_pts, string algo="BFS");

    vector<int> calculateCluster(vector<Point> &data, Point &center_point);
    int expandCluster(vector<Point> &List, Point &point);
    int fit(vector<Point> &data);
};
DBSCAN::DBSCAN(double n_eps, double n_min_pts)
{
    eps = n_eps;
    min_pts = n_min_pts;
}
