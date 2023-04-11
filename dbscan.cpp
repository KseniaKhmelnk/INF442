#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "dbscan.hpp"

using namespace std;

double Point::calculateDistance(const Point& pointTarget)
{
    return sqrt(pow(this->x - pointTarget.x, 2) + pow(this->y - pointTarget.y, 2));
}

vector<Point> DBSCAN::calculateCluster(vector<Point> &List, Point &point, double eps)
{
    int index = 0;
    //initialize cluster_eps
    vector<Point> cluster_eps;
    for(auto v: List)
    {
        if (point.calculateDistance(v) <= eps)
        {
            cluster_eps.push_back(v);
        }
       // printf("%f %d %d\n",calculateDistance(ppoint, v), ppoint.ID, v.ID );
    }
    return cluster_eps;
}

//Old version complexity O(n ^ 2)
// int expandCluster(vector<Point> &List, Point &point, int minPts, int clusterID, double eps)
// {    
//     vector<Point> cluster = calculateCluster(List, point, eps); //Calculate cluster for the point

//     if (cluster.size() < minPts)
//     {
//         point.label = NOISE;
//         return FAILURE;
//     }
//     else 
//     {
//         int index = 0, indexCorePoint = 0;
//         point.label = clusterID;
//         //the whole cluster has clusterID
//         for(auto v: cluster)
//         {
//             List[v.ID].label = clusterID;
//             if (v.x == point.x && v.y == point.y) //to find our core point in order to erase it
//             {
//                 indexCorePoint = index;
//             }
//             ++index;
//         }
//         //printf("Core point %d\n", List[point.ID].label);
//         cluster.erase (cluster.begin() + indexCorePoint);
//         //need to erase point from cluster to do after

//         for (auto v: cluster)
//         {
//             vector<Point> clusterNeigbors = calculateCluster(List, v, eps);//find all neighbours of every point in cluster
//             if (clusterNeigbors.size() >= minPts)
//             {
//                 for (auto neighbor: clusterNeigbors)
//                 {
//                     if (List[neighbor.ID].label == UNCLASSIFIED || List[neighbor.ID].label == NOISE)
//                     {
//                         if (List[neighbor.ID].label == UNCLASSIFIED )
//                         {
//                             cluster.push_back(neighbor);
//                         }
//                         List[neighbor.ID].label = clusterID;
//                     }
//                 }
//             }
//         }
//         return SUCCESS;
//     }
// }

int DBSCAN::expandCluster(vector<Point> &List, Point &point, int minPts, int clusterID, double eps, DSU &UF){
    
    UF.set_parent(point.ID, clusterID);
    vector<Point> cluster = calculateCluster(List, point, eps);
    for(auto& neighbor : cluster){
        if(List[neighbor.ID].label >= 0){ // classified
            UF.join(List[neighbor.ID].label, clusterID);
        }
        List[neighbor.ID].label = UF.find(clusterID);
        // printf("%d %d\n", neighbor.ID, UF.find(clusterID));
    }

    return SUCCESS;
}

int DBSCAN::fit(vector<Point> &List, int minPts, double eps)
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
            core_points_id.push_back(point.ID);
        }
    }

    for(auto id : core_points_id){
        auto& point = List[id];
        expandCluster(List, point, minPts, point.ID, eps, UF);
    }

    for(auto &point : List){
        printf("%d %d %d\n", point.label, point.x, point.y);
    }
    return UF.size-(List.size()-core_points_id.size()); //how many clusters exist
}


int main()
{
    vector<Point> List;
    DBSCAN clustering;
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
    printf("%d\n", clustering.fit(List, m_minPts, eps));
}
