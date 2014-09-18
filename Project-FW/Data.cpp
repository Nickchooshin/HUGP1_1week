#include "Data.h"
#include "LoadManager.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

CData::CData() : m_fModulus(0.5f),
				 m_fMass(1.0f),
				 m_fMoveAcc(0.1f), m_fSpinAcc(0.1f),
				 m_bScore(false), m_bTime(false),
				 m_nMaxScore(10000),
				 m_fTimeLimit(60.0f),
				 m_fBoxForceMax(10.0f),
				 m_bBoxCollision(false)
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
		else if(len==5 && strcmp(item, "SCORE")==0)
		{
			int b ;
			g_LoadManager->GetValue(b) ;
			m_bScore = b ;
		}
		else if(len==9 && strcmp(item, "MAX_SCORE")==0)
		{
			g_LoadManager->GetValue(m_nMaxScore) ;
		}
		else if(len==4 && strcmp(item, "TIME")==0)
		{
			int b ;
			g_LoadManager->GetValue(b) ;
			m_bTime = b ;
		}
		else if(len==10 && strcmp(item, "TIME_LIMIT")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fTimeLimit = (float)strtod(temp, NULL) ;
		}
		else if(len==13 && strcmp(item, "BOX_FORCE_MAX")==0)
		{
			g_LoadManager->GetString(temp) ;
			m_fBoxForceMax = (float)strtod(temp, NULL) ;
		}
		else if(len==13 && strcmp(item, "BOX_COLLISION")==0)
		{
			int b ;
			g_LoadManager->GetValue(b) ;
			m_bBoxCollision = b ;
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
	fprintf(pFile, "%f\n", m_fModulus) ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# gyrating mass\n") ;
	fprintf(pFile, "<mass>\n") ;
	fprintf(pFile, "%f\n", m_fMass) ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# player move/spin acceleration\n") ;
	fprintf(pFile, "<move_acceleration>\n") ;
	fprintf(pFile, "%f\n", m_fMoveAcc) ;
	fprintf(pFile, "\n") ;
	fprintf(pFile, "<spin_acceleration>\n") ;
	fprintf(pFile, "%f\n", m_fSpinAcc) ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# scouring mode\n") ;
	fprintf(pFile, "<score>\n") ;
	fprintf(pFile, "%d\n", m_bScore) ;
	fprintf(pFile, "\n") ;
	fprintf(pFile, "<max_score>\n") ;
	fprintf(pFile, "%d\n", m_nMaxScore) ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# time limit mode\n") ;
	fprintf(pFile, "<time>\n") ;
	fprintf(pFile, "%d\n", m_bTime) ;
	fprintf(pFile, "\n") ;
	fprintf(pFile, "<time_limit>\n") ;
	fprintf(pFile, "%f\n", m_fTimeLimit) ;

	//
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# Box Speed Force Max\n") ;
	fprintf(pFile, "<box_force_max>\n") ;
	fprintf(pFile, "%f\n", m_fBoxForceMax) ;
	fprintf(pFile, "\n") ;

	fprintf(pFile, "# Box Collision Mode\n") ;
	fprintf(pFile, "<box_collision>\n") ;
	fprintf(pFile, "%d\n", m_bBoxCollision) ;

	fclose(pFile) ;

	return true ;
}