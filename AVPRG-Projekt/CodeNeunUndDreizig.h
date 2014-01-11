#ifndef CODENEUNUNDDREIZIG_H_
#define CODENEUNUNDDREIZIG_H_
#include "CodeScanner.h"
#include <vector> 

class CodeNeunUndDreizig : public CodeScanner
{
private:
	int averageNumber(int* elementWidth);
	int binaryNumber(int* elementWidth, int average);
	bool readNineElements(cv::Mat image, int& start, int y, bool foundCode);
	bool convert(int binaryNumber);

	std::vector<int> binaryNumbers;
	int binaryNumbersSize;
public:
	CodeNeunUndDreizig();
	~CodeNeunUndDreizig();
	virtual int decodingBarcode(cv::Mat image, int& start, int end, int y);	
};
#endif
