#include "ScoreSystem.h"
#include <string> 

ScoreSystem::ScoreSystem(int initial_score) {
	current_score = initial_score;
	bar_info.load("ARCADECLASSIC.TTF",  INFOBAR_SIZE);
	bar_info.setLineHeight(18.0f);
	bar_info.setLetterSpacing(1.037);
	max_score = 0;
	//bar_info.drawString(max
	//)
}
void ScoreSystem::Score_add(float add_amount) { current_score += add_amount; };

void ScoreSystem::Display_Score() {
	//int size_x = bar_info.stringWidth(maxscore);
	auto s = std::to_string(current_score);
	//.drawString(maxscore, WINDOW_WIDTH / 2 / 2, WINDOW_HEIGHT / 2);
	bar_info.drawString("SCORE "+s, 0 , WINDOW_HEIGHT + INFOBAR_SIZE);
}

void ScoreSystem::add_maxScore(int amount) {
	max_score += amount; 
	
}
int ScoreSystem::Score_return() { return current_score; }

 int ScoreSystem::get_maxScore() { return max_score; }

