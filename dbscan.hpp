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
    int ID;
    
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
public:
    vector<Point> calculateCluster(vector<Point> &List, Point &ppoint, double eps);
    int expandCluster(vector<Point> &List, Point &point, int minPts, int clusterID, double eps, DSU &UF);
    int fit(vector<Point> &List, int minPts, double eps);
};