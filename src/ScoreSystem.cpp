#include "ScoreSystem.h"


ScoreSystem::ScoreSystem(int max_score) {
	maxscore = max_score;
//	bar_info.load("ARCADECLASSIC.TTF", 50);
//bar_info.setLineHeight(18.0f);
//	bar_info.setLetterSpacing(1.037);
}
void ScoreSystem::Score_add(float add_amount) { maxscore += add_amount; };

void ScoreSystem::Display_Score() {
	//int size_x = bar_info.stringWidth(maxscore);
	//.drawString(maxscore, WINDOW_WIDTH / 2 / 2, WINDOW_HEIGHT / 2);
}

float ScoreSystem::Score_return() { return maxscore; }



