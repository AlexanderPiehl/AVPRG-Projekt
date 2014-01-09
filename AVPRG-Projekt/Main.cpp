#include "CodeScanner.h"
#include "UPCCodeScanner.h"
#include "GUI.h"
using namespace std;
using namespace AVPRGProjekt;

[STAThreadAttribute]
int main()
{
//	//GUI gui;
//	//gui.InitInstance();
//	//GUI gui;
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew GUI());
	return 0;
//	UPCCodeScanner scanner;
//	scanner.readBarcode();
//
//	cout << "test" << endl;
//	return 0;
}