#include "GUI.h"

GUI gui;

CMainGUI::CMainGUI()
{
	Create ( NULL, _T("MFC-Anwendungsskelett") );
}

BOOL GUI::InitInstance() 
{ 
 m_pMainWnd = new CMainGUI; 
 m_pMainWnd ->ShowWindow( m_nCmdShow ); 
 return TRUE; 
}
