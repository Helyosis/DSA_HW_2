#include <iostream>

#include "Game.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
    cout << "What are the player coordinates ?" << endl;
    cout << "x: ";
    int x;
    cin >> x;
    cout << "y: ";
    int y;
    pair<int, int> playerCoord{x, y};
    cin >> y;
    cout << "What are the objective coordinates ?" << endl;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;
    pair<int, int> objectiveCoord{x, y};

    Game game(playerCoord, objectiveCoord);
    cout << "How many obstacles do you want to add ?" << endl;
    int nbObstacles;
    cin >> nbObstacles;
    for (int i = 0; i < nbObstacles; ++i) {
        cout << "Obstacle " << i << endl;
        cout << "x: ";
        int obstacleX;
        cin >> obstacleX;
        cout << "y: ";
        int obstacleY;
        cin >> obstacleY;

        game.add_obstacle({obstacleX, obstacleY});
    }

    while (true) {
        game.print();
        game.next_step();
        sleep(1);
    }
}
