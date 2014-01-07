#include "UPCCodeScanner.h"
using namespace std;
using namespace cv;

string UPCCodeScanner::decodingBarcode(Mat image, int& start, int end, int y)
{
	int bit_width = getBitWidthAndSkipLGuard(image, start, y);
	readLeftCode(image, start, y, bit_width);
	skipMGuard(image, start, y);
	cout << "Bit Weite: " << bit_width << " ; X: " << start <<endl;
	return "";
}

int UPCCodeScanner::getBitWidthAndSkipLGuard(cv::Mat image, int& start, int y)
{
	int lGuard [3] = {BAR,SPACE,BAR};
	int widthBarFirst = 0;
	int widthSpace = 0;
	int widthBarLast = 0;
	int pixel = image.at<uchar>(y,start);
	cout << "Test wo x gerade ist: " << start << endl;
	for(int i = 0; i < 3; i++)
	{
		while(lGuard[i] == pixel)
		{
			start++;
			pixel = image.at<uchar>(y,start);

			if(0 == i)
				widthBarFirst++;
			else if(1 == i)
				widthSpace++;
			else if(2 == i)
				widthBarLast++;
		}
	}
	cout << "Test wo x gerade ist: " << start << endl;
	//Kontrolle ob die Weiten gleich sind
	if(widthBarFirst == widthBarLast && widthBarFirst == widthSpace)
		return widthBarFirst;
	else
	{
		//Fehlermeldung
		return 0;
	}
}


void UPCCodeScanner::readLeftCode(cv::Mat image, int& start, int y, int barWidth)
{
	bool blackBar = false;
	// Speicher für die einzelnen 7 Bits
	int binaryCode [6] = {0,0,0,0,0,0};
	int pixel;
	// die variable setzt die Bits von der 7. bis 1. Stelle
	int bitCounter;
	for (int i = 0; i < 6;i++)
	{
		// if (2 < i) start-=1;
		bitCounter = 1000000;
		for (int l = 0; l < 7;l++)
		{
			pixel = image.at<uchar>(y,start);
			if (BAR == pixel && !blackBar || SPACE == pixel && blackBar)
			{
				ignoreBadPixel(image, blackBar, start, y);
			}

			if (BAR == pixel)
			{			
				blackBar = true;
				binaryCode[i]+= bitCounter;
			}
			else 
			{
				
				blackBar = false;
			}
			cout << "Strich " << i+1 << " : " << binaryCode[i] << " Position X: " << start << endl;
			start+= barWidth;
			bitCounter = bitCounter / 10;
		}
	}
}

// Dies sollte ausgleichen, wenn mal ein Pixel fehlt oder zu viel ist.
void UPCCodeScanner::ignoreBadPixel(cv::Mat image, bool blackBar, int& start, int y)
{
	int pixel;
	bool done = false;
	if(!blackBar)
	{
		pixel = image.at<uchar>(y,start-1);
		if (0 == pixel)
		{
			start-=1;
			done = true;
		}
	}
	if(!blackBar && !done)
	{
		pixel = image.at<uchar>(y,start+1);
		if (255 == pixel)
		{
			start+=1;
		}
	}
	if(blackBar)
	{
		pixel = image.at<uchar>(y,start-1);
		if (255 == pixel)
			start-=1;
	}
}

void UPCCodeScanner::skipMGuard(cv::Mat image, int& start, int y)
{
	int mGuard[5] = {SPACE,BAR,SPACE,BAR,SPACE};
	int pixel = image.at<uchar>(y,start);
	cout << "Test wo x gerade ist: " << start << endl;
	for(int i = 0; i < 5; i++)
	{
		while(mGuard[i] == pixel)
		{
			start++;
			pixel = image.at<uchar>(y,start);
		}
	}
}
