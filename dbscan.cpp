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

    std::vector<bool> classified;
    for(int point = 0; point < total_pts; ++point){
        std::vector<int> neighbors = getNeighbors(point, total_pts, distance_matrix);
        
        if(neighbors.size() < min_pts - 1) continue; // noise
        labels[point] = CORE;

        for(auto neighbor : neighbors){
            if(labels[neighbor] == BORDER) continue; // classified as border
            disjoint_set.join(neighbor, point);
            if(labels[neighbor] == NOISE) labels[neighbor] = BORDER;
        }
    }

    std::vector<int> reindex(total_pts, -1); // -1 noise or not reindexed
    
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
    labels.resize(total_pts, NOISE); // -1 if noise
    n_cluster = 0;

    if (algo != "BFS" && algo != "DSU") 
        throw std::invalid_argument("\'" + algo + "\'" + " is not a valid method");

    algo == "BFS" ? fit_bfs(distance_matrix, total_pts) : fit_dsu(distance_matrix, total_pts);
} 