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

//	boost::asio::io_service io;

//	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(2));
	
	//timer.async_wait(boost::bind(&Grid::ghostAStarSearch, &grid));
//	grid.timerTest();
//	timer.async_wait(boost::bind(&Grid::timerTest, this));
	//&CFoo::bar, &foo
	//&bar::foo, bar()
	


	


}

//--------------------------------------------------------------
void ofApp::update(){
	
	namespace sc = std::chrono;

	auto time = sc::system_clock::now(); // get the current time

	auto since_epoch = time.time_since_epoch(); // get the duration since epoch

	auto millis = sc::duration_cast<sc::milliseconds>(since_epoch);
	//std::cout << millis.count() << std::endl;
	//unsigned long int  test = millis.count(); 
	//std::cout << test << std::endl;

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
		

	/*
	if (grid.getGameState() == "not_started")
	{
		GridElement* currentPacLocation = grid.getPacLocation();
		//check if pacman started to move
		if (currentPacLocation->getX() != pacStartLocation->getX() ||
			currentPacLocation->getY() != pacStartLocation->getY())
			grid.setGameState("started");
	}
	*/
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
			//grid.gameSoundLoad("lol-youdied.mp3");
			//grid.gameSoundPlay();
		}
	}

	/*
	
	
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
	*/
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofBackground(0);  // Clear the screen with a black color
	//ofSetColor(255);  // Set the drawing color to white
	//std::cout << "faka" << std::endl;
	grid.draw();
	/*
	if (grid.getGameState() != "ended")
	{
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
	*/
	if (grid.getGameState() == "not_started")
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
