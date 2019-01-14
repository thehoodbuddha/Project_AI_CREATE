//
//  GridBreadthFirstSearch.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/2016.
//
//

#include "Grid.hpp"

#include <iostream>
#include <queue>

void Grid::breadthFirstSearch() {
    std::queue<GridElement*> queue;

    GridElement* start_element = getStart();
    GridElement* end_element = getEnd();

    start_element->visit();

    queue.push(start_element);

    bool found_end = false;
    int states = 0, path_length = 0;

    while (!queue.empty()) {
        GridElement* current_element = queue.front();
        queue.pop();

        states++;

        if (current_element == end_element) {
            end_element->mark();
            // found end, so stop
            found_end = true;

            while (current_element->hasParent()) {
                current_element = current_element->getParent();
                current_element->mark();
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
                next_element->visit();
                next_element->setParent(current_element);
                queue.push(next_element);
            }
        }


    }

    // print result
    if (!found_end) {
        std::cout << "BFS(end not found)" << '\n';
    } else {
        std::cout << "BFS(states: " << states << ", path length: " << path_length
                  << ")" << '\n';
    }
}
