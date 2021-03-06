//
//  GridDepthFirstSearch.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include <cstdlib>
#include <iostream>
#include <stack>

#include "Grid.hpp"
void Grid::ghostDepthFirstSearch() {
	Grid::ghostDepthFirstSearch(false);
}

void Grid::ghostDepthFirstSearch(bool searchRandom) {
	std::stack<GridElement*> stack;

	GridElement* start_element = getPacLocation();
	GridElement* end_element = getGhostLocation(depthfirst);

	stack.push(start_element);

	int states = 0;
	bool found_end = false;
	bool ghost_moved = false;
	while (!stack.empty()) {
		GridElement* current_element = stack.top();
		current_element->visit();

		states++;

		if (current_element == end_element) {
			// found end, so stop
			found_end = true;
			break;
		}

		int n_unvisited_directions = 0;
		Direction unvisited_directions[N_DIRECTIONS];

		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (!current_element->hasWall((Direction)direction) &&
				!current_element->wasVisited((Direction)direction)) {
				unvisited_directions[n_unvisited_directions++] = (Direction)direction;
			}
		}

		if (n_unvisited_directions == 0) {
			stack.pop();

			continue;
		}

		int nextindex = searchRandom ? std::rand() % n_unvisited_directions : 0;
		Direction next_direction =
			unvisited_directions[nextindex];

		GridElement* next_element = current_element->getNeighbour(next_direction);
		stack.push(next_element);



	}

	int const path_length = stack.size();

	//TODO: most likely it is not important to flush the whole stack
	while (!stack.empty()) {
		GridElement* path_element = stack.top();
		//path_element->mark();
		if (!ghost_moved && stack.size() >= 2)
		{
			stack.pop();
			ghostLocation[depthfirst] = stack.top();
			ghost_moved = true;
			stack.push(path_element);
		}
		stack.pop();

	}

	// print result
	if (!found_end) {
		std::cout << "DFS(end not found)" << '\n';
	}
	else {
		if (searchRandom) {
			std::cout << "DFS Random(states: " << states << ", path length: " << path_length
				<< ")" << '\n';
		}
		else {
			std::cout << "DFS(states: " << states << ", path length: " << path_length
				<< ")" << '\n';
		}
	}

}