#pragma once
#ifndef ScoreSystem_h
#define ScoreSystem_h
#include "constants.h"
#include "ofMain.h"
class ScoreSystem
{
public:
	ScoreSystem(int initial_poins);
	void Score_add(float add_amount);
	int Score_return();
	void Display_Score();
	void set_maxScore(int amount);
	int get_maxScore();
private:

	int current_score;
	int max_score; 

	ofTrueTypeFont bar_info;
	//ofTrueTypeFont gameText;
};





#endif // !visual_h







