#pragma once

#include "Objects.h"

class CBox : public CObjects
{
public :
	CBox() ;
	virtual ~CBox() ;

	void Init() ;

	void Update() ;

	void SetScale(float fScale) ;
} ;