#ifndef CODESCANNER_H_
#define CODESCANNER_H_
#include <opencv2\opencv.hpp>
#include "OpenCV_Tools.h"
#include "BitToStringMap.h"

#define BAR     0
#define SPACE 255

class CodeScanner
{	
private:
	
protected:


public:
	CodeScanner();
	virtual~CodeScanner(void);
	virtual int readBarcode();
	virtual int decodingBarcode(cv::Mat image, int& start, int end, int y) = 0;
	OpenCV_Tools cvTools;
	BitToStringMap bitToStringMap;

	std::map<int,int> binToIntMap;
	std::string path;
	std::string result;

};
#endif