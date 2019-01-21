#pragma once
#ifndef ScoreSystem_h
#define ScoreSystem_h


class ScoreSystem
{
public:
	ScoreSystem(int max_score);
	void Score_add(float add_amount);
	float Score_return();
private:
	float maxscore;
};





#endif // !visual_h










