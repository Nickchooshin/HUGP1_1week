#pragma once

#include "Singleton.h"

class CData : public Singleton<CData>
{
public :
	float m_fModulus ;
	float m_fMass ;
	float m_fMoveAcc, m_fSpinAcc ;

public :
	CData() ;
	~CData() ;

	void Init() ;
private :
	bool LoadData() ;
	bool CreateDataFile() ;
} ;

#define g_Data CData::GetInstance()