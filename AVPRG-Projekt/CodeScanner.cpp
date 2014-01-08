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
	Mat image = cvTools.loadImageAsBW("../BarcodeRotaDemo.jpg");
	int  outcome = 0;
	//Anfang in der Mitte
	int startY = image.rows / 2;
	cout << "Gesamtlaenge des Bildes" << image.cols << endl;
	//Durchlauf von links nach rechts
	for (int y = 0; y < image.rows; y=y+4)
	{
		cout << "y ist: " << y << endl;
		for(int x = 0 ; x < image.cols-100; x++)
		{
			int pixel = image.at<uchar>(y,x);
			if(0 == pixel)
			{
				outcome = decodingBarcode(image, x, image.cols, y);
				if(1 == outcome)
					break;
			}
		}
		if(1 == outcome)
			break;
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