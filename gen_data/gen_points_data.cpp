#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../dbscan/dbscan.hpp"

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
    srand (time(NULL));
    int n = 100; // number of points
    double eps = 0.09;
    int minPts = 4;
    int n_samples = 50;

    FILE *pFile;
    for(int sample = 0; sample < n_samples; ++sample){
        std::string p_fname = "../csv/points_XY_" + std::to_string(n) + "_" + std::to_string(minPts) + "_" + std::to_string(sample) + ".csv";
        pFile = std::fopen(p_fname.c_str(), "w");
        fprintf(pFile, "x,y,label\n");
        
        // data points
        vector<Point> points(n);
        for(auto &p : points){
            p.x = (double) rand() / RAND_MAX; //cpordinates
            p.y = (double) rand() / RAND_MAX; // coordinates
        }

        // distance_matrix
        double** distance_matrix = new double*[n];
        for(int i = 0; i < n; ++i){
            distance_matrix[i] = new double[n];
            for(int j = 0; j < n; ++j){
                distance_matrix[i][j] = points[i].calculateDistance(points[j]);
            }
        }

        // clustering 
        DBSCAN opt_clustering(eps, minPts);
        opt_clustering.fit(distance_matrix, n);
        auto labels = opt_clustering.get_labels();
        for(int i = 0; i < n; ++i){
            auto& p = points[i];
            fprintf(pFile, "%lf,%lf,%d\n", p.x, p.y, labels[i]);
        }

        fclose(pFile);
    }
}