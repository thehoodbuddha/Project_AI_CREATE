//
//  room_generator.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include "Grid.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

#define N_ROOMS 5

void Grid::generateRooms() {
  double room_width = (double)GRID_SIZE / N_ROOMS;
  int room_height = GRID_SIZE / 3;

  for (int i = 0; i < N_ROOMS; i++) {
    int first_x = (int)std::floor(i * room_width);
    int last_x = (int)std::floor((i + 1) * room_width) - 1;

    int width = last_x - first_x + 1;

    double door_center_x = (first_x + last_x) / 2.0;

    int door_x = (int)std::floor(door_center_x);

    int door_width = (int)std::ceil(door_center_x + 1) - door_x;

    // clear room and door
    clearRect(first_x, 0, width, room_height);
    clearRect(door_x, room_height - 1, door_width, 2);

    // repeat for bottom
    clearRect(first_x, GRID_SIZE - room_height, width, room_height);
    clearRect(door_x, GRID_SIZE - room_height - 1, door_width, 2);
  }

  // clear center area
  clearRect(0, room_height, GRID_SIZE, GRID_SIZE - 2 * room_height);
}
