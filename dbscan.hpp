#include <vector>
#include <cmath>
#include <iostream>
#include "DSU.hpp"

#define UNCLASSIFIED -1

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

double Point::calculateDistance(const Point& pointTarget)
{
    return sqrt(pow(this->x - pointTarget.x, 2) + pow(this->y - pointTarget.y, 2));
}

class DBSCAN
{
  private:
    double eps = 0;
    int min_pts = 0;
  
  public:
    std::vector<int> labels;
  
  private:
    void fit_bfs(double **distance_matrix, int total_pts);
    void fit_dsu(double **distance_matrix, int total_pts);

  public:
    DBSCAN(double n_eps, double n_min_pts):eps{n_eps}, min_pts{n_min_pts}{}
    std::vector<int> getNeighbors(int point, int total_pts, double** distance_matrix);
    void fit(double **distance_matrix, int total_pts, std::string algo="BFS");
    void fit(std::vector<Point> &data);
};
