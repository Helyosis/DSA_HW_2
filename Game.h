#ifndef PROJECT_GAME_H
#define PROJECT_GAME_H

#include "Graph.h"

class Game {
private:
    Graph graph = Graph(0);
    vector<int> path;
    bool path_set = false;

    vector<pair<int, int>> obstacles;
    int playerX;
    int playerY;
    int objectiveX;
    int objectiveY;
    int width;
    int height;

    const string OBSTACLE_ICON = "#";
    const string PLAYER_ICON = "x";
    const string EMPTY_ICON = ".";
    const string OBJECTIVE_ICON = "@";

    void setup_graph();
    pair<int, int> node_to_coord(int n) const;
    int coord_to_node(pair<int, int> p) const;
public:
    Game(pair<int, int> playerCoord, pair<int, int> objectiveCoord, int width = 20, int height = 40);
    void next_step();
    void print();
    void add_obstacle(pair<int, int> obstacleCoord);
};


#endif //PROJECT_GAME_H
