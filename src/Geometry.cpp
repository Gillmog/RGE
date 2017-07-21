#include "stdafx.h"
#include "Geometry.h"

Engine::CPoint::CPoint() : m_X(0), m_Y(0)
{

}

Engine::CPoint::CPoint(int X, int Y) : m_X(X), m_Y(Y)
{

}

Engine::CPoint::CPoint(const CPoint &Other) : m_X(Other.m_X), m_Y(Other.m_Y)
{

}
