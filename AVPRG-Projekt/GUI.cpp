#include "GUI.h"

GUI gui;

CMainGUI::CMainGUI()
{
	Create ( NULL, _T("MFC-Anwendungsskelett") );
	
}

void CMainGUI::OnLButtonDown(UINT nFlags, CPoint point) 
{
	static LPCTSTR msg = TEXT("MyApp");
   CFrameWnd::OnLButtonDown(nFlags, point);
   MessageBox(msg);
}

BOOL GUI::InitInstance() 
{ 
 m_pMainWnd = new CMainGUI; 
 m_pMainWnd ->ShowWindow( m_nCmdShow ); 
 return TRUE; 
}
