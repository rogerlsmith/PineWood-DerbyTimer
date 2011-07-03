// ****************************************************************************
// ****************************************************************************
//
//                                    CGCClock
//                           Developed By: George Chastain
//                                    11/10/99
//
//                                   Version 1.0
//
// Derived from the CGCColorStatic class, this class provides the ability to
// quickly include a clock in your GUI/MMI.  Since it is publicly derived from
// the CGCColorStatic class, all the CGCColorStatic class' methods are 
// available for controlling the look of the clock.
//
// ****************************************************************************
// ****************************************************************************

#if !defined(__CGCClock__)
#define __CGCClock__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GCColorStatic.h"


class CGCClock : public CGCColorStatic
{
public:

	
	// Start() - Must be called to initialize and start the clock.
	//           Returns FALSE if a failure occurred starting the clock.
	//
	BOOL Start();

	BOOL Stop();

	void CGCClock::Reset();


	CGCClock();
	~CGCClock();
protected:
	afx_msg void OnTimer(UINT nIDEvent);
	DECLARE_MESSAGE_MAP()
public:

	enum {CLOCK_UPDATE_TIMER_ID = 2};	// We use id of 2 because 1 is reserved for CGCColorStatic.

	CString m_FormattedTime;		// Time formatted for display.

	void FormatTime();				// Used to format the time for display.

	DWORD	m_StartTime;
	DWORD	m_TimeNow;
	DWORD	m_ElapsedTime;
};

#endif