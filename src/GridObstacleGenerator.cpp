//
//  obstacle_generator.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//


#define _USE_MATH_DEFINES

#include "Grid.hpp"


#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "util.hpp"

#define N_OBSTACLES 16
#define MIN_OBSTACLE_RADIUS GRID_SIZE/8
#define MAX_OBSTACLE_RADIUS GRID_SIZE/4

void Grid::generateObstacles() {
    // NOTE: this algorithm is not deterministic
    clearRect(0, 0, GRID_SIZE, GRID_SIZE);

    // helper structure to save obstacles in a vector
    class Obstacle {
      public:
        int center_x, center_y;
        int radius;
    };

    std::vector<Obstacle> obstacles;

    while (obstacles.size() < N_OBSTACLES) {
        int center_x = std::rand() % GRID_SIZE;
        int center_y = std::rand() % GRID_SIZE;
        int radius = std::rand() % (MAX_OBSTACLE_RADIUS - MIN_OBSTACLE_RADIUS) + MIN_OBSTACLE_RADIUS;
        bool too_close = false;

        for (Obstacle obstacle : obstacles) {
            int const distance_x = obstacle.center_x - center_x;
            int const distance_y = obstacle.center_y - center_y;
            int dist = distance(distance_x, distance_y);

            if (dist < obstacle.radius + radius) {
                if (dist < 0) {



                    radius = std::min(radius,dist*(radius / abs(obstacle.radius + radius)));
                    obstacle.radius = std::min(obstacle.radius,dist*(obstacle.radius / (obstacle.radius + radius)));
                } else {
                    radius = 0;
                    obstacle.radius = 0;
                }
            }
        }



        obstacles.push_back({ center_x, center_y, radius });
    }

    for (Obstacle obstacle : obstacles) {
        double const first_alpha = frand(0., M_PI * 2);
        double const last_alpha =
            std::fmod(first_alpha + frand(1.25*M_PI, 2*M_PI), M_PI * 2);

        drawArc(obstacle.center_x, obstacle.center_y, obstacle.radius, first_alpha, last_alpha);
    }
}