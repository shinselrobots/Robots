#ifndef __ROBOT_HTMLCTRL_H__
#define __ROBOT_HTMLCTRL_H__

#include <afxhtml.h>


// Microsoft Systems Journal -- January 2000
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably Windows NT too.
//

static HWND GetLastChild(HWND hwndParent);

class CMyIEWnd : public CWnd {
public:

	// overrides right-mouse click Browser ContextMenu
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   DECLARE_MESSAGE_MAP();
};


class CHtmlCtrl : public CHtmlView {
public:
   CHtmlCtrl() { }
   ~CHtmlCtrl() { }

   BOOL CreateFromStatic(UINT nID, CWnd* pParent);

   // Normally, CHtmlView destroys itself in PostNcDestroy,
   // but we don't want to do that for a control since a control
   // is usually implemented as a stack object in a dialog.
   //
   virtual void PostNcDestroy() {  }

   // overrides to bypass MFC doc/view frame dependencies
   afx_msg void OnDestroy();
   afx_msg int  OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);

    // override to trap "app:" pseudo protocol
   virtual void OnBeforeNavigate2( LPCTSTR lpszURL,
      DWORD nFlags,
      LPCTSTR lpszTargetFrameName,
      CByteArray& baPostedData,
      LPCTSTR lpszHeaders,
      BOOL* pbCancel );

   // override to handle links to "app:mumble...". lpszWhere will be "mumble"
   virtual void OnAppCmd(LPCTSTR lpszWhere);

	virtual void OnNavigateComplete2(LPCTSTR strURL);

protected:
  CMyIEWnd m_myIEWnd;

   DECLARE_MESSAGE_MAP();
   DECLARE_DYNAMIC(CHtmlCtrl)



};


#endif
