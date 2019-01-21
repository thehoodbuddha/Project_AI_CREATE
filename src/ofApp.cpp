/*

*/

#include "ofApp.h"
#include <thread>
//--------------------------------------------------------------
void ofApp::setup(){
	std::thread t(&EyeTracking::Eyetrack_Main, &track);
	t.detach();
	ofBackground(255, 255, 255);

	// init random generator
	std::srand((unsigned int)std::time(0));

	grid.generateMaze();
	grid.setPointsystem();
}

//--------------------------------------------------------------
void ofApp::update(){
	//auto threadfunction = track.Eyetrack_Main;

	//threadfunction();
	//track * taskPtr= new EyeTracking();
	//EyeTracking x; 
	
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(0);  // Clear the screen with a black color
	//ofSetColor(255);  // Set the drawing color to white
	//std::cout << "faka" << std::endl;
	grid.draw();
	
	//std:thread t1(&track:Eyetracking_Main,this, "new");
	
	//if (location.y > frame.rows) location.y = frame.rows;
	//if (location.y < 0) location.y = 0;
	// ofDrawEllipse(track.locationPoint.x, track.locationPoint.y, 80, 80);
	//visual.direction_visuals(track.direction(track.locationPoint.x, track.locationPoint.y,640, 480),400,400,80);
	//std::cout << track.direction(track.locationPoint.x, track.locationPoint.y,WEBCAM_WIDTH,WEBCAM_HEIGHT) << std::endl;

	switch(track.direction(track.locationPoint.x, track.locationPoint.y,WEBCAM_WIDTH, WEBCAM_HEIGHT)) {
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
