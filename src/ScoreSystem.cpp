#include "ScoreSystem.h"


ScoreSystem::ScoreSystem(int max_score) {
	maxscore = max_score;
}
void ScoreSystem::Score_add(float add_amount) {	 maxscore += add_amount;};

float ScoreSystem::Score_return() { return maxscore; }


