#pragma once
#ifndef ScoreSystem_h
#define ScoreSystem_h
#include "constants.h"

class ScoreSystem
{
public:
	ScoreSystem(int max_score);
	void Score_add(float add_amount);
	float Score_return();
	void Display_Score();

private:
	float maxscore;
//	ofTrueTypeFont bar_info;
	//ofTrueTypeFont gameText;
};





#endif // !visual_h







