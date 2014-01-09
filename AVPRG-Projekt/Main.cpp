#include "CodeScanner.h"
#include "UPCCodeScanner.h"
#include "CodeNeunUndDreizig.h"
using namespace std;

int main()
{
	//GUI gui;
	//gui.InitInstance();
	UPCCodeScanner scanner;
	//CodeNeunUndDreizig scanner;
	scanner.readBarcode();

	cout << "test" << endl;
	return 0;
}