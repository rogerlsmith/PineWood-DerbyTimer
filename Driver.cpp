// Driver.cpp: implementation of the CDriver class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "derby1.h"
#include "Driver.h"
#include "Race.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDriver::CDriver()
{
	m_pFirstRace = (CRace*) new (CRace);	// create the initial dummy race header

	m_pNext			= NULL;
	m_pPrev			= NULL;
	m_DriverName	= "";
	m_CarNumber		= "";
	m_Group			= "";
	m_NickName		= "";
	m_NumName		= "";

	m_Active = true;
	m_TotalRaces = 0;
	m_TotalTime = 0;
}

CDriver::~CDriver()
{

}

//////////////////////////////////////////////////////////////////////
// Get/Set 
//////////////////////////////////////////////////////////////////////

CDriver::SetCarNumber (CString CarNumber)
{
	m_CarNumber = CarNumber;
}

CDriver::SetDriverName (CString DriverName)
{
	m_DriverName = DriverName;
}

CDriver::SetNickName (CString NickName)
{
	m_NickName = NickName;
}

CDriver::SetGroup (CString Group)
{
	m_Group = Group;
}

CDriver::SetNumName (CString NumName)
{
	m_NumName = NumName;
}
