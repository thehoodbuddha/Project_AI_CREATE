//
//  GridElement.hpp
//  SearchStrategies
//
//  Created by David Stritzl on 08/11/15.
//
//

#ifndef GridElement_hpp
#define GridElement_hpp

#include "Direction.hpp"

class GridElement {
 public:
  GridElement();

  void reset();
  void setup();
  void resetWalls();
  void resetSearch();
  
  void draw() ;
  void drawWall(Direction) const;
  void setWall(Direction, bool);
  bool hasWall(Direction) const;
  bool wasVisited(Direction) const;

  int getX() const;
  int getY() const;
  void setCoordinate(int, int);

  bool hasNeighbour(Direction) const;
  GridElement* getNeighbour(Direction) const;
  void setNeighbour(Direction, GridElement*);

  float neighbourDistance(GridElement const*) const;
  int manhattanDistance(GridElement const*) const;
 
  void visit();
  void mark();
  void pacmanVisit();
  void pacmanLeave();
  bool hasParent() const;
  GridElement* getParent() const;
  void setParent(GridElement*);
  int getPathLength() const;
  void setPathLength(int);
  int getDistance() const;
  void setDistance(int);
  void setScore(int);
  int getScore();

  void setPoint(int weight);
  void deletePoint();
  bool get_hasPoint();
  int get_hasPointWeight();
  bool pacmanHasVisted();

 private:
  int x, y;
  float fade_amount;
  float fade_inital;

  GridElement* neighbours[N_DIRECTIONS];
  bool walls[N_DIRECTIONS];

  // variables for maze generation and path finding
  bool visited;
  bool marked;
  bool pacmanVisited;
  bool haspoint;
  int score;

  GridElement* parent;

  int path_length;
  int distance;
  int score_weight; 
  

  //ofImage img; 
};

#endif /* GridElement_hpp */
