#include "OpenCV_Tools.h"
using namespace cv;
using namespace std;

OpenCV_Tools::OpenCV_Tools(void)
{
}


OpenCV_Tools::~OpenCV_Tools(void)
{
}

Mat OpenCV_Tools::loadImage(string path)
{
	Mat image = imread(path);
	return image;
}

VideoCapture OpenCV_Tools::loadVideo(string path)
{
	VideoCapture video;
	video.open(path);
	return video;
}

VideoCapture OpenCV_Tools::loadVideoByWebcam()
{
	VideoCapture video;
	video.open(0);
	return video;
}

int OpenCV_Tools::getVideoHeight(VideoCapture video)
{
	int height = video.get(CV_CAP_PROP_FRAME_HEIGHT);
	return height;
}

int OpenCV_Tools::getVideoWidth(VideoCapture video)
{
	int width = video.get(CV_CAP_PROP_FRAME_WIDTH);
	return width;
}
