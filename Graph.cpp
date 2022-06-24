//
// Created by helyosis on 23/06/22.
//

#include "Graph.h"
#include <limits.h>
#include <queue>

class
{
public:
    bool operator()(pair<int, int> first, pair<int, int> second) {
        return first.second < second.second;
    }
} compare;

bool contains(vector<int> v, int val) {
    return find(v.begin(), v.end(), val) != v.end();
}

int get_tentative_distance_of_neighbor(vector<pair<int, int>>& tentative_distances, int n) {
    for (auto it = tentative_distances.begin(); it != tentative_distances.end(); ++it) {
        pair<int, int> p = *it;
        if (p.first == n) return p.second;
    }

    cout << "Error: No distance found for this neighbor";
    throw;
}

void set_tentative_distance_of_neighbor(vector<pair<int, int>>& tentative_distances, int n, int value) {
    for (auto it = tentative_distances.begin(); it != tentative_distances.end(); ++it) {
        pair<int, int>& p = *it;
        if (p.first == n) {
            p.second = value;
            return;
        }
    }

    cout << "Error: No distance found for this neighbor";
    throw;
}

void Graph::remove_node(int n) {
    vector<int> neighbours = nodes[n];
    for_each(neighbours.begin(), neighbours.end(), [this, n](int to) {
        remove_link(n, to);
        remove_link(to, n);
    });
}

void Graph::remove_link(int from, int to) {
    // No value found
    if (!contains(nodes[from], to)) {
        cout << "Error: Value not found in adjacence list" << endl;
        throw;
    }

    remove(nodes[from].begin(), nodes[from].end(), to);
}

void Graph::add_link(int from, int to) {
    nodes[from].push_back(to);
}

Graph::Graph(int nbNodes) {
    for (int i = 0; i < nbNodes; ++i) {
        vector<int> adjacenceList;
        nodes.push_back(adjacenceList);
    }
}

/*
 * Returns the list of node to traverse to go from the `from` node to the `to` node.
 * The path is reversed to allow nodes enumeration from the back to the front (so with minimal overhead).
 */
vector<int> Graph::shortest_path_to(int from, int to) {
    vector<int> unvisited_nodes;
    vector<pair<int, int>> tentative_distances;
    vector<int> prev;
    for (int i = 0; i < nodes.size(); ++i) {
        unvisited_nodes.push_back(i);

        pair<int, int> val{i, INT_MAX};
        if (i == from) val.second = 0;
        tentative_distances.push_back(val);

        prev.push_back(-1);
    }

    // While the destination node is unvisited;
    while(contains(unvisited_nodes, to)) {
        auto valIterator = min_element(tentative_distances.begin(), tentative_distances.end(), compare);
        pair<int, int> val = *valIterator;
        tentative_distances.erase(valIterator);

        int node = val.first;
        int dist = val.second;
        unvisited_nodes.erase(find(unvisited_nodes.begin(), unvisited_nodes.end(), node));

        // Get all unvisited neighbors
        vector<int> unvisited_neighbors;
        for (auto it = nodes[node].begin(); it != nodes[node].end(); ++it) {
            if (contains(unvisited_nodes, *it)) unvisited_neighbors.push_back(*it);
        }

        for (auto it = unvisited_neighbors.begin(); it != unvisited_neighbors.end(); ++it) {
            int oldDist = get_tentative_distance_of_neighbor(tentative_distances, *it);
            int newDist = dist + 1; // Because we are in an unweighted graph, the cost of a vertex will always be 1
            if (newDist < oldDist) {
                set_tentative_distance_of_neighbor(tentative_distances, *it, newDist);
                prev[*it] = node;
            }
        }
    }

    vector<int> path;
    int curr_node = to;
    // If curr_node == -1 -> last curr_node was `from`
    while (curr_node != -1) {
        path.push_back(curr_node);
        curr_node = prev[curr_node];
    }
    return path;
}
