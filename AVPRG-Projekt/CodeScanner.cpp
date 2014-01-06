#include "CodeScanner.h"
using namespace cv;
using namespace std;

CodeScanner::CodeScanner()
{
}

CodeScanner::~CodeScanner()
{}

string CodeScanner::readBarcode()
{
	Mat image = cvTools.loadImageAsBW("../Barcode1rot.jpg");
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