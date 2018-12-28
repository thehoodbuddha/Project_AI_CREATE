#pragma once
#ifndef EyeTracking_h
#define EyeTracking_h

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

private:
	std::vector<cv::Point> centers;
	cv::Point lastPoint;

	cv::CascadeClassifier faceCascade;
	cv::CascadeClassifier eyeCascade;
	void detectEyes(cv::Mat &frame, cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade);
	int Load_Data();
	cv::Rect getLeftmostEye(std::vector<cv::Rect> &eyes);
	cv::Vec3f getEyeball(cv::Mat &eye, std::vector<cv::Vec3f> &circles);
	cv::Point stabilize(std::vector<cv::Point> &points, int windowSize);
};



#endif // !"EyeTracking.h"
