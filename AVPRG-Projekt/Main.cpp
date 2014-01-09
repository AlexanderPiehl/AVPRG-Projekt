#include "CodeScanner.h"
#include "UPCCodeScanner.h"
using namespace std;

int main()
{
	//GUI gui;
	//gui.InitInstance();
	UPCCodeScanner scanner;
	scanner.readBarcode();

	cout << "test" << endl;
	return 0;
}