// AddGroup.cpp : implementation file
//

#include "stdafx.h"
#include "derby1.h"
#include "AddGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddGroup dialog


CAddGroup::CAddGroup(CWnd* pParent /*=NULL*/)
	: CDialog(CAddGroup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddGroup)
	m_DenNumber = _T("");
	m_Level = _T("");
	m_PackNumber = _T("");
	//}}AFX_DATA_INIT
}


void CAddGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddGroup)
	DDX_Text(pDX, IDC_DENEDIT, m_DenNumber);
	DDX_CBString(pDX, IDC_LEVELCOMBO, m_Level);
	DDX_Text(pDX, IDC_PACKEDIT, m_PackNumber);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddGroup, CDialog)
	//{{AFX_MSG_MAP(CAddGroup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddGroup message handlers
// Author: RLS			Date: December 2002
void CAddGroup::OnOK() 
{
	CString		GroupStr;

	UpdateData (TRUE);

	if ((m_PackNumber == "") ||
		(m_Level == "") ||
		(m_DenNumber == ""))
	{
		MessageBox ("All fields must be completed", "Missing info", MB_OK);
		return;
	}

	GroupStr = m_PackNumber + " " + m_Level + " " + m_DenNumber;

	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();

	if (theApp->m_GroupIndex < 99)
	{
		theApp->m_GroupList[theApp->m_GroupIndex] = GroupStr;
		theApp->m_CurrentGroup = theApp->m_GroupIndex;
		theApp->m_GroupIndex++;
	}
	else
		MessageBox ("There are too many groups being used", "Too many groups", MB_OK);

	CDialog::OnOK();
}
