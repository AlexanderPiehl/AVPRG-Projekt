#ifndef UPCCODESCANNER_H_
#define UPCCODESCANNER_H_
#include "CodeScanner.h"

class UPCCodeScanner : public CodeScanner
{
private:

public:
	virtual std::string decodingBarcode(cv::Mat image, int& start, int end, int y);
	int getBitWidthAndSkipLGuard(cv::Mat image, int& start, int y);
	void readCode(cv::Mat image, int& start, int y, int barWidth, bool isLeft);
	void ignoreBadPixel(cv::Mat image, bool blackBar, int& start, int y);
	void skipMGuard(cv::Mat image, int& start, int y);
	void checkNextPixel(cv::Mat image, int& start, int y);
};
#endif
