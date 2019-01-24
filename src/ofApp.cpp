/*

*/

#include "ofApp.h"
#include <thread>

//--------------------------------------------------------------
GridElement* pacStartLocation;




void ofApp::setup(){
	std::thread t(&EyeTracking::Eyetrack_Main, &track);
	t.detach();
	ofBackground(0);

	// init random generator
	std::srand((unsigned int)std::time(0));

	grid.generateMaze();
	grid.setPointsystem();

	pacStartLocation = grid.getPacLocation();

	millisSincePacMoved = 0;
	millisSinceGhostMoved = 0;


}

//--------------------------------------------------------------
void ofApp::update(){
	
	namespace sc = std::chrono;
	auto time = sc::system_clock::now(); // get the current time
	auto since_epoch = time.time_since_epoch(); // get the duration since epoch
	auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);



	int track_result = track.direction(track.locationPoint.x, track.locationPoint.y, WEBCAM_WIDTH, WEBCAM_HEIGHT);
	if (grid.getGameState() == "not_started")
	{
		
		switch (track_result) {
		case 3:
			if (grid.pacMove(DirectionWest)) 
				grid.setGameState("started");
			break;
		case 1:
			if (grid.pacMove(DirectionEast)) 
				grid.setGameState("started");
			break;
		case 0:
			if (grid.pacMove(DirectionNorth))
				grid.setGameState("started");
			break;
		case 2:
			if (grid.pacMove(DirectionSouth))
				grid.setGameState("started");
			break;

		}

	}
		


	if (grid.getGameState() == "started")
	{
	
		if (millis.count() - millisSincePacMoved >= 500)
		{
			millisSincePacMoved = millis.count();
			switch (track_result) {
			case 3:
				grid.pacMove(DirectionWest);
				break;
			case 1:
				grid.pacMove(DirectionEast);
				break;
			case 0:
				grid.pacMove(DirectionNorth);
				break;
			case 2:
				grid.pacMove(DirectionSouth);
				break;

			}
		}

		if (millis.count() - millisSinceGhostMoved >= 1000) {
			millisSinceGhostMoved = millis.count();
			grid.resetSearch();
			grid.ghostAStarSearch();
			grid.resetSearch();
			grid.ghostGreedySearch();
			grid.resetSearch();
			grid.ghostDepthFirstSearch();

			

			for (int i = 0; i < 3; i++)
			{
				GridElement* currentGhostLocation = grid.getGhostLocation(i);
				GridElement* currentPacLocation = grid.getPacLocation();
				if (currentGhostLocation->getX() == currentPacLocation->getX() &&
					currentGhostLocation->getY() == currentPacLocation->getY())
					grid.setGameState("ended");
					
			}

			
			
		}
		
	}
	else if (grid.getGameState() == "ended")
	{
		if (!grid.gameSoundisPlaying())
		{
			grid.gameSoundLoad("lol-youdied.mp3");
			grid.gameSoundPlay();
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	grid.draw();
	if (grid.getGameState() == "at_splash")
	{
		ofBackground(0);
		grid.displayGameSplashScreen();
	}

	else if (grid.getGameState() == "ended") //game has ended
	{

		grid.displayGameOverScreen();

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	
	case ' ':
		grid.setGameState("not_started");
		break;
	
	case 'q':
		ofExit();
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
