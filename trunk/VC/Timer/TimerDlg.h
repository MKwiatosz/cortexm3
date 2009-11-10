// TimerDlg.h : header file
//

#if !defined(AFX_TIMERDLG_H__1ACE2D08_6437_4E8A_8BD9_63A5D8B85B94__INCLUDED_)
#define AFX_TIMERDLG_H__1ACE2D08_6437_4E8A_8BD9_63A5D8B85B94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Digistatic.h"

/////////////////////////////////////////////////////////////////////////////
// CTimerDlg dialog

class CTimerDlg : public CDialog
{
// Construction
public:
	CTimerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTimerDlg)
	enum { IDD = IDD_TIMER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CDigiStatic	m_lcd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTimerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMERDLG_H__1ACE2D08_6437_4E8A_8BD9_63A5D8B85B94__INCLUDED_)
