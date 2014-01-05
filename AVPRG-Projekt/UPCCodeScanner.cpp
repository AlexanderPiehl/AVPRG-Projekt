#include "UPCCodeScanner.h"
using namespace std;
using namespace cv;

string UPCCodeScanner::decodingBarcode(Mat image, int& start, int end, int y)
{
	int bit_width = getBitWidthAndSkipLGuard(image, start, y);
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
	//Kontrolle ob die Weiten gleich sind
	if(widthBarFirst == widthBarLast && widthBarFirst == widthSpace)
		return widthBarFirst;
	else
	{
		//Fehlermeldung
		return 0;
	}
}

string UPCCodeScanner::readBarcode()
{
	Mat image = cvTools.loadImageAsBW("C:\\Users\\Bla\\Documents\\GitHub\\AVPRG-Projekt\\Barcode1rot.jpg");
	//Anfang in der Mitte
	int startY = image.rows / 2;

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
