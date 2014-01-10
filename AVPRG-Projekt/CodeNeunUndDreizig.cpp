#include "CodeNeunUndDreizig.h"
using namespace std;
using namespace cv;
CodeNeunUndDreizig::CodeNeunUndDreizig()
{
	bitToStringMap.setMap(110100,"0");
	bitToStringMap.setMap(100100001,"1");
	bitToStringMap.setMap(1100001,"2");
	bitToStringMap.setMap(101100000,"3");
	bitToStringMap.setMap(110001,"4");
	bitToStringMap.setMap(10011000,"5");
	bitToStringMap.setMap(1110000,"6");
	bitToStringMap.setMap(100101,"7");
	bitToStringMap.setMap(100100100,"8");
	bitToStringMap.setMap(1100100,"9");
	bitToStringMap.setMap(100001001,"A");
	bitToStringMap.setMap(1001001,"B");
	bitToStringMap.setMap(101001000,"C");
	bitToStringMap.setMap(11001,"D");
	bitToStringMap.setMap(100011000,"E");
	bitToStringMap.setMap(1011000,"F");
	bitToStringMap.setMap(1101,"G");
	bitToStringMap.setMap(100001100,"H");
	bitToStringMap.setMap(1001100,"I");
	bitToStringMap.setMap(11100,"J");
	bitToStringMap.setMap(100000011,"K");
	bitToStringMap.setMap(1000011,"L");
	bitToStringMap.setMap(101000010,"M");
	bitToStringMap.setMap(10011,"N");
	bitToStringMap.setMap(100010010,"O");
	bitToStringMap.setMap(1010010,"P");
	bitToStringMap.setMap(111,"Q");
	bitToStringMap.setMap(100000110,"R");
	bitToStringMap.setMap(1000110,"S");
	bitToStringMap.setMap(10110,"T");
	bitToStringMap.setMap(110000001,"U");
	bitToStringMap.setMap(11000001,"V");
	bitToStringMap.setMap(111000000,"W");
	bitToStringMap.setMap(10010001,"X");
	bitToStringMap.setMap(110010000,"Y");
	bitToStringMap.setMap(11010000,"Z");
	bitToStringMap.setMap(10000101,"-");
	bitToStringMap.setMap(110000100,"_");
	bitToStringMap.setMap(11000100," ");
	bitToStringMap.setMap(10010100,"*");
	bitToStringMap.setMap(10101000,"$");
	bitToStringMap.setMap(10100010,"/");
	bitToStringMap.setMap(10001010,"+");
	bitToStringMap.setMap(101010,"%");

	binaryNumbersSize = 0;
}

CodeNeunUndDreizig::~CodeNeunUndDreizig()
{
	bitToStringMap.clearMap();
}

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
		// zweiter Stern wurde gefunden. Code fertig ausgelesen. Nun muss konvertiert werden
		if (!foundCode)	
		{
			bool successConvert = true;
			for(int i = 0; i < binaryNumbers.size(); i++)
			{
				successConvert = convert(binaryNumbers[i]);
			}
			if(successConvert)
			{
				return 1;
			}
			else
			{
				binaryNumbersSize = 0;
				binaryNumbers.clear();
				return -1;
			}
		}
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
			if(start < image.cols-5)
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
	binaryNumbersSize++;
	binaryNumbers.resize(binaryNumbersSize);
	binaryNumbers.at(binaryNumbersSize-1) = finalBiNum;
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

	if (0 < binaryNumber)
		cout << "Die Binärzahl lautet: " << binaryNumber << endl;
	
	return binaryNumber;
}

bool CodeNeunUndDreizig::convert(int binaryNumber)
{
	string tmpValue;
	bool successConvert = true;
	tmpValue = bitToStringMap.convertBitToString(binaryNumber);
	if(0 < tmpValue.length())
	{
		result += tmpValue;
		successConvert = true;
	}		
	else
	{
		successConvert = false;
	}
	return successConvert;
}