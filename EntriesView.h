#if !defined(AFX_ENTRIESVIEW_H__8B95D616_F321_11D6_B10F_005004983D52__INCLUDED_)
#define AFX_ENTRIESVIEW_H__8B95D616_F321_11D6_B10F_005004983D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EntriesView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEntriesView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


#include <AFXPRIV.H>

class CEntriesView : public CFormView
{
public:
	void ResetEntriesDialog (void);
	static CDriver* SearchDriverlist(CString NumNameStr);
	void BuildDriverList(CString Group);
	void UpdateForm();
	CEntriesView();           // protected constructor used by dynamic creation
	void OnActivateView(BOOL var, CView* pPtr1, CView *pPtr2);
	void CEntriesView::ViewUpdate ();
	void OnInitialUpdate();
	DECLARE_DYNCREATE(CEntriesView)

// Form Data
public:
	//{{AFX_DATA(CEntriesView)
	enum { IDD = IDD_ENTRIESFORM };
	CString	m_DriverName;
	CString	m_NickName;
	CString	m_CarNumber;
	CString	m_Group;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEntriesView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEntriesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CEntriesView)
	afx_msg void OnStore();
	afx_msg void OnReset();
	afx_msg void OnRemove();
	afx_msg void OnSelchangeDriverlist();
	afx_msg void OnCloseupGroupcombo();
	afx_msg void OnAddgroup();
	afx_msg void OnCreateSchedule();
	afx_msg void OnGolineup();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ENTRIESVIEW_H__8B95D616_F321_11D6_B10F_005004983D52__INCLUDED_)
