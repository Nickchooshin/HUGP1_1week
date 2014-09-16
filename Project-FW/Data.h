#pragma once

#include "Singleton.h"

class CData : public Singleton<CData>
{
public :
	float m_fModulus ;
	float m_fMass ;
	float m_fMoveAcc, m_fSpinAcc ;

	bool m_bScore, m_bTime ;
	int m_nMaxScore ;
	float m_fTimeLimit ;

	float m_fBoxForceMax ;
	float m_bBoxCollision ;

public :
	CData() ;
	~CData() ;

	void Init() ;
private :
	bool LoadData() ;
	bool CreateDataFile() ;
} ;

#define g_Data CData::GetInstance()