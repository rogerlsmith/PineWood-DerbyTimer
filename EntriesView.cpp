// EntriesView.cpp : implementation file
//
// Manages the Entry View Form
//
#include "stdafx.h"
#include "derby1.h"
#include "EntriesView.h"
#include "Driver.h"
#include "AddGroup.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntriesView - Constructors / Destructors

IMPLEMENT_DYNCREATE(CEntriesView, CFormView)

CEntriesView::CEntriesView()
	: CFormView(CEntriesView::IDD)
{
	//{{AFX_DATA_INIT(CEntriesView)
	m_DriverName = _T("");
	m_NickName = _T("");
	m_CarNumber = _T("");
	//}}AFX_DATA_INIT
}

CEntriesView::~CEntriesView()
{
}

void CEntriesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntriesView)
	DDX_Text(pDX, IDC_DRIVERNAMEEDIT, m_DriverName);
	DDX_Text(pDX, IDC_NICKNAMEEDIT, m_NickName);
	DDX_Text(pDX, IDC_NUMBEREDIT, m_CarNumber);
	DDX_CBString(pDX, IDC_GROUPCOMBO, m_Group);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntriesView, CFormView)
	//{{AFX_MSG_MAP(CEntriesView)
	ON_BN_CLICKED(IDC_STORE, OnStore)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_LBN_SELCHANGE(IDC_DRIVERLIST, OnSelchangeDriverlist)
	ON_CBN_CLOSEUP(IDC_GROUPCOMBO, OnCloseupGroupcombo)
	ON_BN_CLICKED(IDC_ADDGROUP, OnAddgroup)
	ON_BN_CLICKED(IDC_CREATE_SCHEDULE, OnCreateSchedule)
	ON_BN_CLICKED(IDC_GOLINEUP, OnGolineup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntriesView diagnostics

#ifdef _DEBUG
void CEntriesView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEntriesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG
//
/////////////////////////////////////////////////////////////////////////////
// CEntriesView message handlers
//
// OnInitialUpdate - 
//
void CEntriesView::OnInitialUpdate()
{
}
//
// OnActivateView - 
// Author: RLS			Date: January 2003
//
void CEntriesView::OnActivateView(BOOL var, CView* pPtr1, CView *pPtr2)
{
	CComboBox*	pBox		= NULL;
	CString		GroupStr;
	int			count		= 0;
	int			i			= 0;
	CDerby1App* theApp		= (CDerby1App*)AfxGetApp ();

	if (var && (theApp != NULL))
	{
		pBox = (CComboBox*)GetDlgItem(IDC_GROUPCOMBO);
		if (pBox != NULL)
		{
			// clear out group list
			count = pBox->GetCount();
			for (i=0; i < count; i++)
				pBox->DeleteString (0);	
			
			// add new list
			count = theApp->m_GroupIndex;
			for (i = 0; i < count; i++)
				pBox->AddString (theApp->m_GroupList[i]);

			pBox->SetCurSel (theApp->m_CurrentGroup);
			GroupStr = theApp->m_GroupList[theApp->m_CurrentGroup];
			BuildDriverList (GroupStr);
		}
	}
}
//
// ViewUpdate - Update the view
// Author: RLS			Date: January 2003
//
void CEntriesView::ViewUpdate ()
{
	OnActivateView (false, NULL, NULL);
}
//
// Store - add or update entry in listbox
// Author: RLS			Date: January 2003
//
void CEntriesView::OnStore() 
{
	CListBox*	pBox	= NULL;
	CDriver*	pList	= NULL;
	CDriver*	pEntry	= NULL;

	// Get app pointer
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();

	// force call to DoDataExchange
	UpdateData (TRUE);

	// If there isn't a group, notify the user and return
	if ((theApp != NULL) && (theApp->m_GroupIndex == 0))
	{
		MessageBox ("You must add a group for this driver to be associated with", "No Groups", MB_OK);
		return;
	}

	m_Group = theApp->m_GroupList[theApp->m_CurrentGroup];

	if ((m_CarNumber == "") ||
			(m_DriverName == ""))
		MessageBox ("Please complete the entire form", "Entry form not complete", MB_OK);
	else
	{
		// go through the list and see if this is an update
		// or if it is a new entry.
		CString NumNameStr = m_CarNumber + " - " + m_DriverName;
		pEntry = SearchDriverlist (NumNameStr);
		if (pEntry != NULL)
		{
			// update original entry
			pEntry->SetGroup (m_Group);
			pEntry->SetNickName (m_NickName);
		}
		else
		{
			// this is a new entry
			CDriver* pNew = new (CDriver);

			pNew->SetGroup (m_Group);
			pNew->SetCarNumber (m_CarNumber);
			pNew->SetDriverName (m_DriverName);
			pNew->SetNickName (m_NickName);
			pNew->SetNumName (m_CarNumber + " - " + m_DriverName);

			CDriver* tail = theApp->GetDriverListTail ();

			// if tail is NULL, the list is empty

			if (tail == NULL)
				theApp->SetNewHead (pNew);
			else
				tail->m_pNext = pNew;

			pNew->m_pPrev = tail;

			theApp->SetNewTail (pNew);

			pBox = (CListBox*)GetDlgItem (IDC_DRIVERLIST);
			if (pBox != NULL)
			{
				pBox->AddString (m_CarNumber + " - " + m_DriverName);
			}
		}
		ResetEntriesDialog ();
	}
}
//
// ResetEntriesDialog - Reset only the edit boxes in the Entries Form
//							so that a new entry may be added.
// Author: RLS			Date: January 2003
//
void CEntriesView::ResetEntriesDialog() 
{
	CEdit*	pBox	= NULL;

	SetDlgItemText (IDC_DRIVERNAMEEDIT, "");
	SetDlgItemText (IDC_NICKNAMEEDIT, "");
	SetDlgItemText (IDC_NUMBEREDIT, "");

	pBox = (CEdit*)GetDlgItem (IDC_DRIVERNAMEEDIT);
	if (pBox != NULL)
		pBox->SetFocus ();


}
//
// OnReset - Handle Reset pick from dialog form
// Author: RLS			Date: January 2003
//
void CEntriesView::OnReset() 
{
	CListBox*	pBox	= NULL;

	ResetEntriesDialog ();
	pBox = (CListBox*)GetDlgItem (IDC_DRIVERLIST);
	if (pBox != NULL)
		pBox->SetCurSel (-1);
}
//
// OnRemove - Handle Remove pick from dialog form
// Author: RLS			Date: January 2003
//
void CEntriesView::OnRemove() 
{
	CListBox*	pBox	= NULL;
	CDriver*	pList	= NULL;
	CDriver*	pEntry	= NULL;
	CDriver*	pPrev	= NULL;
	CDriver*	pNext	= NULL;
	CString		NumNameStr;
	int			index	= 0;
	char		NumName[100];
	char		messagebuffer[200];

	
	pBox = (CListBox*)GetDlgItem (IDC_DRIVERLIST);
	if (pBox != NULL)
	{
		index = pBox->GetCurSel ();
		if (index < 0)
			MessageBox ("Please select an entry from the list to remove", "No Entry Selected", MB_OK);
		else
		{
			pBox->GetText (index, NumName);
			NumNameStr = NumName;
			pEntry = SearchDriverlist (NumNameStr);
			if (pEntry != NULL)
			{
				sprintf (messagebuffer, "Remove %s", NumName);
				if (MessageBox (messagebuffer, "Remove Entry", MB_YESNO) == IDYES)
				{
					pPrev = pEntry->m_pPrev;
					pNext = pEntry->m_pNext;

					if (pPrev != NULL)
						pPrev->m_pNext = pNext;
					else
					{
						// update head pointer
						CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
						theApp->SetNewHead (pNext);
					}

					if (pNext != NULL)
						pNext->m_pPrev = pPrev;
					else
					{
						// update tail pointer
						CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
						theApp->SetNewTail (pPrev);
					}
					
					pBox->DeleteString (index);
					ResetEntriesDialog ();

//					delete (pEntry);
				}
			}
		}
	}
}
//
// OnSelchangeDriverList - handle a new selection from the driver list
// Author: RLS			Date: January 2003
//
void CEntriesView::OnSelchangeDriverlist() 
{
	CListBox*	pBox		= NULL;
	CDriver*	pEntry		= NULL;
	CString		NumNameStr;
	char		NumName[100];
	int			index		= 0;
	
	pBox = (CListBox*)GetDlgItem (IDC_DRIVERLIST);
	if (pBox != NULL)
	{
		index = pBox->GetCurSel ();
		pBox->GetText (index, NumName);

		NumNameStr = NumName;
		pEntry = SearchDriverlist (NumNameStr);
		//
		// Update Entries Form if an entry was found
		//
		if (pEntry != NULL)
		{
			SetDlgItemText (IDC_DRIVERNAMEEDIT, pEntry->m_DriverName);
			SetDlgItemText (IDC_NICKNAMEEDIT, pEntry->m_NickName);
			SetDlgItemText (IDC_NUMBEREDIT, pEntry->m_CarNumber);
		}
	}
}
//
// SearchDriverlist - searches the DriverList for a NumName string
// Author: RLS			Date: January 2003
//
CDriver* CEntriesView::SearchDriverlist(CString NumNameStr)
{
	CDriver*	pList		= NULL;
	bool		found		= false;

	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();

	pList = theApp->GetDriverListHead ();

	// loop through the list searching for the Number-DriverName combo
	do
	{
		if ((pList == NULL) || (pList->m_NumName == NumNameStr))
			found = true;
		else
			pList = pList->m_pNext;
	} while (!found);

	return pList;
}
//
// CloseupGroupcombo - Handle the Groupcombo change event
// Author: RLS			Date: January 2003
//
void CEntriesView::OnCloseupGroupcombo() 
{
	CComboBox*		pBox = NULL;
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();

	pBox = (CComboBox*)GetDlgItem (IDC_GROUPCOMBO);
	theApp->m_CurrentGroup = pBox->GetCurSel ();

	UpdateForm ();
}
//
// BuildDriverList - Builds the DriverList control based on the selected group
// Author: RLS			Date: January 2003
//
void CEntriesView::BuildDriverList(CString Group) 
{
	CDriver*	pList		= NULL;
	CListBox*	pBox		= NULL;
	int			boxcount	= 0;

	// Get the application to get a pointer to the list head
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
	pList = theApp->GetDriverListHead ();

	if (pList != NULL)
	{
		pBox = (CListBox*)GetDlgItem (IDC_DRIVERLIST);
		if (pBox != NULL)
		{
			boxcount = pBox->GetCount();
			// clear out driver list and add new
			for (int i=0; i < boxcount; i++)
				pBox->DeleteString (0);		

			// loop through the list searching for Group
			do
			{
				if (pList->m_Group == Group)
					pBox->AddString (pList->m_NumName);

				pList = pList->m_pNext;
			} while (pList != NULL);
		}
		ResetEntriesDialog ();
	}
}
//
// UpdateForm - Update the Entries Form
// Author: RLS			Date: January 2003
//
void CEntriesView::UpdateForm() 
{
	char		NewString[100];
	CComboBox*	pBox	= NULL;
	int			index = 0;
	CString		GroupStr;  

	pBox = (CComboBox*)GetDlgItem(IDC_GROUPCOMBO);
	if (pBox != NULL)
	{
		index = pBox->GetCurSel ();
		pBox->GetLBText (index, NewString);
		GroupStr = NewString;
	}	

	BuildDriverList (GroupStr);
}
//
// Addgroup - Add a group/den to the race
// Author: RLS			Date: January 2003
//
void CEntriesView::OnAddgroup() 
{
	CComboBox*	pBox		= NULL;
	CAddGroup	NewGroup;
	CString		GroupStr;
	int			count		= 0;
	int			i			= 0;
	char		stringbuf[100];
	CDerby1App* theApp		= (CDerby1App*)AfxGetApp ();

	NewGroup.DoModal ();

	pBox = (CComboBox*)GetDlgItem(IDC_GROUPCOMBO);
	if (pBox != NULL)
	{
		// clear out group list
		count = pBox->GetCount();
		for (i=0; i < count; i++)
			pBox->DeleteString (0);	
		
		// add new list
		count = theApp->m_GroupIndex;
		for (i = 0; i < count; i++)
			pBox->AddString (theApp->m_GroupList[i]);

		GetDlgItemText (IDC_GROUPCOMBO, stringbuf, 100);
		if (strcmp (stringbuf, "") == 0)
		{
			pBox->SetCurSel (theApp->m_CurrentGroup);
			GroupStr = theApp->m_GroupList[theApp->m_CurrentGroup];
			BuildDriverList (GroupStr);
		}
	}
}
//
// OnCreateSchedule - Create Race schedules for all groups
// Author: RLS			Date: January 2003
//
void CEntriesView::OnCreateSchedule() 
{
	CDriver*		pList		= NULL;
	CGroup*			pGroup		= NULL;
	CSchedule*		pHeat		= NULL;
	CSchedule*		pCurHeat	= NULL;
	CString			GName;
	char			statstr[100];
	CDriver*		tlist[100];
	int				index = 0;
	int				groupcount	= 0;
	int				drivercount	= 0;
	int				tindex		= 0;
	CDerby1App*		theApp		= (CDerby1App*)AfxGetApp ();

	// loop through each group and 
	for (int i = 0; i < theApp->m_GroupIndex; i++)
	{
		GName  = theApp->m_GroupList[i];
		groupcount ++;
		
		// reset the list
		pList = theApp->GetDriverListHead ();
		pGroup = theApp->AddGroupSchedule (GName);
		index = 0;

		do
		{
			if (pList->m_Group == GName)
			{
				// add driver to temp group schedule if still active

				if (pList->m_Active)
				{
					tlist[index] = pList;
					drivercount ++;
					index++;
				}
			}
			pList = pList->m_pNext;
		} while (pList);

		// allocate the heats and make the schedule
		pCurHeat = pGroup->m_pHeatSched;
		tindex = 0;

		for (int j = 1; j <= index * 2; j++)
		{
			// Heat settings
			pCurHeat->m_HeatNum = j;
			pCurHeat->m_RaceComplete = false;

			// cycle twice through list 
			if (tindex >= index)
				tindex = 0;

			// Set order
			if (index >= 1)
			{
				if (tindex + 0 < index)
				{
					pCurHeat->m_Lane1 = tlist[tindex+0];
					pCurHeat->m_Name1 = tlist[tindex+0]->m_NumName;
				}
				else
				{
					pCurHeat->m_Lane1 = tlist[tindex-index+0];
					pCurHeat->m_Name1 = tlist[tindex-index+0]->m_NumName;
				}
			}

			if (index >= 2)
			{
				if (tindex + 1 < index)
				{
					pCurHeat->m_Lane2 = tlist[tindex+1];
					pCurHeat->m_Name2 = tlist[tindex+1]->m_NumName;
				}
				else
				{
					pCurHeat->m_Lane2 = tlist[tindex-index+1];
					pCurHeat->m_Name2 = tlist[tindex-index+1]->m_NumName;
				}
			}

			if (index >= 3)
			{
				if (tindex + 2 < index)
				{
					pCurHeat->m_Lane3 = tlist[tindex+2];
					pCurHeat->m_Name3 = tlist[tindex+2]->m_NumName;
				}
				else
				{
					pCurHeat->m_Lane3 = tlist[tindex-index+2];
					pCurHeat->m_Name3 = tlist[tindex-index+2]->m_NumName;
				}
			}

			if (index >= 4)
			{
				if (tindex + 3 < index)
				{
					pCurHeat->m_Lane4 = tlist[tindex+3];
					pCurHeat->m_Name4 = tlist[tindex+3]->m_NumName;
				}
				else
				{
					pCurHeat->m_Lane4 = tlist[tindex-index+3];
					pCurHeat->m_Name4 = tlist[tindex-index+3]->m_NumName;
				}
			}

			// allocate next heat - at the end this will all NULL
			pHeat				= new (CSchedule);
			pCurHeat->m_pNext	= pHeat;
			pHeat->m_pPrev		= pCurHeat;
			pCurHeat			= pHeat;

			tindex++;
		}
		// One extra heat is allocated, null the ptr and delete it
		pCurHeat->m_pPrev->m_pNext = NULL;
		delete (pCurHeat);
	}

	sprintf (statstr, "Schedule created for %d groups, of %d drivers", groupcount, drivercount);
	MessageBox (statstr, "Schedule Created", MB_OK);
}

void CEntriesView::OnGolineup() 
{
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
	theApp->SwitchView (theApp->m_pLineupView);	
}
