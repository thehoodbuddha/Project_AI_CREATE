#include "EyeTracking.h"

#include <iostream>


#define  CV_HAAR_SCALE_IMAGE   2
using namespace cv;

EyeTracking::EyeTracking() {
	Load_Data();
	cv::CascadeClassifier faceCascade;
	cv::CascadeClassifier eyeCascade;
};

int EyeTracking::Load_Data() {
	if (!faceCascade.load("C:\\Users\\JP\\Documents\\of_v0.10.0_vs2017_release\\apps\\myApps\\newProject\\src\\haarcascade_frontalface_default.xml"))
	{
		std::cerr << "Could not load face detector." << std::endl;
		return -1;
	}
	if (!eyeCascade.load("C:\\Users\\JP\\Documents\\of_v0.10.0_vs2017_release\\apps\\myApps\\newProject\\src\\haarcascade_eye.xml"))
	{
		std::cerr << "Could not load eye detector." << std::endl;
		return -1;
	}
};


int EyeTracking::Eyetrack_Main(){
	cv::VideoCapture cap(0);
	cv::Mat frame;
	while (1)
	{
		cap >> frame; // outputs the webcam image to a Mat
		if (!frame.data) break;
		detectEyes(frame, faceCascade, eyeCascade);
		cv::imshow("Webcam", frame); // displays the Mat
		if (cv::waitKey(30) >= 0) break;  // takes 30 frames per second. if the user presses any button, it stops from showing the webcam
	}
	return 0;
};


int EyeTracking::cam_Check(){
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
		cv::imshow("Webcam", frame); // displays the Mat
		if (cv::waitKey(30) >= 0) break; // takes 30 frames per second. if the user presses any button, it stops from showing the webcam
	}
	return 0;	
};

void EyeTracking::detectEyes(cv::Mat &frame, cv::CascadeClassifier &faceCascade, cv::CascadeClassifier &eyeCascade)
{
	cv::Mat grayscale;
	cv::cvtColor(frame, grayscale, cv::COLOR_RGB2GRAY); // convert image to grayscale
	//cv::equalizeHist(grayscale, grayscale); // enhance image contrast 
	std::vector<cv::Rect> faces;
	std::vector<cv::Rect> eyes;

	faceCascade.detectMultiScale(grayscale, faces, 1.1, 5, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(150, 150));

	if (faces.size() == 0) return; // none face was detected
	if (faces.size() == 1) std::cout << "facedetected" << std::endl;

	cv::Mat face = frame(faces[0]); // crop the face
	eyeCascade.detectMultiScale(face, eyes, 1.1, 5, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30)); // same thing as above  
	rectangle(frame, faces[0].tl(), faces[0].br(), cv::Scalar(255, 0, 0), 2);

	if (eyes.size() != 2) return; // both eyes were not detected
	if (eyes.size() == 2) std::cout << "eyes" << std::endl;
	for (cv::Rect &eye : eyes)
	{
		rectangle(frame, faces[0].tl() + eye.tl(), faces[0].tl() + eye.br(), cv::Scalar(0, 255, 0), 2);
	}
	cv::Rect eyeRect = getLeftmostEye(eyes);
	cv::Mat eye = face(eyeRect); // crop the leftmost eye
	//cv::equalizeHist(eye, eye);
	std::vector<cv::Vec3f> circles;

	//cv::HoughCircles(eye, circles, cv::HOUGH_GRADIENT, 1, eye.cols / 8, 250, 15, eye.rows / 8, eye.rows / 3);

};



	

cv::Vec3f getEyeball(cv::Mat &eye, std::vector<cv::Vec3f> &circles)
{
	std::vector<int> sums(circles.size(), 0);
	for (int y = 0; y < eye.rows; y++)
	{
		uchar *ptr = eye.ptr<uchar>(y);
		for (int x = 0; x < eye.cols; x++)
		{
			int value = static_cast<int>(*ptr);
			for (int i = 0; i < circles.size(); i++)
			{
				cv::Point center((int)std::round(circles[i][0]), (int)std::round(circles[i][1]));
				int radius = (int)std::round(circles[i][2]);
				if (std::pow(x - center.x, 2) + std::pow(y - center.y, 2) < std::pow(radius, 2))
				{
					sums[i] += value;
				}
			}
			++ptr;
		}
	}
	int smallestSum = 9999999;
	int smallestSumIndex = -1;
	for (int i = 0; i < circles.size(); i++)
	{
		if (sums[i] < smallestSum)
		{
			smallestSum = sums[i];
			smallestSumIndex = i;
		}
	}
	return circles[smallestSumIndex];
}


	cv::Rect EyeTracking::getLeftmostEye(std::vector<cv::Rect> &eyes)
	{
		int leftmost = 99999999;
		int leftmostIndex = -1;
		for (int i = 0; i < eyes.size(); i++)
		{
			if (eyes[i].tl().x < leftmost)
			{
				leftmost = eyes[i].tl().x;
				leftmostIndex = i;
			}
		}
		return eyes[leftmostIndex];
	};