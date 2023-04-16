#include <iostream>
#include <vector>
#include "dbscan.hpp"


std::vector<int> DBSCAN::getNeighbors(int point_id, int total_pts, double** distance_matrix){
    std::vector<int> neighbors;
    for(int neighbor_id = 0; neighbor_id < total_pts; ++neighbor_id){
        double dist = distance_matrix[point_id][neighbor_id];
        if(dist <= eps && neighbor_id != point_id) neighbors.push_back(neighbor_id);
    }
    return neighbors;
}


void DBSCAN::fit_dsu(double** distance_matrix, int total_pts){
    DSU disjoint_set(total_pts);

    for(int point = 0; point < total_pts; ++point){
        std::vector<int> neighbors = getNeighbors(point, total_pts, distance_matrix);
        if(neighbors.size() < min_pts - 1) continue;
        for(auto neighbor : neighbors){
            disjoint_set.join(neighbor, point);
            labels[neighbor] = disjoint_set.find(point);
        }
        labels[point] = disjoint_set.find(point);
    }

    std::vector<int> reindex(total_pts, -1); // -1 noise or not reindexed
    int n_cluster = -1;
    
    for(int point = 0; point < total_pts; ++point){
        if(~labels[point]){ // not noise
            int id = disjoint_set.find(point);
            if(reindex[id] == -1) reindex[id] = ++n_cluster;
            labels[point] = reindex[id];
        }
    }
    
}

void DBSCAN::fit_bfs(double** distance_matrix, int total_pts){
    std::vector<bool> visited(total_pts);
    int n_cluster = -1;

    for(int point = 0; point < total_pts; ++point){
        
        if(visited[point]) continue;
        
        visited[point] = true;
        std::vector<int> neighbors = getNeighbors(point, total_pts, distance_matrix);
        if(neighbors.size() < min_pts - 1) continue; // if noise

        labels[point] = ++n_cluster;

        for(int i = 0; i < neighbors.size(); ++i){
            int& neighbor = neighbors[i];
            if(visited[neighbor]) continue; 
            
            labels[neighbor] = n_cluster;
            visited[neighbor] = true;
            std::vector<int> neighbors_neighbor = getNeighbors(neighbor, total_pts, distance_matrix);
            if(neighbors_neighbor.size() < min_pts - 1) continue; // if noise

            // expand neighbors
            for(auto neighbor_neighbor : neighbors_neighbor){
                if(!visited[neighbor_neighbor]) neighbors.push_back(neighbor_neighbor);
            }
        }
    }
}

void DBSCAN::fit(double** distance_matrix, int total_pts, std::string algo){
    // cleaning labels 
    labels.clear();
    labels.resize(total_pts, -1); // -1 if noise

    if (algo != "BFS" && algo != "DSU") 
        throw std::invalid_argument("\'" + algo + "\'" + " is not a method");
    
    algo == "BFS" ? fit_bfs(distance_matrix, total_pts) : fit_dsu(distance_matrix, total_pts);
} 

// testing
using namespace std;

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
    
    int total_pts = List.size();
    double** distance_matrix = new double*[total_pts];
    for(int i = 0; i < total_pts; ++i){
        distance_matrix[i] = new double[total_pts];
        for(int j = 0; j < total_pts; ++j){
            distance_matrix[i][j] = List[i].calculateDistance(List[j]);
        }
    }

    DBSCAN clustering(eps, m_minPts);
    clustering.fit(distance_matrix, total_pts, "DS");
    
    for(auto id : clustering.labels) cout << id << " ";
    cout << endl;
}