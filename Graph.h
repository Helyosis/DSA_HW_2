#ifndef PROJECT_GRAPH_H
#define PROJECT_GRAPH_H

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Graph {
private:
    vector<vector<int>> nodes;

public:
    Graph(int nbNodes);
    void add_link(int from, int to);
    void remove_link(int from, int to);
    void remove_node(int n);
    vector<int> shortest_path_to(int from, int to);
};


#endif //PROJECT_GRAPH_H
