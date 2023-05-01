#include <iostream>
#include <vector>
#include <cmath>
#include "dbscan/dbscan.hpp"

using namespace std;

struct Point
{  
    double x; // first coordinate
    double y; // second coordinate 
    
    Point(double n_x = 0.0, double n_y = 0.0): x(n_x), y(n_y){}
    double calculateDistance(const Point& pointTarget)
    {
        return sqrt(pow(this->x - pointTarget.x, 2) + pow(this->y - pointTarget.y, 2));
    }
};

int main(){
    int n; // number of points
    cin >> n;
    vector<Point> points(n);
    for(auto &p : points)
    {
        cin >> p.x >> p.y; // coordinates
    }
    
    int total_pts = points.size();
    double** distance_matrix = new double*[total_pts];
    for(int i = 0; i < total_pts; ++i)
    {
        distance_matrix[i] = new double[total_pts];
        for(int j = 0; j < total_pts; ++j){
            distance_matrix[i][j] = points[i].calculateDistance(points[j]);
        }
    }

    double eps = 3;
    int minPts = 4;
    DBSCAN clustering(eps, minPts);
    clustering.fit(distance_matrix, total_pts, "BFS");

    cout << "Number of clusters: " << clustering.get_n_cluster() << endl;
    cout << "Nodes in largest cluster: " << clustering.get_largest_cluster() << endl; 

    // for(auto id : clustering.labels) cout << id << " ";
    // cout << endl;
}