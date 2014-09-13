#include "Data.h"
#include "LoadManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

CData::CData() : m_fModulus(0.0f),
				 m_fMass(0.0f),
				 m_fMoveAcc(0.0f), m_fSpinAcc(0.0f)
{
}
CData::~CData()
{
}

void CData::Init()
{
	if(!LoadData())
	{
		CreateDataFile() ;
		LoadData() ;
	}
}

bool CData::LoadData()
{
	if( !g_LoadManager->OpenDat("Resource/Game.ini") )
		return false ;

	char item[100] ;
	char temp[100] ;

	while(g_LoadManager->GetItem(item))
	{
		int len = strlen(item) ;

		if(len==7 && strcmp(item, "MODULUS")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fModulus = (float)strtod(temp, NULL) ;
		}
		else if(len==4 && strcmp(item, "MASS")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fMass = (float)strtod(temp, NULL) ;
		}
		else if(len==17 && strcmp(item, "MOVE_ACCELERATION")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fMoveAcc = (float)strtod(temp, NULL) ;
		}
		else if(len==17 && strcmp(item, "SPIN_ACCELERATION")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fSpinAcc = (float)strtod(temp, NULL) ;
		}
	}

	g_LoadManager->CloseDat() ;

	return true ;
}

bool CData::CreateDataFile()
{
	FILE *pFile ;

	pFile = fopen("Resource/Game.ini", "w") ;
	if(pFile==NULL)
		return false ;

	fprintf(pFile, "# modulus of elasticity\n") ;
	fprintf(pFile, "<modulus>\n") ;
	fprintf(pFile, "0.5\n") ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# gyrating mass\n") ;
	fprintf(pFile, "<mass>\n") ;
	fprintf(pFile, "1.0\n") ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# player move/spin acceleration\n") ;
	fprintf(pFile, "<move_acceleration>\n") ;
	fprintf(pFile, "0.1\n") ;
	fprintf(pFile, "\n") ;
	fprintf(pFile, "<spin_acceleration>\n") ;
	fprintf(pFile, "0.1\n") ;

	fclose(pFile) ;

	return true ;
}