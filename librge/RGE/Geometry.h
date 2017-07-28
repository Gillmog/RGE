#ifndef GEOMETRY_H
#define GEOMETRY_H

#pragma once

#include "Core.h"

using namespace std;

namespace Engine
{
	class CColor
	{
	public:

		int m_Red;
		int m_Green;
		int m_Blue;
		int m_Alpha;

		int m_BGRed;
		int m_BGGreen;
		int m_BGBlue;
		int m_BGAlpha;

		CColor();

		CColor(int Red, int Green, int Blue, int Alpha = 1, int BGRed = 0, int BGGreen = 0, int BGBlue = 0, int BGAlpha = 0);

		CColor(const CColor &Other);

		CColor &operator=(const CColor &Other)
		{
			m_Red = Other.m_Red;
			m_Green = Other.m_Green;
			m_Blue = Other.m_Blue;
			m_Alpha = Other.m_Alpha;

			m_BGRed = Other.m_BGRed;
			m_BGGreen = Other.m_BGGreen;
			m_BGBlue = Other.m_BGBlue;
			m_BGAlpha = Other.m_BGAlpha;

			return *this;
		}
                
#ifdef RGE_WIN
		WORD GetColor() const;
#elif defined(RGE_UNIX)
             string GetColor() const;   
#endif
	};

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
