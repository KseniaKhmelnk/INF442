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

vector<int> DBSCAN::getNeighbors(int point_id, int total_pts, double** distance_matrix){
    vector<int> neighbors;
    for(int neighbor_id = 0; neighbor_id < total_pts; ++neighbor_id){
        double dist = distance_matrix[point_id][neighbor_id];
        if(dist <= eps && neighbor_id != point_id) neighbors.push_back(neighbor_id);
    }
    return neighbors;
}

void DBSCAN::fit_bfs(double** distance_matrix, int total_pts){
    vector<bool> visited(total_pts);
    vector<int> label(total_pts, -1); // -1 if NOISE
    int n_cluster = -1;

    for(int point = 0; point < total_pts; ++point){
        
        if(visited[point]) continue;
        
        visited[point] = true;
        vector<int> neighbors = getNeighbors(point, total_pts, distance_matrix);

        if(neighbors.size() < min_pts) continue; // if noise, dont expand

        label[point] = ++n_cluster;

        for(int neighbor : neighbors){
            if(visited[neighbor]) continue;
            label[neighbor] = n_cluster;
            visited[neighbor] = true;
            vector<int> neighbors_neighbor = getNeighbors(neighbor, total_pts, distance_matrix);
            if(neighbors_neighbor.size() < min_pts) continue;

            // expand neighbors
            for(auto neighbor_neighbor : neighbors_neighbor){
                if(!visited[neighbor_neighbor]) neighbors.push_back(neighbor_neighbor);
            }
        }

        // print
        for(auto id : label) cout << id << " ";
        cout <<  endl;
    }
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