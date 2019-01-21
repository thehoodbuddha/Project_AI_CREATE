/*

*/

#include "ofApp.h"
#include <thread>
//--------------------------------------------------------------
GridElement* pacStartLocation;

void ofApp::setup(){
	std::thread t(&EyeTracking::Eyetrack_Main, &track);
	t.detach();
	ofBackground(255, 255, 255);

	// init random generator
	std::srand((unsigned int)std::time(0));

	grid.generateMaze();
	grid.setPointsystem();

	pacStartLocation = grid.getPacLocation();

}

//--------------------------------------------------------------
void ofApp::update(){
	//auto threadfunction = track.Eyetrack_Main;

	//threadfunction();
	//track * taskPtr= new EyeTracking();
	//EyeTracking x; 
	if (grid.getGameState() == "not_started")
	{
		GridElement* currentPacLocation = grid.getPacLocation();
		//check if pacman started to move
		if (currentPacLocation->getX() != pacStartLocation->getX() ||
			currentPacLocation->getY() != pacStartLocation->getY())
			grid.setGameState("started");
	}

	else if (grid.getGameState() == "started")
	{
		grid.resetSearch();
		grid.ghostAStarSearch();
		grid.resetSearch();
		grid.ghostGreedySearch();
		grid.resetSearch();
		grid.ghostDepthFirstSearch();
		//check if the game has ended
		//TODO this can be done better
		//this whole procedure can be just a collision check function

		for (int i = 0; i < 3; i++)
		{
			GridElement* currentGhostLocation = grid.getGhostLocation(i);
			GridElement* currentPacLocation = grid.getPacLocation();
			if (currentGhostLocation->getX() == currentPacLocation->getX() &&
				currentGhostLocation->getY() == currentPacLocation->getY())
				grid.setGameState("ended");
		}

	}
	else if (grid.getGameState() == "ended")
	{
		if (!grid.gameSoundisPlaying())
		{
			grid.gameSoundLoad("lol-youdied.mp3");
			grid.gameSoundPlay();
		}
		ofBackground(255);

	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(0);  // Clear the screen with a black color
	//ofSetColor(255);  // Set the drawing color to white
	//std::cout << "faka" << std::endl;
	if (grid.getGameState() != "ended")
	{
		grid.draw();
		switch (track.direction(track.locationPoint.x, track.locationPoint.y, WEBCAM_WIDTH, WEBCAM_HEIGHT)) {
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

	else //game has ended
	{

		grid.displayGameOverScreen();

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'm':
		grid.reset();
		grid.generateMaze();
		break;

	case 'r':
		grid.reset();
		grid.generateRooms();
		break;

	case 'o':
		grid.reset();
		grid.generateObstacles();
		break;

	case 'j':
		grid.reset();
		grid.generateJail();
		break;

	case 'd':
		grid.resetSearch();
		grid.depthFirstSearch();
		break;

	case 'b':
		grid.resetSearch();
		grid.breadthFirstSearch();
		break;

	case 'g':
		grid.resetSearch();
		grid.greedySearch();
		break;

	case 'a':
		grid.resetSearch();
		grid.aStarSearch();
		break;

	case 's':
		grid.resetSearch();
		grid.aStarSearchRT();
		break;

	case 'p':
		grid.resetSearch();
		grid.aStarSearchRT();

	

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
