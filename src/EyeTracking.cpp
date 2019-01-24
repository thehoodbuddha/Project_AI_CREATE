#include "EyeTracking.h"

#include <iostream>


#define  CV_HAAR_SCALE_IMAGE   2
using namespace cv;



EyeTracking::EyeTracking() {
	Load_Data();
	cv::CascadeClassifier faceCascade;
	cv::CascadeClassifier eyeCascade;
	std::vector<cv::Point> centers;
	cv::Point lastPoint;
	cv::Point locationPoint;
};



int EyeTracking::Load_Data() {
	if (!faceCascade.load("..\\src\\haarcascade_frontalface_default.xml"))
	{
		std::cerr << "Could not load face detector." << std::endl;
		return -1;
	}
	if (!eyeCascade.load("..\\src\\haarcascade_eye.xml"))
	{
		std::cerr << "Could not load eye detector." << std::endl;
		return -1;
	}
};


int EyeTracking::Eyetrack_Main() {
	cv::VideoCapture cap(0);
	cv::Mat frame;

	while (1)
	{
		cap >> frame; // outputs the webcam image to a Mat
		if (!frame.data) break;
		faceDetect(frame, faceCascade, eyeCascade);
		cv::imshow("Webcam", frame); // displays the Mat
	//	std::cout << direction(locationPoint.x, locationPoint.y, frame) << std::endl;
		//std::cout<< frame.rows << std::endl;
		if (cv::waitKey(5) >= 0) break;  // takes 30 frames per second. if the user presses any button, it stops from showing the webcam
		//break;
	}
	return 0;
};


int EyeTracking::cam_Check() {
	cv::VideoCapture cap(0); // the fist webcam connected to your PC
	if (!cap.isOpened())
	{
		std::cerr << "Webcam not detected." << std::endl;
		return -1;
	}
	cv::Mat frame;
	while (1)
	{
		cap >> frame; // outputs the webcam image to a Mat
		//cv::imshow("Webcam", frame); // displays the Mat
		if (cv::waitKey(30) >= 0) break; // takes 30 frames per second. if the user presses any button, it stops from showing the webcam
	}
	return 0;
};


void EyeTracking::faceDetect(cv::Mat &frame, cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade)
{
	
	cv::Mat grayscale;
	cv::Mat frame_mirrored = frame;
	cv::flip(frame_mirrored,frame_mirrored,1);
	cv::cvtColor(frame_mirrored, grayscale, cv::COLOR_RGB2GRAY); // convert image to grayscale
	//cv::equalizeHist(grayscale, grayscale); // enhance image contrast 
	std::vector<cv::Rect> faces;
	std::vector<cv::Rect> eyes;
	faceCascade.detectMultiScale(grayscale, faces, 1.5, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(100, 100));
	if (faces.size() == 0) return; // none face was detected
	//if (faces.size() == 1) std::cout << "facedetected" << std::endl;

	cv::Mat face = frame(faces[0]); // crop the face
	eyeCascade.detectMultiScale(face, eyes, 1.1, 4, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30)); // same thing as above  


	rectangle(frame, faces[0].tl(), faces[0].br(), cv::Scalar(255, 0, 0),2);

	//std::cout << "X :" << (face.cols + faces[0].x)/2 <<  "Y :" << (face.rows + faces[0].y)/2 << std::endl;

	if (eyes.size() != 2) return; // both eyes were not detected
	for (cv::Rect &eye : eyes)
	{
		rectangle(frame_mirrored, faces[0].tl() + eye.tl(), faces[0].tl() + eye.br(), cv::Scalar(0, 255, 0), 3);
	}

	locationPoint.x = faces[0].x+( faces[0].br().x - faces[0].x )/2;
	locationPoint.y = faces[0].y + (faces[0].br().y - faces[0].y) / 2;

}	

 int EyeTracking::direction(float x, float y, int frame_x, int frame_y)
{

	if ((y < frame_y / 2) && (x > frame_x / 3) && (x < frame_x*2/3)){
	return 0;
	}
	else if( (y>frame_y/2) && (x>frame_x/3) && (x<frame_x*2/3)){
		return 2;
	}
	else if ((x> frame_x*2/3))  {
		return 1;
	}
	else if ((x < (frame_x / 3))) {
		return 3; 
	}
	else
		return -1;

	}
	
