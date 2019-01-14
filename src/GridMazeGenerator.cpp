//
//  maze_generator.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include "Grid.hpp"

#include <cstdlib>
#include <stack>
#include <ctime>

void Grid::generateMaze() {
	//std::srand(std::time(0));
  std::stack<GridElement*> stack;

  // push first element (0, 0) on stack
  stack.push(&grid[0][0]);

  while (!stack.empty()) {
    // get next element
    GridElement* current_element = stack.top();
    current_element->visit();
    // find all unvisited directions
    int n_unvisited_directions = 0;
    Direction unvisited_directions[N_DIRECTIONS];

    for (int direction = 0; direction < N_DIRECTIONS; direction++) {
      if (current_element->hasNeighbour((Direction)direction) &&
          !current_element->wasVisited((Direction)direction)) {
        unvisited_directions[n_unvisited_directions] = (Direction)direction;
        n_unvisited_directions++;
      }
    }

    // backtrack if no possible directions are found
    if (n_unvisited_directions == 0) {
      stack.pop();
      continue;
    }

    // choose random direction from unvisited directions
    Direction next_direction =
        unvisited_directions[std::rand() % n_unvisited_directions];

    // remove wall in this direction
    current_element->setWall(next_direction, false);

    // push next element on stack
    GridElement* next_element = current_element->getNeighbour(next_direction);
    stack.push(next_element);
  }

  {
    // randomly remove some walls
    int n_walls_removed = 0;

    while (n_walls_removed < N_WALLS_TO_BE_REMOVED) {
      // choose random element and direction
      int x = std::rand() % GRID_SIZE;
      int y = std::rand() % GRID_SIZE;
      GridElement* current_element = &grid[x][y];

      Direction direction = (Direction)(std::rand() % N_DIRECTIONS);

      // remove wall if possible
      if (current_element->hasNeighbour(direction) &&
          current_element->hasWall(direction)) {
        current_element->setWall(direction, false);
        n_walls_removed++;
      }
    }
  }

  resetSearch();
}
