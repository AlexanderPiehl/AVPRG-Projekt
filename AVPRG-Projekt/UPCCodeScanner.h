#ifndef UPCCODESCANNER_H_
#define UPCCODESCANNER_H_
#include "CodeScanner.h"

class UPCCodeScanner : public CodeScanner
{
private:
	int getBitWidthAndSkipGuard(cv::Mat image, int& start, int y);
	bool readCode(cv::Mat image, int& start, int y, int barWidth, bool isLeft);
	void ignoreBadPixel(cv::Mat image, bool blackBar, int& start, int y);
	bool skipMGuard(cv::Mat image, int& start, int y);
	void checkNextPixel(cv::Mat image, int& start, int y);
	void checkBitWidth(cv::Mat image, int&start, int y, int bitWidth);
	int skipTooThickBars(cv::Mat image, int barThickness);
	bool convertBinToInt(int binaryCode[],bool isLeft);
	bool calcCheckDigit();

	std::map<int,int> binToIntMap;
	int barCodeValue [12];
public:
	UPCCodeScanner();
	~UPCCodeScanner();
	virtual int decodingBarcode(cv::Mat image, int& start, int end, int y);
	
};
#endif
