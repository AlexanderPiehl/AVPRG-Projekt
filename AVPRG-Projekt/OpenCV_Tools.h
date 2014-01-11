#ifndef OPENCVTOOLS_H_
#define OPENCVTOOLS_H_
#include "opencv2\opencv.hpp"

class OpenCV_Tools
{
public:
	OpenCV_Tools(void);
	~OpenCV_Tools(void);
	//L‰dt ein Image
	cv::Mat loadImage(std::string path);
	//L‰dt ein Image als Bin‰rbild(Schwarz/Weiﬂ)
	cv::Mat loadImageAsBW(std::string path);
	//L‰dt ein Video, VideoCapture Objekt muss vorhanden sein
	cv::VideoCapture loadVideo(std::string path);
	//Greift auf die Webcam zu; VideoCapture muss vorhanden sein
	cv::VideoCapture loadVideoByWebcam();

	int getVideoHeight(cv::VideoCapture video);
	int getVideoWidth(cv::VideoCapture video);
};
#endif