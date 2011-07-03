// Driver.h: interface for the CDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "Race.h"

#if !defined(AFX_DRIVER_H__C5CF6231_F355_11D6_B10F_005004983D52__INCLUDED_)
#define AFX_DRIVER_H__C5CF6231_F355_11D6_B10F_005004983D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDriver  
{
public:
	CString		m_CarNumber;
	CString		m_DriverName;
	CString		m_NickName;
	CString		m_Group;
	CString		m_NumName;
	bool		m_Active;
	DWORD		m_TotalTime;
	int			m_TotalRaces;

	CRace	   *m_pFirstRace;
	CRace	   *m_pLastRace;

	CDriver	   *m_pNext;
	CDriver	   *m_pPrev;

public:
	CDriver();
	virtual ~CDriver();

	SetCarNumber (CString CarNumber);
	SetDriverName (CString DriverName);
	SetNickName (CString NickName);
	SetGroup (CString Group);
	SetNumName (CString NumName);

};

#endif // !defined(AFX_DRIVER_H__C5CF6231_F355_11D6_B10F_005004983D52__INCLUDED_)
