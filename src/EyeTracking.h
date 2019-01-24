#pragma once
#ifndef EyeTracking_h
#define EyeTracking_h
#include "constants.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp> 
#include <opencv2/opencv.hpp>

class EyeTracking {

public:
	
	EyeTracking();
	int cam_Check();
	int Eyetrack_Main();
	int direction(float x, float y, int frame_x, int frame_y);
	
	cv::Point locationPoint;
private:
	
	cv::Point lastPoint;
	cv::CascadeClassifier faceCascade;
	cv::CascadeClassifier eyeCascade;
	int Load_Data();
	void faceDetect(cv::Mat &frame, cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade);

};



#endif // !"EyeTracking.h"
