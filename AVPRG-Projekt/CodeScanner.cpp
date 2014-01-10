#include "CodeScanner.h"
using namespace cv;
using namespace std;

CodeScanner::CodeScanner()
{}

CodeScanner::~CodeScanner()
{}

string CodeScanner::readBarcode()
{
	Mat image;
	try
	{
	image = cvTools.loadImageAsBW(path);
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		std::cout << "exception caught: " << err_msg << std::endl;
	}
	// Ergebnis Fehler oder Ein richtiges Ergebnis
	int  outcome = 0;
	// Hiermit wird nur eine Guard gesucht, wenn auch eine Quiet zone gefunden wurde
	int whitePixelCounter = 0;
	//Quiet zone gefunden oder nicht
	bool foundQuietZone = false;
	//Anfang in der Mitte
	int startY = image.rows / 2;
	cout << "Gesamtlaenge des Bildes" << image.cols << endl;
	//Durchlauf von links nach rechts
	for (int y =44; y < image.rows; y=y+4)
	{
		cout << "y ist: " << y << endl;
		for(int x = 0 ; x < image.cols-100; x++)
		{
			int pixel = image.at<uchar>(y,x);
			//bei weiﬂen Pixel +1 um eine quiet zone zu suchen
			if(255 == pixel)
				whitePixelCounter++;
			// Wenn eine quiet zonde gefunden, darf nach einer Guard gesucht werden.
			if (9 < whitePixelCounter)
				foundQuietZone = true;
			if(0 == pixel && foundQuietZone)
			{
				foundQuietZone = false;
				whitePixelCounter = 0;
				outcome = decodingBarcode(image, x, image.cols, y);
				if(1 == outcome)
					break;
			}
		}
		if(1 == outcome)
			break;
	}

	if (1 > outcome)
		cout << "Keinen Barcode gefunden oder Barcode nicht lesbar";
	/*while(true){
	

		if(waitKey(10) != -1)
		{
			break; 
		}
	}*/
	return "";
}