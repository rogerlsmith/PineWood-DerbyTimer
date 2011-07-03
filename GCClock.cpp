#include "stdafx.h"
#include "GCClock.h"
#include "RaceView.h"
#include "derby1.h"

CGCClock::CGCClock() : CGCColorStatic()
{
	//MessageBox ("Creating Clock", "clock", MB_OK);
}


CGCClock::~CGCClock()
{
}


BEGIN_MESSAGE_MAP(CGCClock, CGCColorStatic)
	ON_WM_TIMER()
END_MESSAGE_MAP()


void CGCClock::OnTimer(UINT nIDEvent) 
{
	// The CGCClock class is derived from the CGCColorStatic class.
	// Since the CGCColorStatic class provides the capability to flash the background
	// or text using timer events, we must distinguish between CGCColorStatic timer events
	// and the CGCClock's clock update timer event. Verify that the current timer
	// event is the CGCClock class' update event.  If it isn't route it on to the
	// parent class' OnTimer() event handler because that may be one of the 
	// CGCColorStatic class' flashing timer events.
	
//	if (nIDEvent != CLOCK_UPDATE_TIMER_ID)
//		CStatic::OnTimer(nIDEvent);
//		CGCColorStatic::OnTimer(nIDEvent);

	// Get the current time.
	m_TimeNow = GetTickCount ();

	// Format it for display.
	FormatTime();

	// Display the time.
	SetWindowText(m_FormattedTime);

	// check the finish line detector
	CDerby1App* theApp = (CDerby1App*)AfxGetApp ();
	CRaceView* pRView = (CRaceView*) ((CFrameWnd*) theApp->m_pMainWnd)->GetActiveView();

	// if bypass mode is on, don't check the finish switch.
	if (!theApp->GetBypassMode ())
		pRView->CheckFinishLine ();
}


void CGCClock::FormatTime()
{
	int		m_Seconds;
	int		m_Milliseconds;

	m_ElapsedTime = m_TimeNow - m_StartTime;
	m_Seconds = m_ElapsedTime / 1000;
	m_Milliseconds = m_ElapsedTime % 1000;

	m_FormattedTime.Format("%02d:%03d", m_Seconds, m_Milliseconds);
}


BOOL CGCClock::Start()
{
	m_StartTime = GetTickCount ();
	m_TimeNow = m_StartTime;

	FormatTime();
	SetWindowText(m_FormattedTime);

	UINT id = this->SetTimer(CLOCK_UPDATE_TIMER_ID,5,NULL);

	if (id == 0) 
		return FALSE;

	return TRUE;
}


BOOL CGCClock::Stop()
{
	return this->KillTimer (CLOCK_UPDATE_TIMER_ID);
}

void CGCClock::Reset()
{
	m_StartTime = 0;
	m_TimeNow = 0;
	FormatTime();
	SetWindowText(m_FormattedTime);
}
