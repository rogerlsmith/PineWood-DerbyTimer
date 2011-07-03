#if !defined(AFX_ADDGROUP_H__FC689596_F706_11D6_B10F_005004983D52__INCLUDED_)
#define AFX_ADDGROUP_H__FC689596_F706_11D6_B10F_005004983D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddGroup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddGroup dialog

class CAddGroup : public CDialog
{
// Construction
public:
	CAddGroup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddGroup)
	enum { IDD = IDD_ADDGROUPDIALOG };
	CString	m_DenNumber;
	CString	m_Level;
	CString	m_PackNumber;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddGroup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddGroup)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDGROUP_H__FC689596_F706_11D6_B10F_005004983D52__INCLUDED_)
