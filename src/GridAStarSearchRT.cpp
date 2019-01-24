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


