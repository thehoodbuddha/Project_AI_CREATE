#pragma once 
#include "visual.h" 
Visual::Visual() {


};

void Visual::direction_visuals(int state, int frame_x, int frame_y, int size) {


	//ofDrawTriangle(180, 180, 220, 180,  200, 150 );

	switch (state) {
	case 0 :{
			ofSetColor(0,255,0);  // Set the drawing color to white
			ofDrawTriangle(frame_x/2 - size, frame_y/2 + size , frame_x /2 + size, frame_y /2 + size, frame_x/2, frame_y/2- size);
			break;
	};
	case 1: {
			ofSetColor(255,0,0);  // Set the drawing color to white
			ofPushMatrix();
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofTranslate(frame_x, 0, 0);
			ofRotate(90);
			ofDrawTriangle(frame_x / 2 - size, frame_y / 2 + size, frame_x / 2 + size, frame_y / 2 + size, frame_x / 2, frame_y / 2 - size);
			ofPopMatrix();
			break;
	};
	case 2: {
		ofSetColor(255, 0, 255);  // Set the drawing color to white
		ofDrawTriangle(frame_x / 2 - size, frame_y / 2 - size, frame_x / 2 + size, frame_y / 2 - size, frame_x / 2, frame_y / 2 + size);
		break;


	};
	case 3: {
		ofSetColor(0, 0, 255);  // Set the drawing color to white
		ofPushMatrix();
		ofSetRectMode(OF_RECTMODE_CENTER);
		ofTranslate(0, frame_y, 0);
		ofRotate(270);
		ofDrawTriangle(frame_x / 2 - size, frame_y / 2 + size, frame_x / 2 + size, frame_y / 2 + size, frame_x / 2, frame_y / 2 - size);
		ofPopMatrix();
		break;
	};

	};
}
