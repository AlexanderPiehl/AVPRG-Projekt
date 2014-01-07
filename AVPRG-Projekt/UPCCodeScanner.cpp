#include "UPCCodeScanner.h"
using namespace std;
using namespace cv;

string UPCCodeScanner::decodingBarcode(Mat image, int& start, int end, int y)
{
	int bit_width = getBitWidthAndSkipGuard(image, start, y);
	if(0 < bit_width)
	{
		readCode(image, start, y, bit_width, true);
		skipMGuard(image, start, y);
		readCode(image, start, y, bit_width, false);
		cout << "Bit Weite: " << bit_width << " ; X: " << start <<endl;
		return "";
	}
	else
	{
		return "";
	}
	
}

int UPCCodeScanner::getBitWidthAndSkipGuard(Mat image, int& start, int y)
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
	//Kontrolle ob 2 Weiten gleich sind, wenn nicht -1 als Fehler
	if(widthBarFirst == widthBarLast)
		return widthBarFirst;
	else if(widthBarFirst == widthSpace)
		return widthBarFirst;
	else if(widthSpace == widthBarLast)
		return widthSpace;
	else
		return -1;
}


void UPCCodeScanner::readCode(Mat image, int& start, int y, int barWidth, bool isLeft)
{
	bool blackBar = false;
	// Speicher f�r die einzelnen 7 Bits
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
			checkNextPixel(image, start,y);
			pixel = image.at<uchar>(y,start);
			if (BAR == pixel && !blackBar || SPACE == pixel && blackBar)
			{
				ignoreBadPixel(image, blackBar, start, y);
			}

			if(isLeft)
			{
				if (BAR == pixel)
				{			
					blackBar = true;
					binaryCode[i]+= bitCounter;
				}
				else 
				{
					blackBar = false;
				}
			}
			else
			{
				if (BAR == pixel)
				{			
					blackBar = true;
				}
				else 
				{
					blackBar = false;
					binaryCode[i]+= bitCounter;		
				}
			}
			
			cout << "Strich " << i+1 << " : " << binaryCode[i] << " Position X: " << start << endl;
			start+= barWidth;
			bitCounter = bitCounter / 10;
		}
	}
}

void UPCCodeScanner::checkNextPixel(Mat image, int& start, int y)
{
	int pixel = image.at<uchar>(y,start);
	int rightPixel = image.at<uchar>(y,start+1);

	if (pixel != rightPixel)
		start+=1;
}

// Dies sollte ausgleichen, wenn mal ein Pixel fehlt oder zu viel ist.
void UPCCodeScanner::ignoreBadPixel(Mat image, bool blackBar, int& start, int y)
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

void UPCCodeScanner::skipMGuard(Mat image, int& start, int y)
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

void UPCCodeScanner::checkBitWidth(Mat image, int& start, int y, int bitWidth)
{


}