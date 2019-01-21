//
//  GridAStartSearch.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//  Implemented by Anil Ozen s1943618
//

#include "Grid.hpp"

#include <iostream>
#include <thread>
#include <chrono>

#include "PriorityQueue.hpp"
#include "ofMain.h"



// score comparison class for priority queue
class FScoreCompare {
public:
	bool operator()(GridElement const* a, GridElement const* b) const {
		return (a->getPathLength() + a->getDistance()) >
			(b->getPathLength() + b->getDistance());
	}
};

void Grid::ghostAStarSearch() {
	// priority queue which sorts elements based on the sum of its path length
	// since the start and manhattan distance to the end (path_length and distance
	// are members of GridElement) for A* search
	PriorityQueue<GridElement*, FScoreCompare> queue;

	//GridElement* start_element = getStart();
	GridElement* start_element = getPacLocation();
	GridElement* end_element = getGhostLocation(astar); // getGhostLocation();

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
						current_element->mark();
						ghostLocation[astar] = current_element;
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
			if (!current_element->hasWall((Direction)direction)) {
				GridElement* next_element =
					current_element->getNeighbour((Direction)direction);

				if (current_element->wasVisited((Direction)direction)) {
					if (current_element->getPathLength() + 1 < next_element->getPathLength()) {
						queue.erase(next_element);
					}
					else {
						continue;
					}
				}


				int manhattan_to_end = next_element->manhattanDistance(end_element);
				next_element->setDistance(manhattan_to_end);

				GridElement* iterator = current_element;
				int path_so_far = 1;
				while (iterator->hasParent())
				{
					iterator = iterator->getParent();
					path_so_far++;
				}

				next_element->setScore(path_so_far + manhattan_to_end);
				next_element->setPathLength(path_so_far);
				next_element->setDistance(manhattan_to_end);
				//std::this_thread::sleep_for(std::chrono::milliseconds(10));

				next_element->visit();

				next_element->setParent(current_element);
				queue.push(next_element);
			}

		}

	}

	// print result
	/*
	if (!found_end) {
		std::cout << "A*(end not found)" << '\n';
	}
	else {
		std::cout << "A*(states: " << states << ", path length: " << path_length
			<< ")" << '\n';
	}
	*/
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
