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
#include "ScoreSystem.h"



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
	GridElement* getGhostLocation(int);

	void setPointsystem();

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

	void ghostAStarSearch();
	void ghostGreedySearch();

	void ghostDepthFirstSearch();
	void ghostDepthFirstSearch(bool);

	bool pacMove(Direction nextMove);

	string getGameState();
	void setGameState(string);
	void gameSoundLoad(string);
	void gameSoundPlay();
	bool gameSoundisPlaying();

	void displayGameOverScreen();


  private:
    GridElement grid[GRID_SIZE][GRID_SIZE];
	ofTimer timer;
	GridElement* pacLocation;
	GridElement* ghostLocation[3];
	enum { astar, greedy, depthfirst };

	GridElement* pointsystemLocation;
	ScoreSystem score_sys = ScoreSystem(MAX_SCORE);

	string gameState;
	ofSoundPlayer gameSound;
	ofTrueTypeFont gameText;

	
	
};

#endif /* Grid_hpp */
