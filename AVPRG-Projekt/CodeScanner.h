#ifndef CODESCANNER_H_
#define CODESCANNER_H_
#include <opencv2\opencv.hpp>
#include "OpenCV_Tools.h"



class CodeScanner
{	
private:
	
protected:


public:
	CodeScanner(void);
	~CodeScanner(void);
	virtual std::string readBarcode();
	virtual std::string decodingBarcode(cv::Mat image, int& start, int end, int y);
	OpenCV_Tools cvTools;

};
#endif