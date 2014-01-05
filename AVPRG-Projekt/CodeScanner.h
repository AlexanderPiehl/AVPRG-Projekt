#ifndef CODESCANNER_H_
#define CODESCANNER_H_
#include <opencv2\opencv.hpp>
#include "OpenCV_Tools.h"

class CodeScanner
{
private:
	OpenCV_Tools cvTools;
protected:

public:
	CodeScanner(void);
	~CodeScanner(void);
	std::string readBarcode();
};
#endif