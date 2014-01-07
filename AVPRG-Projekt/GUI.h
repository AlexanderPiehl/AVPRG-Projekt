#ifndef GUI_H_
#define GUI_H_
#include <afxwin.h>
class GUI : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainGUI : public CFrameWnd 
{ 
 public: 
	CMainGUI(); 
	 void OnLButtonDown(UINT nFlags, CPoint point);
	////DECLARE_MESSAGE_MAP()
};

//BEGIN_MESSAGE_MAP( CMainGUI, CFrameWnd)
//      ON_WM_LBUTTONDOWN() 
//END_MESSAGE_MAP()


#endif

