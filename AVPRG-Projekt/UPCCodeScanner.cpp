#include "UPCCodeScanner.h"
using namespace std;
using namespace cv;

string UPCCodeScanner::decodingBarcode(Mat image, int& start, int end, int y)
{
	int bit_width = getBitWidthAndSkipLGuard(image, start, y);
	readLeftCode(image, start, y, bit_width);
	cout << "Bit Weite: " << bit_width << " ; X: " << start <<endl;
	return "";
}

int UPCCodeScanner::getBitWidthAndSkipLGuard(cv::Mat image, int& start, int y)
{
	int lGuard [3] = {0,255,0};
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
	int binaryCode [6] = {0,0,0,0,0,0};
	int pixel;
	int bitCounter;
	for (int i = 0; i < 6;i++)
	{
		// if (0 < i) start-=1;
		bitCounter = 1000000;
		for (int l = 0; l < 7;l++)
		{
			pixel = image.at<uchar>(y,start);
			if (0 == pixel)
				binaryCode[i]+= bitCounter;
			else
				binaryCode[i]+= 0;
			cout << "Strich " << i+1 << " : " << binaryCode[i] << " Position X: " << start << endl;
			start+= barWidth;
			bitCounter = bitCounter / 10;
		}

	}

}






string UPCCodeScanner::readBarcode()
{
	Mat image = cvTools.loadImageAsBW("C:\\Users\\Bla\\Documents\\GitHub\\AVPRG-Projekt\\Barcode2.jpg");
	//Anfang in der Mitte
	int startY = image.rows / 2;
	cout << "Gesamtlaenge des Bildes" << image.cols << endl;
	//Durchlauf von links nach rechts
	for(int x = 0 ; x < image.cols; x++)
	{
		int pixel = image.at<uchar>(startY,x);
		if(0 == pixel)
		{
			decodingBarcode(image, x, image.cols, startY);
			break;
		}
	}

	imshow("Test", image);


	while(true){
	

		if(waitKey(10) != -1)
		{
			break; 
		}
	}
	return "";
}	
