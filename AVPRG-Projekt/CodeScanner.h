#ifndef CODESCANNER_H_
#define CODESCANNER_H_
#include <opencv2\opencv.hpp>
#include "OpenCV_Tools.h"

#define BAR     0
#define SPACE 255

class CodeScanner
{	
private:
	
protected:


public:
	CodeScanner();
	virtual~CodeScanner(void);
	virtual std::string readBarcode();
	virtual int decodingBarcode(cv::Mat image, int& start, int end, int y) = 0;
	OpenCV_Tools cvTools;

	std::string path;

};
#endif