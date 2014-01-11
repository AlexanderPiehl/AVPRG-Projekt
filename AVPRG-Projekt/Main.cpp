#include "GUI.h"
using namespace AVPRGProjekt;

[STAThreadAttribute]
int main()
{
	//GUI vorbereiten
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausführen
	Application::Run(gcnew GUI());
	return 0;
}