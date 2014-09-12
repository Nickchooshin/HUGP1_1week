#pragma once

typedef struct _Vector
{
	float x ;
	float y ;

	_Vector() : x(0.0f),
				y(0.0f)
	{}
	_Vector(float X, float Y) : x(X),
								y(Y)
	{}

	const _Vector operator+(_Vector vec)
	{
		_Vector temp ;
		temp.x = x + vec.x ;
		temp.y = y + vec.y ;

		return temp ;
	}
	const _Vector& operator=(_Vector vec)
	{
		x = vec.x ;
		y = vec.y ;

		return *this ;
	}
	const _Vector& operator+=(_Vector vec)
	{
		*this = *this + vec ;

		return *this ;
	}
} Vector ;