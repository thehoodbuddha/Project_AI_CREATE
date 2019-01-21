#pragma once
#ifndef GridPoints_h
#define GridPoints_h
#include "GridElement.hpp"
#include "Grid.hpp"

class GridPoints
{
public:
	GridPoints(int AmountOfPoints);
	void GeneratePoints();

private:
	int AmountOfPoints_;
};





#endif // !GrindPoints_h
