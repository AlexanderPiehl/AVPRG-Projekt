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
};

#endif

