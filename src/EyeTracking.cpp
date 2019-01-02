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
	//	cv::imshow("Webcam", frame); // displays the Mat
		if (cv::waitKey(5) >= 0) break;  // takes 30 frames per second. if the user presses any button, it stops from showing the webcam
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
		//cv::imshow("Webcam", frame); // displays the Mat
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

	faceCascade.detectMultiScale(grayscale, faces, 1.5, 3, 0| CV_HAAR_SCALE_IMAGE, cv::Size(170, 170));

	if (faces.size() == 0) return; // none face was detected
	//if (faces.size() == 1) std::cout << "facedetected" << std::endl;

	cv::Mat face = frame(faces[0]); // crop the face
	eyeCascade.detectMultiScale(face, eyes, 1.1, 4, 0| CV_HAAR_SCALE_IMAGE, cv::Size(30,30)); // same thing as above  
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
//	cv::cvtColor(eye, grayscale, cv::COLOR_RGB2GRAY); // convert image to grayscale
	cv::Mat eyeGrayScale;	
	cv::cvtColor(eye, eyeGrayScale,cv::COLOR_RGB2GRAY);

	cv::HoughCircles(eyeGrayScale, circles, cv::HOUGH_GRADIENT, 1, eyeGrayScale.cols / 8, 250, 15, eyeGrayScale.rows / 8, eyeGrayScale.rows / 3);

	if (circles.size() > 0)
	{
		cv::Vec3f eyeball = getEyeball(eye, circles);
		cv::Point center(eyeball[0], eyeball[1]);
		centers.push_back(center);
		center = stabilize(centers, 400);
		
		if (centers.size() > 1)
		{
			//std::cout << "detected" << std::endl; 
			cv::Point diff;
			diff.x = (center.x - lastPoint.x) * 20;
			diff.y = (center.y - lastPoint.y) * -30;
			std::cout << diff << std::endl;

			locationPoint += diff;
			std::cout << diff << std::endl;
			if (locationPoint.x > 400) locationPoint.x = 400;
			if (locationPoint.x < 0) locationPoint.x = 0;
		}
		lastPoint = center;
		int radius = (int)eyeball[2];
		cv::circle(frame, faces[0].tl() + eyeRect.tl() + center, radius, cv::Scalar(0, 0, 255), 2);
		cv::circle(eye, center, radius, cv::Scalar(255, 255, 255), 2);
	}

	//cv::Mat outImg;
	//cv::resize(eyeGrayScale, outImg, cv::Size(eyeGrayScale.cols * 5, eyeGrayScale.rows * 5), 0, 0, cv::INTER_LINEAR);
	//cv::imshow("Eye",outImg);

};
	


cv::Vec3f EyeTracking::getEyeball(cv::Mat &eye, std::vector<cv::Vec3f> &circles)
{
	std::vector<int> sums(circles.size(), 0);
	for (int y = 0; y < eye.cols; y++)
	{
		uchar *ptr = eye.ptr<uchar>(y);
		for (int x = 0; x < eye.cols; x++)
		{
			int value = int(*ptr);
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



	cv::Point EyeTracking::stabilize(std::vector<cv::Point> &points, int windowSize)
	{
		float sumX = 0;
		float sumY = 0;
		int count = 0;
		for (int i = std::max(0, (int)(points.size() - windowSize)); i < points.size(); i++)
		{
			sumX += points[i].x;
			sumY += points[i].y;
			++count;
		}
		if (count > 0)
		{
			sumX /= count;
			sumY /= count;
		}
		return cv::Point(sumX, sumY);
	}
