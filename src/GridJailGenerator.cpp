//
//  GridJailGenerator.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"
#define _USE_MATH_DEFINES
#include <cmath>

void Grid::generateJail() {
  clearRect(0, 0, GRID_SIZE, GRID_SIZE);
  drawArc(0, 0, GRID_SIZE / 2, 0, M_PI / 2);
}
