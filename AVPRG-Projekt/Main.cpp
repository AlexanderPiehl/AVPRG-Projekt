#include "GUI.h"
using namespace AVPRGProjekt;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Hauptfenster erstellen und ausf�hren
	Application::Run(gcnew GUI());
	return 0;
}