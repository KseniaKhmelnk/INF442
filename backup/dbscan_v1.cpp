#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "dbscan_v1.hpp"

using namespace std;

double Point::calculateDistance(const Point& pointTarget)
{
    return sqrt(pow(this->x - pointTarget.x, 2) + pow(this->y - pointTarget.y, 2));
}

vector<int> DBSCAN::calculateCluster(vector<Point> &data, Point &center_point)
{
    int index = 0;
    //initialize cluster_eps
    vector<int> cluster_eps;
    for(auto point : data)
    {
        if (center_point.calculateDistance(point) <= eps)
        {
            cluster_eps.push_back(point.ID);
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

int DBSCAN::expandCluster(vector<Point> &data, Point &center_point){
    vector<int> cluster_eps;
    for(auto point : data)
    {
        if (center_point.calculateDistance(point) <= eps)
        {
            cluster_eps.push_back(point.ID);
        }
    }

    if(cluster_eps.size() < min_pts) return FAILURE;

    for(auto& neighbor_ID : cluster_eps){
        if(data[neighbor_ID].label >= 0){ // classified
            disjoint_set->join(data[neighbor_ID].label, center_point.ID);
        }
        data[neighbor_ID].label = disjoint_set->find(center_point.ID);
    }

    return SUCCESS;
}

int DBSCAN::fit(vector<Point> &data)
{
    disjoint_set = new DSU((int) data.size());;
    
    int noises = 0;
    for(auto &point : data){
        if(calculateCluster(data, point).size() >= min_pts){
            ++noises;
            expandCluster(data, point);
        }
    }

    for(auto &point : data){
        printf("%d %d %d\n", point.label, point.x, point.y);
    }

    return disjoint_set->size-(data.size()-noises); //how many clusters exist
}

int main()
{
    vector<Point> List;
    double eps = 3;
    int m_minPts = 2, n;
    int i = 0;
    cin >> n;
    DBSCAN clustering(eps, m_minPts);
    while(n--)
    {
        int x, y;
        cin >> x >> y;
        List.push_back(Point(x, y, i));
        i++; 
    }
    printf("%d\n", clustering.fit(List));
}

// FIT
// VERSION 1
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

    // VERSION 2
    // vector<int> core_points_id;
    // for(auto &point : List){
    //     if(calculateCluster(List, point).size() >= min_pts){
    //         core_points_id.push_back(point.ID);
    //     }
    // }

    // for(auto id : core_points_id){
    //     auto& point = List[id];
    //     expandCluster(List, point);
    // }
