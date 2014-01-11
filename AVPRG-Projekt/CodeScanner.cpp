#include "CodeScanner.h"
using namespace cv;
using namespace std;

CodeScanner::CodeScanner(){}

CodeScanner::~CodeScanner(){}

int CodeScanner::readBarcode()
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
		return -2;
	}
	// Ergebnis Fehler oder Ein richtiges Ergebnis;1= barcode gefunden, kleiner 1 = Fehler
	int  outcome = 0;
	// Hiermit wird nur eine Guard gesucht, wenn auch eine Quiet zone gefunden wurde
	int whitePixelCounter = 0;
	//Quiet zone gefunden oder nicht
	bool foundQuietZone = false;
	cout << "Gesamtlaenge des Bildes" << image.cols << endl;
	
	//Durchlauf von links nach rechts
	for (int y =0; y < image.rows; y=y+4)
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
			//Wenn QuietZone gefonden wurden ist und ein schwarzer Pixel kommt, wird versucht den Barcode auszulesen
			if(0 == pixel && foundQuietZone)
			{
				foundQuietZone = false;
				whitePixelCounter = 0;
				result = "";
				outcome = decodingBarcode(image, x, image.cols, y);
				//Abfrage, ob Barcode gefunden
				if(1 == outcome && result.length() > 0)
					break;
			}
		}
		if(1 == outcome && result.length() > 0)
			break;
	}

	if (1 > outcome)
		cout << "Keinen Barcode gefunden oder Barcode nicht lesbar";

	return outcome;
}