#ifndef GEOMETRY_H
#define GEOMETRY_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CPoint
	{
	public:

		int m_X;
		int m_Y;

		CPoint();

		CPoint(int X, int Y);

		CPoint(const CPoint &Other);

		CPoint &operator=(const CPoint &Other)
		{
			m_X = Other.m_X;
			m_Y = Other.m_Y;

			return *this;
		}

		CPoint &operator+(const CPoint &Other)
		{
			m_X += Other.m_X;
			m_Y += Other.m_Y;

			return *this;
		}
	};
}


#endif // !GEOMETRY_H
