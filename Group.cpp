// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "derby1.h"
#include "Group.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGroup::CGroup()
{
	m_pNext			= NULL;
	m_pPrev			= NULL;
	m_pHeatSched	= NULL;
	m_Round			= 1;
	m_GroupIndex	= 0;
}

CGroup::~CGroup()
{
	m_pNext = NULL;
	m_pPrev = NULL;
	m_pHeatSched = NULL;
}
