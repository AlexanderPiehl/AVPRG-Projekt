#ifndef UPCCODESCANNER_H_
#define UPCCODESCANNER_H_
#include "CodeScanner.h"

class UPCCodeScanner : CodeScanner
{
private:

public:
	virtual std::string readBarcode();
	virtual std::string decodingBarcode(cv::Mat image, int& start, int end, int y);
	int getBitWidthAndSkipLGuard(cv::Mat image, int& start, int y);
};
#endif
