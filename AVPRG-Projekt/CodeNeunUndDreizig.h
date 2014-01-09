#ifndef CODENEUNUNDDREIZIG_H_
#define CODENEUNUNDDREIZIG_H__H_
#include "CodeScanner.h"

class CodeNeunUndDreizig : public CodeScanner
{
private:
	int averageNumber(int* elementWidth);
	int binaryNumber(int* elementWidth, int average);
	bool readNineElements(cv::Mat image, int& start, int y, bool foundCode);

public:
	CodeNeunUndDreizig();
	~CodeNeunUndDreizig();
	virtual int decodingBarcode(cv::Mat image, int& start, int end, int y);
	
};
#endif
