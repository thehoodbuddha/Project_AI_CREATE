#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
	ofSetupOpenGL(WINDOW_WIDTH, WINDOW_HEIGHT + INFOBAR_SIZE, OF_WINDOW);			// <-------- setup the GL context
	std::cout << "SearchStrategies v" << APP_VERSION_MAJOR << '.'
		<< APP_VERSION_MINOR << '\n';
	
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
}
