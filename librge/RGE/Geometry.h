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

		inline CColor &operator=(const CColor &Other)
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

		inline bool operator==(const CColor &Other)
		{
			return m_Red == Other.m_Red &&
				m_Green == Other.m_Green &&
				m_Blue == Other.m_Blue &&
				m_Alpha == Other.m_Alpha &&
				m_BGRed == Other.m_BGRed &&
				m_BGGreen == Other.m_BGGreen &&
				m_BGBlue == Other.m_BGBlue &&
				m_BGAlpha == Other.m_BGAlpha;
		}

		inline bool operator!=(const CColor &Other)
		{
			return m_Red != Other.m_Red ||
				m_Green != Other.m_Green ||
				m_Blue != Other.m_Blue ||
				m_Alpha != Other.m_Alpha ||
				m_BGRed != Other.m_BGRed ||
				m_BGGreen != Other.m_BGGreen ||
				m_BGBlue != Other.m_BGBlue ||
				m_BGAlpha != Other.m_BGAlpha;
		}

                
#ifdef RGE_WIN
		WORD GetColor() const;
#elif defined(RGE_UNIX)
             int GetColor() const;  
             int GetBGColor() const;   
#endif
	};

	class CRect
	{
	public:

		int m_Left = 0;
		int m_Top = 0;
		int m_Right = 0;
		int m_Bottom = 0;

		CRect();

		CRect(int Left, int Top, int Right, int Bottom);

		CRect(const CRect &Other);

		int GetWidth()
		{
			return abs(m_Right - m_Left);
		}

		int GetHeight()
		{
			return abs(m_Bottom - m_Top);
		}

		bool IsInside(int X, int Y)
		{
			if (X >= m_Left && X <= m_Right && Y >= m_Top && Y < m_Bottom)
				return true;

			return false;
		}

		void Move(int X, int Y)
		{
			m_Left += X;
			m_Right += X;
			m_Bottom += Y;
			m_Top += Y;
		}

	};

	class CPoint
	{
	public:

		int m_X;
		int m_Y;

		CPoint();

		CPoint(int X, int Y);

		CPoint(const CPoint &Other);

		inline CPoint &operator=(const CPoint &Other)
		{
			m_X = Other.m_X;
			m_Y = Other.m_Y;

			return *this;
		}

		inline bool operator==(const CPoint &Other)
		{
			return m_X == Other.m_X && m_Y == Other.m_Y;
		}

		inline bool operator!=(const CPoint &Other)
		{
			return m_X != Other.m_X || m_Y != Other.m_Y;
		}

		inline CPoint operator+(const CPoint &Other) const
		{
			return CPoint(m_X + Other.m_X, m_Y + Other.m_Y);
		}

		inline CPoint operator+(const int &Other) const
		{
			return CPoint(m_X + Other, m_Y + Other);
		}

		inline CPoint operator/(const CPoint &Other) const
		{
			return CPoint(m_X - Other.m_X, m_Y - Other.m_Y);
		}

		inline CPoint operator/(const int &Other) const
		{
			return CPoint(m_X / Other, m_Y / Other);
		}

		inline CPoint operator-(const int &Other) const
		{
			return CPoint(m_X - Other, m_Y - Other);
		}

		inline CPoint operator-(const CPoint &Other) const
		{
			return CPoint(m_X - Other.m_X, m_Y - Other.m_Y);
		}
	};
}


#endif // !GEOMETRY_H
