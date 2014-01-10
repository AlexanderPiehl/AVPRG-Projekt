#include "CodeNeunUndDreizig.h"
using namespace std;
using namespace cv;
CodeNeunUndDreizig::CodeNeunUndDreizig()
{
	/*
	binToIntMap[110100]= "0";
	binToIntMap[100100001]= "1";
	binToIntMap[1100001]= "2";
	binToIntMap[101100000]= "3";
	binToIntMap[110001]= "4";
	binToIntMap[100110000]= "5";
	binToIntMap[1110000]= "6";
	binToIntMap[100101]= "7";
	binToIntMap[100100100]= "8";
	binToIntMap[1100100]= "9";
	binToIntMap[100001001] = "A";
	binToIntMap[1001001] = "B";
	binToIntMap[101001000] = "C";
	binToIntMap[11001] = "D";
	binToIntMap[100011000] = "E";
	binToIntMap[1011000] = "F";
	binToIntMap[1101] = "G";
	binToIntMap[100001100] = "H";
	binToIntMap[1001100] = "I";
	binToIntMap[11100] = "J";
	binToIntMap[100000011] = "K";
	binToIntMap[1000011] = "L";
	binToIntMap[101000010] = "M";
	binToIntMap[10011] = "N";
	binToIntMap[100010010] = "O";
	binToIntMap[1010010] = "P";
	binToIntMap[111] = "Q"; 
	binToIntMap[100000110] = "R";
	binToIntMap[1000110] = "S";
	binToIntMap[10110] = "T";
	binToIntMap[110000001] = "U";
	binToIntMap[11000001] = "V";
	binToIntMap[111000000] = "W";
	binToIntMap[10010001] = "X";
	binToIntMap[110010000] = "Y";
	binToIntMap[11010000] = "Z";
	binToIntMap[10000101] = "-";
	binToIntMap[110000100] = "_";
	binToIntMap[11000100] = " ";
	binToIntMap[10010100] = "*"
	binToIntMap[10101000] = "$";
	binToIntMap[10100010] = "/";
	binToIntMap[10001010] = "+";
	binToIntMap[101010] = "%";
	*/
}

CodeNeunUndDreizig::~CodeNeunUndDreizig()
{}

int CodeNeunUndDreizig::decodingBarcode(cv::Mat image, int& start, int end, int y)
{
	// suche nach einem Stern als Anfangszeichen
	bool foundCode = readNineElements(image, start, y, false);
	while (foundCode)
	{
		int pixel = image.at<uchar>(y,start);

		// Trennzeichen auslassen
		//while (pixel == SPACE)
		//{
			//start++;
		//}
		// Auslesen des Codes bis zum zweiten Stern
		if (pixel == 0)
		foundCode = readNineElements(image, start, y, foundCode);
		start++;

		// wenn bis kurz vor Ende des Bildes noch kein zweiter Stern gefunden wurde, abbrechen
		if( start > end-10)
			return -1;
		// zweiter Stern wurde gefunden. Code fertig ausgelesen
		if (!foundCode)
			return 1;
	}
	return -1;
}


bool CodeNeunUndDreizig::readNineElements(Mat image, int& start, int y, bool foundCode)
{
	int code39Sign [9] = {BAR,SPACE,BAR,SPACE,BAR,SPACE,BAR,SPACE,BAR};
	int elementWidth [9] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0};
	int pixel = image.at<uchar>(y,start);
	// cout << "Test wo x gerade ist: " << start << endl;
	for(int i = 0; i < 9; i++)
	{
		while(code39Sign[i] == pixel)
		{
			//if (y == 44)
				// cout << "Guard an der Stelle x: " << start << " y: " << y << endl;
			// abfangen, dass er nicht über den Rand des Bildes prüft
			if(start < image.cols-50)
			{
				// Breite der einzelnen Elemente wird gespeichert
				elementWidth[i]++;

				start++;
				pixel = image.at<uchar>(y,start);
				
			}else
				break;
		}
	}
	int average = averageNumber(elementWidth);
	int finalBiNum = binaryNumber(elementWidth, average);
	if (10010100 == finalBiNum)
		foundCode = !foundCode;
	return foundCode;
}


// erzeugt aus allen Zahlen im Array den Durchschnitt 
int CodeNeunUndDreizig::averageNumber(int* elementWidth)
{
	int sum = 0;
	int average = 0;

	for (int i = 0; i < 9; i++)
	{
		sum = sum + elementWidth[i];
	}
	average = sum / 9;
	return average;
	
}

// erzeugt die Binärzahl indem sie den 3 breitesten streifen eine 1 zuweist
int CodeNeunUndDreizig::binaryNumber(int* elementWidth, int average)
{
	int bitCounter = 100000000;
	int binaryNumber = 0;

	for (int i = 0; i < 9; i++)
	{
		if(elementWidth[i] > average)
			binaryNumber = binaryNumber + bitCounter;
		bitCounter = bitCounter / 10;
		
	}

	if (0 <binaryNumber)
		cout << "Die Binärzahl lautet: " << binaryNumber << endl;
	return binaryNumber;
}