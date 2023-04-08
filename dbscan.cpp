#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "dbscan.hpp"

using namespace std;

vector<point> cluster;
vector<point> cluster_v;
vector<point> cluster_eps;

int dbscan(vector<point> List, int minPts, double eps)
{
    int clusterID = 1;
    for(auto p: List)
    {
        if (p.label == UNCLASSIFIED )
        {
            if (expandCluster(List, p, minPts, clusterID, eps) != FAILURE )
            {
                clusterID += 1;
            }
        }
    }
    return 0;
}

int expandCluster(vector<point> List, point point, int minPts, int clusterID, double eps)
{    
    cluster = calculateCluster(List, point, eps); //Calculate cluster for the point

    if (cluster.size() < minPts)
    {
        point.label = NOISE;
        return FAILURE;
    }
    else 
    {
        //need to erase point from cluster to do after
        for (auto v: cluster)
        {
            if (v.label == NOISE) v.label = clusterID;
            if (v.label == UNCLASSIFIED)
            {
                v.label = clusterID;
                cluster_v = calculateCluster(List, v, eps); //Calculate cluster for the point
                if (cluster_v.size() >= minPts)
                {
                    //cluster = cluster + cluster_v
                }
            }
        }
        return SUCCESS;
    }
}

vector<point> calculateCluster(vector<point> List, point point, double eps)
{
    int index = 0;
    //initialize cluster_eps
    for(auto v: List)
    {
        if (calculateDistance(point, v) <= eps)
        {
            cluster_eps.push_back(v);
        }
    }
    return cluster_eps;
}

double calculateDistance(point& pointCore, point& pointTarget )
{
    return sqrt(pow(pointCore.x - pointTarget.x, 2) + pow(pointCore.y - pointTarget.y, 2));
}

int main()
{
    vector<point> List;
    double eps;
    int minPts, n;
    cin >> n >> minPts >> eps;
    while(n--){
        int x, y;
        cin >> x >> y;
        List.push_back(point(x, y)); 
    }
    dbscan(List, minPts, eps);
}