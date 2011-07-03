#if !defined(AFX_DIAGNOSTICS_H__C8CE4261_1109_11D7_B111_005004983D52__INCLUDED_)
#define AFX_DIAGNOSTICS_H__C8CE4261_1109_11D7_B111_005004983D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Diagnostics.h : header file
//
#include "GCClock.h"
#include "resource.h"


/////////////////////////////////////////////////////////////////////////////
// CDiagnostics dialog

class CDiagnostics : public CDialog
{
// Construction
public:
	bool m_DiagOn;
	int pulsecount1;
	int pulsecount2;
	int pulsecount3;
	int pulsecount4;
	int pulsecount5;

	CDiagnostics(CWnd* pParent = NULL);   // standard constructor

	void CDiagnostics::DiagTimerProc (HWND hwnd, UINT msg, UINT id, DWORD curtime);

	enum {DIAG_UPDATE_TIMER_ID = 3};

// Dialog Data
	//{{AFX_DATA(CDiagnostics)
	enum { IDD = IDD_DIAGNOSTICS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiagnostics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDiagnostics)
	afx_msg void OnDiagStart();
	afx_msg void OnDiagStop();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAGNOSTICS_H__C8CE4261_1109_11D7_B111_005004983D52__INCLUDED_)
