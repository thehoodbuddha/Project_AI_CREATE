#pragma once 
#include "visual.h" 
Visual::Visual() {


};

void Visual::direction_visuals(int state, int frame_x, int frame_y, int size) {


	//ofDrawTriangle(180, 180, 220, 180,  200, 150 );

	switch (state) {
	case 0 :{
			ofDrawTriangle(frame_x/2 - size, frame_y/2 - size , frame_x /2 + size, frame_y /2 - size, frame_x/2, frame_y/2- 2*size);
			break;
	};
	case 1:ofDrawTriangle(300, 180, 200, 220, 330,200);

	case 2:;
	case 3:;

	};
}
