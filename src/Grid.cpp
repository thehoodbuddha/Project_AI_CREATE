//
//  Grid.cpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#define _USE_MATH_DEFINES

#include "Grid.hpp"

#include <algorithm>

#include <cassert>
#include <cmath>

#include "Direction.hpp"
#include "util.hpp"

Grid::Grid() {
  // set positions and neighbours of all elements
  for (int y = 0; y < GRID_SIZE; y++) {
    for (int x = 0; x < GRID_SIZE; x++) {
      grid[x][y].setCoordinate(x, y);

      if (x > 0) {
        grid[x][y].setNeighbour(DirectionWest, &grid[x - 1][y]);
      }

      if (x < GRID_SIZE - 1) {
        grid[x][y].setNeighbour(DirectionEast, &grid[x + 1][y]);
      }

      if (y > 0) {
        grid[x][y].setNeighbour(DirectionNorth, &grid[x][y - 1]);
      }

      if (y < GRID_SIZE - 1) {
        grid[x][y].setNeighbour(DirectionSouth, &grid[x][y + 1]);
      }
    }
  }


 

  pacLocation = &grid[0][0];
  pacLocation->pacmanVisit();
  ghostLocation[astar] = &grid[GRID_SIZE - 1][GRID_SIZE - 1];
  ghostLocation[greedy] = &grid[0][GRID_SIZE - 1];
  ghostLocation[depthfirst] = &grid[GRID_SIZE - 1][0];


  gameState = "not_started";

  gameText.load("ARCADECLASSIC.TTF", 28);
  gameText.setLineHeight(18.0f);
  gameText.setLetterSpacing(1.037);
  score_system = new ScoreSystem(10);

 
}

void Grid::reset() {
  // reset all elements
  for (int y = 0; y < GRID_SIZE; y++) {
    for (int x = 0; x < GRID_SIZE; x++) {
      grid[x][y].reset();
    }
  }
}

void Grid::setPointsystem() {//int amountofpoints) {                    //generates a randompoint system in the grid. 
	//RAND_MAX = 20;

		//std::cout << (std::rand() % 100 + 1) << std::endl;
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			if ((std::rand() & 2 + 0) > 1) {
	
				pointsystemLocation = &grid[x][y];
				int x = std::rand() % 4 + 1;
				score_system->add_maxScore(x);                //add to the maxscore system, every iteration. 
				pointsystemLocation->setPoint(x);             //set a point with a certain score weight. 

				
			}
		}
	}
}

bool Grid::gamegoal_reached() {
	 	if (score_system->get_maxScore() == score_system->Score_return()) {
		return true;
	}else{return false; }
	
}

void Grid::resetSearch() {
  // reset all elements
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			grid[x][y].resetSearch();
		}
	}
	int x = getGhostLocation(astar)->getX();
	int y = getGhostLocation(astar)->getY();
	grid[x][y].mark();
	x = getGhostLocation(greedy)->getX();
	y = getGhostLocation(greedy)->getY();
	grid[x][y].mark();
	x = getGhostLocation(depthfirst)->getX();
	y = getGhostLocation(depthfirst)->getY();
	grid[x][y].mark();


}

void Grid::draw() {
  // draw all elements
	score_system->Display_Score();
	for (int y = 0; y < GRID_SIZE; y++) {
		for (int x = 0; x < GRID_SIZE; x++) {
			grid[x][y].draw();
			//pointsystemLocation->draw();
		}
	}
}

void Grid::clearRect(int first_x, int first_y, int width, int height) {
  int last_x = first_x + width - 1;
  int last_y = first_y + height - 1;

  for (int y = first_y; y <= last_y; y++) {
    for (int x = first_x; x <= last_x; x++) {
      if (x != first_x) {
        grid[x][y].setWall(DirectionWest, false);
      }

      if (x != last_x) {
        grid[x][y].setWall(DirectionEast, false);
      }

      if (y != first_y) {
        grid[x][y].setWall(DirectionNorth, false);
      }

      if (y != last_y) {
        grid[x][y].setWall(DirectionSouth, false);
      }
    }
  }
}

void Grid::drawArc(int x_center, int y_center, int radius, double first_alpha,
                   double last_alpha) {
  assert(first_alpha >= 0.0 && first_alpha <= M_PI * 2);
  assert(last_alpha >= 0.0 && last_alpha <= M_PI * 2);

  for (int y = std::max(0, y_center - radius);
       y <= std::min(y_center + radius, GRID_SIZE - 1); y++) {
    for (int x = std::max(0, x_center - radius);
         x <= std::min(x_center + radius, GRID_SIZE - 1); x++) {
      int const x_relative = x - x_center;
      int const y_relative = y - y_center;

      double const alpha =
          std::fmod(M_PI * 2 + std::atan2(x_relative, y_relative), M_PI * 2);

      // stop if outside of arc angle range
      if (last_alpha >= first_alpha) {
        if (alpha < first_alpha || alpha > last_alpha) {
          continue;
        }
      } else {
        if (alpha < first_alpha && alpha > last_alpha) {
          continue;
        }
      }

      // stop if outside of arc radius
      if (distance(x_relative, y_relative) >= radius) {
        continue;
      }

      for (int direction = 0; direction < N_DIRECTIONS; direction++) {
        if (grid[x][y].hasNeighbour((Direction)direction)) {
          GridElement* neighbour =
              grid[x][y].getNeighbour((Direction)direction);

          // mark wall if neighbour is outside of arc radius
          int const x_distance = neighbour->getX() - x_center;
          int const y_distance = neighbour->getY() - y_center;

          if (distance(x_distance, y_distance) >= radius) {
            grid[x][y].setWall((Direction)direction, true);
          }
        }
      }
    }
  }
}

GridElement* Grid::getStart() { return &grid[0][0]; }

GridElement* Grid::getEnd() { return &grid[GRID_SIZE - 1][GRID_SIZE - 1]; }

GridElement* Grid::getPacLocation() { return pacLocation; }

GridElement* Grid::getGhostLocation(int ghostType) { return ghostLocation[ghostType]; }


bool Grid::pacMove(Direction nextMove) {
	
	if (!pacLocation->hasWall((Direction)nextMove)) {
		pacLocation->pacmanLeave();
		pacLocation = pacLocation->getNeighbour((Direction)nextMove);
		pacLocation->pacmanVisit();
		pointsystemLocation = pacLocation;

		if (pointsystemLocation->get_hasPoint() == pacLocation->pacmanHasVisted()) {
			pointsystemLocation->deletePoint();
			score_system->Score_add(pointsystemLocation->get_hasPointWeight());

			//std::cout << "score" << score_sys.Score_return() << std::endl;
		}
		return true;
	}

	else
		return false;

}

string Grid::getGameState() { return gameState; }

void Grid::setGameState(string newGameState) { gameState = newGameState; }

void Grid::gameSoundLoad(string soundFileName) {
	gameSound.load("sounds/" + soundFileName);
	gameSound.setVolume(1.0f);
	gameSound.setLoop(true);
}
void Grid::gameSoundPlay() { gameSound.play(); }

bool Grid::gameSoundisPlaying() { return gameSound.isPlaying(); }

void Grid::displayGameOverScreen() {

	int size_x = gameText.stringWidth(END_GAME);
	gameText.drawString(END_GAME, WINDOW_WIDTH / 2 - size_x / 2, WINDOW_HEIGHT / 2);
	string end_score = to_string(score_system->Score_return());
	end_score = end_score + "out of" + to_string(score_system->get_maxScore());
	int size_y = gameText.stringHeight(end_score);
	gameText.drawString(end_score, WINDOW_WIDTH / 2 - size_x / 2, WINDOW_HEIGHT / 2 + size_y * 2);

}

void Grid::displayGameSplashScreen(){
	ofSetColor(255);
	int size_x, size_y;
	string splashMessage = "Use your head Nerd literally";
	size_x = gameText.stringWidth(splashMessage);
	gameText.drawString(splashMessage, WINDOW_WIDTH / 2 - size_x / 2, WINDOW_HEIGHT / 2);
	splashMessage = "A game by Anil and JP";
	size_x = gameText.stringWidth(splashMessage);
	size_y = gameText.stringHeight(splashMessage);
	gameText.drawString(splashMessage, WINDOW_WIDTH / 2 - size_x / 2, WINDOW_HEIGHT / 2 + 2 * size_y);


}