#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "dbscan.hpp"
#include "DSU.hpp"

using namespace std;

double calculateDistance(Point& pointCore, Point& pointTarget)
{
    return sqrt(pow(pointCore.x - pointTarget.x, 2) + pow(pointCore.y - pointTarget.y, 2));
}

vector<Point> calculateCluster(vector<Point> &List, Point &ppoint, double eps)
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
       // printf("%f %d %d\n",calculateDistance(ppoint, v), ppoint.number, v.number );
    }
    return cluster_eps;
}

int expandCluster(vector<Point> &List, Point &point, int minPts, int clusterID, double eps)
{    
    vector<Point> cluster = calculateCluster(List, point, eps); //Calculate cluster for the point

    if (cluster.size() < minPts)
    {
        point.label = NOISE;
        return FAILURE;
    }
    else 
    {
        int index = 0, indexCorePoint = 0;
        point.label = clusterID;
        //the whole cluster has clusterID
        for(auto v: cluster)
        {
            List[v.number].label = clusterID;
            if (v.x == point.x && v.y == point.y) //to find our core point in order to erase it
            {
                indexCorePoint = index;
            }
            ++index;
        }
        //printf("Core point %d\n", List[point.number].label);
        cluster.erase (cluster.begin() + indexCorePoint);
        //need to erase point from cluster to do after

        for (auto v: cluster)
        {
            vector<Point> clusterNeigbors = calculateCluster(List, v, eps);//find all neighbours of every point in cluster
            if (clusterNeigbors.size() >= minPts)
            {
                for (auto neighbor: clusterNeigbors)
                {
                    if (List[neighbor.number].label == UNCLASSIFIED || List[neighbor.number].label == NOISE)
                    {
                        if (List[neighbor.number].label == UNCLASSIFIED )
                        {
                            cluster.push_back(neighbor);
                        }
                        List[neighbor.number].label = clusterID;
                    }
                }
            }
        }
        return SUCCESS;
    }
}

int expandCluster(vector<Point> &List, Point &point, int minPts, int clusterID, double eps, DSU &UF){
    
    UF.set_parent(point.number, clusterID);
    vector<Point> cluster = calculateCluster(List, point, eps);
    for(auto& neighbor : cluster){
        if(List[neighbor.number].label >= 0){ // classified
            UF.join(List[neighbor.number].label, clusterID);
        }
        List[neighbor.number].label = UF.find(clusterID);
        // printf("%d %d\n", neighbor.number, UF.find(clusterID));
    }

    return SUCCESS;
}

int dbscan(vector<Point> &List, int minPts, double eps)
{
    // int clusterID = 0;
    // for(auto point: List)
    // {
    //     if (point.label == UNCLASSIFIED)
    //     {
    //         if (expandCluster(List, point, minPts, clusterID, eps) != FAILURE)
    //         {
    //             clusterID += 1;
    //         }
    //     }
    //    printf("%d %d %d\n", point.label, point.x, point.y);
    // }
    // return clusterID;

    DSU UF((int) List.size());
    vector<int> core_points_id;
    for(auto &point : List){
        if(calculateCluster(List, point, eps).size() >= minPts){
            core_points_id.push_back(point.number);
        }
    }

    for(auto id : core_points_id){
        auto& point = List[id];
        expandCluster(List, point, minPts, point.number, eps, UF);
    }

    for(auto &point : List){
        printf("%d %d %d\n", point.label, point.x, point.y);
    }
    return UF.size-(List.size()-core_points_id.size()); //how many clusters exist
}


int main()
{
    vector<Point> List;
    double eps = 3;
    int m_minPts = 2, n;
    int i = 0;
    cin >> n;
    while(n--)
    {
        int x, y;
        cin >> x >> y;
        List.push_back(Point(x, y, i));
        i++; 
    }
    printf("%d\n", dbscan(List, m_minPts, eps));
}
