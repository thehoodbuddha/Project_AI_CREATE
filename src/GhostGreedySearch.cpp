//
//  GridGreedySearch.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//  Implemented by Anil Ozen s1943618
//

#include "Grid.hpp"

#include <iostream>

#include "PriorityQueue.hpp"

// distance comparison class for priority queue
class DistanceCompare {
public:
	bool operator()(GridElement const* a, GridElement const* b) const {
		return a->getDistance() > b->getDistance();
	}
};

void Grid::ghostGreedySearch() {
	// priority queue which sorts elements based on its manhattan distance to the
	// end (distance is a member of GridElement) for greedy search
	PriorityQueue<GridElement*, DistanceCompare> queue;

	GridElement* start_element = getPacLocation();
	GridElement* end_element = getGhostLocation(greedy);

	start_element->visit();

	queue.push(start_element);

	bool found_end = false;
	bool ghost_moved = false;
	int states = 0, path_length = 0;

	while (!queue.empty()) {
		GridElement* current_element = queue.front();
		queue.pop();
		states++;
		if (current_element == end_element) {
			found_end = true;

			while (current_element->hasParent()) {
				current_element = current_element->getParent();
				//current_element->mark();
				if (!ghost_moved)
				{
					ghostLocation[greedy] = current_element;
					ghost_moved = true;
				}
				//std::this_thread::sleep_for(std::chrono::milliseconds(100));

				path_length++;
			}

			//mark all left in queue as visited

			while (!queue.empty()) {
				GridElement* q_element = queue.front();
				q_element->visit();
				queue.pop();
			}

			break;

		}

		for (int direction = 0; direction < N_DIRECTIONS; direction++) {
			if (!current_element->hasWall((Direction)direction) &&
				!current_element->wasVisited((Direction)direction)) {
				GridElement* next_element =
					current_element->getNeighbour((Direction)direction);
				int manhattan_to_end = next_element->manhattanDistance(end_element);
				next_element->setDistance(manhattan_to_end);
				next_element->visit();
				next_element->setParent(current_element);
				queue.push(next_element);
			}
		}


	}

	// print result
	/*
	if (!found_end) {
		std::cout << "GFS(end not found)" << '\n';
	}
	else {
		std::cout << "GFS(states: " << states << ", path length: " << path_length
			<< ")" << '\n';
	}
	*/
}
