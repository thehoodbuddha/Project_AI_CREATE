//
//  GridElement.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#include "GridElement.hpp"

#include <cstdio>

#include "ofMain.h"

#include "constants.h"

GridElement::GridElement() {
  // reset all neighbours
	fade_amount = 10;
	fade_inital = 80;

  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    neighbours[direction] = nullptr;
	
  }
 

  reset();
}/* void GridElement::setup() {
	ofImage img;
	img.loadImage("pac.png");
}
*/
void GridElement::reset() {
  resetWalls();
  resetSearch();
  haspoint = false;

}

void GridElement::resetWalls() {
  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    walls[direction] = true;
  }
}

void GridElement::resetSearch() {
  visited = false;
  marked = false;
 // pacmanVisited = false;
  parent = nullptr;
  path_length = -1;
  distance = -1;
}
void GridElement::setPoint(int weight) {
	haspoint = true;
	score_weight = weight;
}
void GridElement::deletePoint() {
	haspoint = false;
}


void GridElement::draw(){
	// draw background if visited
	/*
	if (visited) {
		ofSetColor(200);
		ofDrawRectangle(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
			GRID_ELEMENT_WIDTH, GRID_ELEMENT_HEIGHT);
	}
	*/
	// draw circle if marked
	if (marked) {

		ofSetColor(255, 0, 0);
		ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
			(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
			GRID_ELEMENT_HEIGHT * 0.5);
		//ofSetColor(0);
		//ofDrawBitmapString(score, (x + 0.5) * GRID_ELEMENT_WIDTH, (y + 0.5) * GRID_ELEMENT_HEIGHT);
	}

	// draw where pacman is
	if (pacmanVisited) {
		ofSetColor(255, 0, 0);
		ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
			(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
			GRID_ELEMENT_HEIGHT * 0.5);

	}
	// img.draw((x + 0.5) * GRID_ELEMENT_WIDTH,
	   //  (y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
   //	  GRID_ELEMENT_HEIGHT * 0.5);
	
	if (haspoint) {
		
		fade_inital += fade_amount;
		if (fade_inital >= 100 || fade_inital <=10) {
			fade_amount = -fade_amount;
		}
		
	
		//std::cout << fade_inital << std::endl;

		switch (score_weight) {
		case 1: ofSetColor(102, 255, 51,fade_inital);
			ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
				(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
				GRID_ELEMENT_HEIGHT * 0.5);
				break;
		case 2: 
			ofSetColor(255, 0, 255,fade_inital);
			ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
				(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
				GRID_ELEMENT_HEIGHT * 0.5);
				break;
		case 3:
			ofSetColor(0, 255, 255,fade_inital);
			ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
				(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
				GRID_ELEMENT_HEIGHT * 0.5);
			break;

		case 4:
			ofSetColor(255, 204, 0,fade_inital);
			ofDrawEllipse((x + 0.5) * GRID_ELEMENT_WIDTH,
				(y + 0.5) * GRID_ELEMENT_HEIGHT, GRID_ELEMENT_WIDTH * 0.5,
				GRID_ELEMENT_HEIGHT * 0.5);
			break;


		}
		
	}
	
  // draw all walls
  for (int direction = 0; direction < N_DIRECTIONS; direction++) {
    if (walls[direction]) {
      drawWall((Direction)direction);
    }
  }
}

void GridElement::drawWall(Direction direction) const {
  ofSetColor(0);

  switch (direction) {
    case DirectionNorth:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionEast:
      ofDrawLine((x + 1) * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionSouth:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT,
                 (x + 1) * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;

    case DirectionWest:
      ofDrawLine(x * GRID_ELEMENT_WIDTH, y * GRID_ELEMENT_HEIGHT,
                 x * GRID_ELEMENT_WIDTH, (y + 1) * GRID_ELEMENT_HEIGHT);
      break;
  }
}

void GridElement::setWall(Direction direction, bool is_solid) {
  walls[direction] = is_solid;

  // set opposite wall if it exists
  if (neighbours[direction] != NULL) {
    neighbours[direction]->walls[oppositeDirection(direction)] = is_solid;
  }
}

bool GridElement::hasWall(Direction direction) const {
  return walls[direction];
}

bool GridElement::wasVisited(Direction direction) const {
  return (neighbours[direction]->visited);
}

int GridElement::getX() const { return x; }

int GridElement::getY() const { return y; }

bool GridElement::get_hasPoint() { return haspoint; }

void GridElement::setCoordinate(int x, int y) {
  this->x = x;
  this->y = y;
}


bool GridElement::hasNeighbour(Direction direction) const {
  return (neighbours[direction] != NULL);
}

GridElement* GridElement::getNeighbour(Direction direction) const {
  return neighbours[direction];
}

void GridElement::setNeighbour(Direction direction, GridElement* newNeighour) {
  neighbours[direction] = newNeighour;
}

int GridElement::manhattanDistance(GridElement const* other) const {
  return (std::abs(x - other->x) + std::abs(y - other->y));
}

int GridElement::get_hasPointWeight() {return score_weight;}

void GridElement::visit() { visited = true; }

void GridElement::mark() { marked = true; }

void GridElement::pacmanVisit() { pacmanVisited = true; }

bool GridElement::pacmanHasVisted() { return pacmanVisited;  }

void GridElement::pacmanLeave() { pacmanVisited = false; }

bool GridElement::hasParent() const { return parent != nullptr; }

GridElement* GridElement::getParent() const { return parent; }

void GridElement::setParent(GridElement* parent) { this->parent = parent; }

int GridElement::getPathLength() const { return path_length; }

void GridElement::setPathLength(int path_length) {
  this->path_length = path_length;
}

int GridElement::getDistance() const { return distance; }

void GridElement::setDistance(int distance) { this->distance = distance; }

void GridElement::setScore(int score) { this->score = score; }

int GridElement::getScore() { return score; }