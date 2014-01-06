#include "CodeScanner.h"
#include "UPCCodeScanner.h"
#include "GUI.h"
using namespace std;

int main()
{
	//GUI gui;
	//gui.InitInstance();
	UPCCodeScanner scanner;
	scanner.readBarcode();

	
	return 0;
}