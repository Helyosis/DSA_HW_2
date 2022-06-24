//
// Created by helyosis on 23/06/22.
//

#include "Game.h"

bool contains(vector<pair<int, int>> v, pair<int, int> val) {
    return find(v.begin(), v.end(), val) != v.end();
}

void Game::next_step() {
    if (!path_set) {
        path_set = true;
        path = graph.shortest_path_to(coord_to_node({playerX, playerY}), coord_to_node({objectiveX, objectiveY}));
    }

    pair<int, int> newCoord = node_to_coord(path.back());
    if (path.size() > 0)
        path.pop_back();

    playerX = newCoord.first;
    playerY = newCoord.second;
}

void Game::print() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (contains(obstacles, {x, y})) {
                cout << OBSTACLE_ICON;
            }
            if (x == playerX && y == playerY) {
                cout << PLAYER_ICON;
            } else if (x == objectiveX && y == objectiveY) {
                cout << OBJECTIVE_ICON;
            } else {
                cout << EMPTY_ICON;
            }
        }
        cout << endl;
    }
}

void Game::setup_graph() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (x + 1 < width)
                graph.add_link(coord_to_node({x, y}), coord_to_node({x + 1, y}));
            if (x - 1 >= 0)
                graph.add_link(coord_to_node({x, y}), coord_to_node({x - 1, y}));
            if (y + 1 < height)
                graph.add_link(coord_to_node({x, y}), coord_to_node({x, y + 1}));
            if (y - 1 >= 0)
                graph.add_link(coord_to_node({x, y}), coord_to_node({x, y - 1}));
        }
    }
}

Game::Game(pair<int, int> playerCoord, pair<int, int> objectiveCoord, int width, int height) {
    objectiveX = objectiveCoord.first;
    objectiveY = objectiveCoord.second;
    this->width = width;
    this->height = height;
    playerX = playerCoord.first;
    playerY = playerCoord.second;

    graph = Graph(width * height);
    setup_graph();
}

int Game::coord_to_node(pair<int, int> p) const {
    return p.first + p.second * width;
}

pair<int, int> Game::node_to_coord(int n) const {
    return {
        n % width,
        n / width
    };
}

/*
 * Add an obstacle at specified coord by removing corresponding graph nodes and all its vertices.
 */
void Game::add_obstacle(pair<int, int> coord) {
    graph.remove_node(coord_to_node(coord));
    obstacles.push_back(coord);
}
