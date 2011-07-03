// Diagnostics.cpp : implementation file
//

#include "stdafx.h"
#include "derby1.h"
#include "Diagnostics.h"
#include <conio.h>

#define HIGH_BASE_ADDRESS      0x03BC                 // printer port base address
#define HIGH_DATA_REGISTER     (HIGH_BASE_ADDRESS+0)  //  address of data register
#define HIGH_STATUS_REGISTER   (HIGH_BASE_ADDRESS+1)  //  address of status register
#define HIGH_CONTROL_REGISTER  (HIGH_BASE_ADDRESS+2)  //  address of control register

#define MID_BASE_ADDRESS      0x0378                  // printer port base address
#define MID_DATA_REGISTER     (MID_BASE_ADDRESS+0)    //  address of data register
#define MID_STATUS_REGISTER   (MID_BASE_ADDRESS+1)    //  address of status register
#define MID_CONTROL_REGISTER  (MID_BASE_ADDRESS+2)    //  address of control register

#define LOW_BASE_ADDRESS      0x0278                  // printer port base address
#define LOW_DATA_REGISTER     (LOW_BASE_ADDRESS+0)    //  address of data register
#define LOW_STATUS_REGISTER   (LOW_BASE_ADDRESS+1)    //  address of status register
#define LOW_CONTROL_REGISTER  (LOW_BASE_ADDRESS+2)    //  address of control register

short _stdcall Inp32(short PortAddress);
void _stdcall Out32(short PortAddress, short data);

static unsigned char stat_reg;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiagnostics dialog


CDiagnostics::CDiagnostics(CWnd* pParent /*=NULL*/)
	: CDialog(CDiagnostics::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiagnostics)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDiagnostics::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CDiagnostics)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiagnostics, CDialog)
	//{{AFX_MSG_MAP(CDiagnostics)
	ON_BN_CLICKED(IDC_DIAG_START, OnDiagStart)
	ON_BN_CLICKED(IDC_DIAG_STOP, OnDiagStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#if 0
int CDiagnostics::OnInitialUpdate()
{
	return (0);
}
#endif
/////////////////////////////////////////////////////////////////////////////
// CDiagnostics message handlers

void CDiagnostics::OnDiagStart() 
{
//	UINT id = this->SetTimer(DIAG_UPDATE_TIMER_ID, 5, (TIMERPROC)DiagTimerProc);
//	UINT id = this->SetTimer(DIAG_UPDATE_TIMER_ID, 5, NULL);
	char	result = (char) 0xff;
	char	buff[10];
	MSG		msg;
	bool	bypass = false;
	CString sPortName;

	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
	
	// set status register
	sPortName = theApp->GetPort ();
	if (sPortName == "LPT1")
		stat_reg = (unsigned char)HIGH_STATUS_REGISTER;
	if (sPortName == "LPT2")
		stat_reg = (unsigned char)MID_STATUS_REGISTER;
	if (sPortName == "LPT3")
		stat_reg = (unsigned char)LOW_STATUS_REGISTER;


	if (theApp != NULL)
	{

		pulsecount1 = 0;
		pulsecount2 = 0;
		pulsecount3 = 0;
		pulsecount4 = 0;
		pulsecount5 = 0;
		m_DiagOn = true;

		bypass = theApp->m_BypassSwitch;
		result = 0;
		do
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
			  if ((msg.message == WM_QUIT) || (msg.message == WM_KEYDOWN) || (!m_DiagOn))
				  break;

			  TranslateMessage(&msg);
			  DispatchMessage(&msg);
			}
			else
			{

				if (!bypass)
//					result = (_inp (STATUS_REGISTER) & 0xf8);
					result = (Inp32 (stat_reg) & 0xf8);					//NT, XP, Win2K compatibility

				if (!(result & 0x08))	// pin 15 (Error)
				{
					pulsecount1++;
					sprintf (buff, "%d", pulsecount1);
					SetDlgItemText (IDC_GATE_STAT, "1");
					SetDlgItemText (IDC_GATE_PC, buff);
				}
				else
				{
					SetDlgItemText (IDC_GATE_STAT, "0");
					pulsecount1 = 0;
				}

				if (!(result & 0x10))	// pin 13 (Selected)
				{
					pulsecount2++;
					sprintf (buff, "%d", pulsecount2);
					SetDlgItemText (IDC_1_STAT, "1");
					SetDlgItemText (IDC_1_PC, buff);
				}
				else
				{
					SetDlgItemText (IDC_1_STAT, "0");
					pulsecount2 = 0;
				}

				if (!(result & 0x20))	// pin 12 (No Paper)
				{
					pulsecount3++;
					sprintf (buff, "%d", pulsecount3);
					SetDlgItemText (IDC_2_STAT, "1");
					SetDlgItemText (IDC_2_PC, buff);
				}
				else
				{
					SetDlgItemText (IDC_2_STAT, "0");
					pulsecount3 = 0;
				}

				if ((result & 0x80))	// pin 11 (Busy)   <--- this pin inverted
				{
					pulsecount4++;
					sprintf (buff, "%d", pulsecount4);
					SetDlgItemText (IDC_3_STAT, "1");
					SetDlgItemText (IDC_3_PC, buff);
				}
				else
				{
					SetDlgItemText (IDC_3_STAT, "0");
					pulsecount4 = 0;
				}


				if (!(result & 0x40))	// pin 10 (Ack)
				{
					pulsecount5++;
					sprintf (buff, "%d", pulsecount5);
					SetDlgItemText (IDC_4_STAT, "1");
					SetDlgItemText (IDC_4_PC, buff);
				}
				else 
				{
					SetDlgItemText (IDC_4_STAT, "0");
					pulsecount5 = 0;
				}		
			}
		}
		while (true);
	}
}

void CDiagnostics::OnDiagStop() 
{
//	char	buff[10];

//	this->KillTimer (DIAG_UPDATE_TIMER_ID);
//	sprintf (buff, " - ");
//	SetDlgItemText (IDC_GATE_STAT, buff);
	m_DiagOn = false;
}

void CDiagnostics::DiagTimerProc (HWND hwnd, UINT msg, UINT id, DWORD curtime)
{
}

void CDiagnostics::OnTimer(UINT nIDEvent) 
{
	char	result = (char) 0xff;
	char	buff[10];

//	result = (_inp (STATUS_REGISTER) & 0xf8);
	result = (Inp32 (stat_reg) & 0xf8);					//NT, XP, Win2K compatibility


	sprintf (buff, "%d", result);
	SetDlgItemText (IDC_GATE_STAT, buff);

	if (!(result & 0x08))	// Lane 1 - pin 15 (Error)
	{
		pulsecount1++;
		sprintf (buff, "%d", pulsecount1);
		SetDlgItemText (IDC_1_STAT, "1");
		SetDlgItemText (IDC_1_PC, buff);
	}
	else
	{
		SetDlgItemText (IDC_1_STAT, "0");
		pulsecount1 = 0;
	}

	if (!(result & 0x10))	// Lane 2 - pin 13 (Selected)
	{
		pulsecount2++;
		sprintf (buff, "%d", pulsecount2);
		SetDlgItemText (IDC_2_STAT, "1");
		SetDlgItemText (IDC_2_PC, buff);
	}
	else
	{
		SetDlgItemText (IDC_2_STAT, "0");
		pulsecount2 = 0;
	}

	if (!(result & 0x20))	// Lane 3 - pin 12 (No Paper)
	{
		pulsecount3++;
		sprintf (buff, "%d", pulsecount3);
		SetDlgItemText (IDC_3_STAT, "1");
		SetDlgItemText (IDC_3_PC, buff);
	}
	else
	{
		SetDlgItemText (IDC_3_STAT, "0");
		pulsecount3 = 0;
	}

	if (!(result & 0x40))	// Lane 4 - pin 10 (Ack)
	{
		pulsecount4++;
		sprintf (buff, "%d", pulsecount4);
		SetDlgItemText (IDC_4_STAT, "1");
		SetDlgItemText (IDC_4_PC, buff);
	}
	else 
	{
		SetDlgItemText (IDC_4_STAT, "0");
		pulsecount4 = 0;
	}
}


BOOL CDiagnostics::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
	
	if (theApp != NULL)
	{
		CWnd*			pWin = NULL;

		pWin = GetDlgItem (IDC_P10_LABEL);
		if (pWin)
			pWin->SetWindowText (theApp->GetPin10());
		pWin = GetDlgItem (IDC_P11_LABEL);
		if (pWin)
			pWin->SetWindowText (theApp->GetPin11());
		pWin = GetDlgItem (IDC_P12_LABEL);
		if (pWin)
			pWin->SetWindowText (theApp->GetPin12());
		pWin = GetDlgItem (IDC_P13_LABEL);
		if (pWin)
			pWin->SetWindowText (theApp->GetPin13());
		pWin = GetDlgItem (IDC_P15_LABEL);
		if (pWin)
			pWin->SetWindowText (theApp->GetPin15());
		pWin = GetDlgItem (IDC_PORT_STRING);
		if (pWin)
			pWin->SetWindowText (theApp->GetPort());

		pWin = GetDlgItem (IDC_PORT_ADDRESS);
		if (pWin) 
		{
/*
 *   LPT1 = 0x0378 or 0x03BC
 *   LPT2 = 0x0278 or 0x0378
 *   LPT3 = 0x0278
 */
			if (theApp->GetPort () == "LPT1")
				pWin->SetWindowText ("0x03BC");

			if (theApp->GetPort () == "LPT2")
				pWin->SetWindowText ("0x0378");

			if (theApp->GetPort () == "LPT3")
				pWin->SetWindowText ("0x0278");
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
