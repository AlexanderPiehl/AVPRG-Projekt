#include "CodeScanner.h"
using namespace cv;

CodeScanner::CodeScanner()
{
	
}

CodeScanner::~CodeScanner()
{}

string CodeScanner::readBarcode()
{
	Mat imageRGB = cvTools.loadImage("C:\\Users\\Bla\\Documents\\GitHub\\AVPRG-Projekt\\Barcode1rot.jpg");
	Mat imageGrey;
	cvtColor(imageRGB,imageGrey,CV_RGB2GRAY);
	Mat imageBW = imageGrey > 10;
	imshow("Test", imageBW);

	
	while(true){
	

		if(waitKey(10) != -1)
		{
			break; 
		}
	}
	return "";
}