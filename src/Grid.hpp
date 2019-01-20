//
//  Grid.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef Grid_hpp
#define Grid_hpp

#include "GridElement.hpp"
#include "constants.h"
#include "ofMain.h"
#define N_WALLS_TO_BE_REMOVED 150

class Grid : public ofThread{
  public:
    Grid();

    void reset();
    void resetSearch();

    void draw();

    // methods for manipulating walls
    void clearRect(int, int, int, int);
    void drawArc(int, int, int, double, double);

    GridElement* getStart();
    GridElement* getEnd();
	GridElement* getPacLocation();
	GridElement* getGhostLocation();


    void generateMaze();
    void generateRooms();
    void generateObstacles();
    void generateJail();

    void depthFirstSearch();
    void depthFirstSearch(bool);
    void breadthFirstSearch();
    void greedySearch();
    void aStarSearch();
	void aStarSearchRT();

	void pacMove(Direction nextMove);


  private:
    GridElement grid[GRID_SIZE][GRID_SIZE];
	ofTimer timer;

	GridElement* pacLocation;
	GridElement* ghostLocation;
};

#endif /* Grid_hpp */
