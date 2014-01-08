#include "UPCCodeScanner.h"
using namespace std;
using namespace cv;

int UPCCodeScanner::decodingBarcode(Mat image, int& start, int end, int y)
{
	int bit_width = getBitWidthAndSkipGuard(image, start, y);
	if(0 < bit_width)
	{
		readCode(image, start, y, bit_width, true);
		skipMGuard(image, start, y);
		readCode(image, start, y, bit_width, false);
		// cout << "Bit Weite: " << bit_width << " ; X: " << start <<endl;
		// Überprüfung der Prüfziffer hier noch einfügen für den richtigen return

		// Der Barcode wurde richtig erkannt
		return 1;
	}
	else
	{
		// Fehler, keine Guard gefunden
		cout << "keine Guard gefunden an der stelle x: " << start << " und y: " << y <<endl;
		return -1;
	}
	
}

int UPCCodeScanner::getBitWidthAndSkipGuard(Mat image, int& start, int y)
{
	int lGuard [3] = {BAR,SPACE,BAR};
	int widthBarFirst = 0;
	int widthSpace = 0;
	int widthBarLast = 0;
	int pixel = image.at<uchar>(y,start);
	// cout << "Test wo x gerade ist: " << start << endl;
	for(int i = 0; i < 3; i++)
	{
		while(lGuard[i] == pixel)
		{
			// abfangen, dass er nicht über den Rand des Bildes prüft
			if(start < image.cols-1)
				{
				start++;
				pixel = image.at<uchar>(y,start);

				if(0 == i)
					widthBarFirst++;
				else if(1 == i)
					widthSpace++;
				else if(2 == i)
					widthBarLast++;

				// Überprüfung ob die Bars noch eine Pixelanzahl im Bereich des möglichen haben.
				int firstBarBorderline = skipTooThickBars(image, widthBarFirst);
				int secondBarBorderline = skipTooThickBars(image, widthSpace);
				int thirdBarBorderline = skipTooThickBars(image, widthBarLast);
				int borderline = firstBarBorderline + secondBarBorderline + thirdBarBorderline;
				if(3 > borderline)
					return -1;
				
			}else
				break;
		}
	}
	// cout << "Test wo x gerade ist: " << start << endl;
	//Kontrolle ob 2 Weiten gleich sind, wenn nicht -1 als Fehler
	if(widthBarFirst == widthBarLast)
		return widthBarFirst;
	else if(widthBarFirst == widthSpace)
		return widthBarFirst;
	else if(widthSpace == widthBarLast)
		return widthSpace;
	else
		// Entweder keine Guard getroffen oder Guard ist zu beschädigt um sie zu lesen
		return -1;
}

// falls ein Balken bei der Überprüfung dicker wird als es theoretisch möglich ist, gibt die Methode -1 zurück zum Abbruch
int UPCCodeScanner::skipTooThickBars(cv::Mat image, int barThickness)
{
	int borderline = image.cols/100;
	if( barThickness > borderline)
		return -1;
	else
		return 1;
}

// Diese Methode ließt den eigentlichen Code zwicshen den Guards aus und speichert ihm in einem Array
void UPCCodeScanner::readCode(Mat image, int& start, int y, int barWidth, bool isLeft)
{
	bool blackBar = false;
	// Speicher für die einzelnen 7 Bits
	int binaryCode [6] = {0,0,0,0,0,0};
	int pixel;
	// die variable setzt die Bits von der 7. bis 1. Stelle
	int bitCounter;
	for (int i = 0; i < 6;i++)
	{
		// Die Bits werden vor jedem Durchgang wieder auf das 7. gesetzt
		bitCounter = 1000000;
		for (int l = 0; l < 7;l++)
		{
			// Überprüfung ob der nächste Pixel eine andere Farbe hat. Wenn ja gab es höchstwahrscheinlich einen Pixelfehler
			// Dieser wird behoben und x einen nach rechts auf das richtige Feld gesetzt
			checkNextPixel(image, start,y);
			pixel = image.at<uchar>(y,start);
			// bei einem Farbwechsel
			if (BAR == pixel && !blackBar || SPACE == pixel && blackBar)
			{
				// überfrüft ob x durch einen Pixelfehler x einen zu weit rechts ist. Falls ja wird dies korrigiert
				ignoreBadPixel(image, blackBar, start, y);
			}
			pixel = image.at<uchar>(y,start);

			// Wenn der Code links von der mittleren Guard ist
			if(isLeft)
			{
				// Schwarz = 1, Weiß = 0
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
			// Wenn der Code rechts von der mittleren Guard ist
			else
			{
				// Schwaz = 0, weiß = 1
				// invertierung führt dazu, dass man nur eine Tabelle zum entschlüsseln braucht.
				// Die rechte Seite wird nämlich invertiert von der linken ausgelesen
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
			
			// cout << "Strich " << i+1 << " : " << binaryCode[i] << " Position X: " << start << endl;
			// Sprung um eine Standardlänge weiter
			start+= barWidth;
			// der bit Counter wird durch 10 geteilt um beim nächsten Durchgang das Bit einen weiter rechts zu setzten
			bitCounter = bitCounter / 10;
		}
	}
	cout << "y ist: " << y << endl;
	for(int i = 0; i < 6; i++)
	{
		if(binaryCode[i] > 0)
		{
			cout << "Strich " << i << ": "<< binaryCode[i] << endl;
		}
	}
}


// Überprüfung ob der nächste Pixel eine andere Farbe hat. Wenn ja gab es höchstwahrscheinlich einen Pixelfehler
// Dieser wird behoben und x einen nach rechts auf das richtige Feld gesetzt
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

// wenn man bei der mittleren Guard angekommen ist, sorgt diese Methode dafür, dass sie übersprungen wird
void UPCCodeScanner::skipMGuard(Mat image, int& start, int y)
{
	int mGuard[5] = {SPACE,BAR,SPACE,BAR,SPACE};
	int pixel = image.at<uchar>(y,start);
	//cout << "Test wo x gerade ist: " << start << endl;
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