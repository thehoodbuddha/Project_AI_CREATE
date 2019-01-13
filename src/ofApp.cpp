#include "ofApp.h"
#include <thread>
//--------------------------------------------------------------
void ofApp::setup(){
	std::thread t(&EyeTracking::Eyetrack_Main, &track);
	t.detach();
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
	ofBackground(0);  // Clear the screen with a black color
	ofSetColor(255);  // Set the drawing color to white
	//std::cout << "faka" << std::endl;
	
	
	//std:thread t1(&track:Eyetracking_Main,this, "new");
	
	//if (location.y > frame.rows) location.y = frame.rows;
	//if (location.y < 0) location.y = 0;
	// ofDrawEllipse(track.locationPoint.x, track.locationPoint.y, 80, 80);
	visual.direction_visuals(track.direction(track.locationPoint.x, track.locationPoint.y,640, 480),640,480,80);
	std::cout << track.direction(track.locationPoint.x, track.locationPoint.y,640,480) << std::endl;

	}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
