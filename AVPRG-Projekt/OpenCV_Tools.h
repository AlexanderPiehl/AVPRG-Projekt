#pragma once
#include "opencv2\opencv.hpp"
class OpenCV_Tools
{
public:
	OpenCV_Tools(void);
	~OpenCV_Tools(void);
	//Lädt ein Image
	cv::Mat loadImage(std::string path);
	//Lädt ein Video, VideoCapture Objekt muss vorhanden sein
	cv::VideoCapture loadVideo(std::string path);
	//Greift auf die Webcam zu; VideoCapture muss vorhanden sein
	cv::VideoCapture loadVideoByWebcam();

	int getVideoHeight(cv::VideoCapture video);
	int getVideoWidth(cv::VideoCapture video);

};

