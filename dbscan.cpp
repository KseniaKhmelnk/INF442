#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "dbscan.hpp"

using namespace std;

vector<Point> cluster;
vector<Point> cluster_v;


int dbscan(vector<Point> List, int minPts, double eps)
{
    int clusterID = 1;
    for(auto p: List)
    {
        if (p.label == UNCLASSIFIED)
        {
            if (expandCluster(List, p, minPts, clusterID, eps) != FAILURE)
            {
                clusterID += 1;
            }
        }
    }
    return 0;
}

int expandCluster(vector<Point> List, Point point, int minPts, int clusterID, double eps)
{    
    cluster = calculateCluster(List, point, eps); //Calculate cluster for the point

    if (cluster.size() < minPts)
    {
        point.label = NOISE;
        return FAILURE;
    }
    else 
    {
        int index = 0, indexCorePoint = 0;
        //the whole cluster has clusterID
        for(auto v: cluster)
        {
            v.label = clusterID;
            if (v.x == point.x && v.y == point.y) //to find our core point in order to erase it
            {
                indexCorePoint = index;
            }
            ++index;
        }
        cluster.erase (cluster.begin() + indexCorePoint);
        //need to erase point from cluster to do after

        for (auto v: cluster)
        {
            vector<Point> clusterNeigbors = calculateCluster(List, v, eps);//find all neighbours of every point in cluster
            if (clusterNeigbors.size() >= minPts)
            {
                for (auto neighbor: clusterNeigbors)
                {
                    if (neighbor.label == UNCLASSIFIED || neighbor.label == NOISE)
                    {
                        if (neighbor.label == UNCLASSIFIED )
                        {
                            cluster.push_back(neighbor);
                        }
                        neighbor.label = clusterID;
                    }
                }
            }
        }
        return SUCCESS;
    }
}

vector<Point> calculateCluster(vector<Point> List, Point ppoint, double eps)
{
    int index = 0;
    //initialize cluster_eps
    vector<Point> cluster_eps;
    for(auto v: List)
    {
        if (calculateDistance(ppoint, v) <= eps)
        {
            cluster_eps.push_back(v);
        }
    }
    return cluster_eps;
}

double calculateDistance(Point& pointCore, Point& pointTarget )
{
    return sqrt(pow(pointCore.x - pointTarget.x, 2) + pow(pointCore.y - pointTarget.y, 2));
}

int main()
{
    vector<Point> List;
    double eps;
    int minPts, n;
    cin >> n >> minPts >> eps;
    while(n--){
        int x, y;
        cin >> x >> y;
        List.push_back(Point(x, y)); 
    }
    dbscan(List, minPts, eps);
}
