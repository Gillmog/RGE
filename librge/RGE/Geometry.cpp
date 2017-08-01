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

Engine::CColor::CColor() :
	m_Red(0),
	m_Green(0),
	m_Blue(0),
	m_Alpha(1),
	m_BGRed(0),
	m_BGGreen(0),
	m_BGBlue(0),
	m_BGAlpha(0)
{

}

Engine::CColor::CColor(const CColor &Other) :
	m_Red(Other.m_Red),
	m_Green(Other.m_Green),
	m_Blue(Other.m_Blue),
	m_Alpha(Other.m_Alpha),
	m_BGRed(Other.m_BGRed),
	m_BGGreen(Other.m_BGGreen),
	m_BGBlue(Other.m_BGBlue),
	m_BGAlpha(Other.m_BGAlpha)
{

}

Engine::CColor::CColor(int Red, int Green, int Blue, int Alpha /*= 1*/, int BGRed /*= 0*/, int BGGreen /*= 0*/, int BGBlue /*= 0*/, int BGAlpha /*= 0*/) :
	m_Red(Red),
	m_Green(Green),
	m_Blue(Blue),
	m_Alpha(1),
	m_BGRed(BGRed),
	m_BGGreen(BGGreen),
	m_BGBlue(BGBlue),
	m_BGAlpha(BGAlpha)
{

}
#ifdef RGE_WIN
WORD Engine::CColor::GetColor() const
{

	int Red = 0x0004;
	int Green = 0x0002;
	int Blue = 0x0001;
	int Alpha = 0x0008;

	int BGRed = 0x0040;
	int BGGreen = 0x0020;
	int BGBlue = 0x0010;
	int BGAlpha = 0x0080;

	return Red * m_Red | Green * m_Green | Blue * m_Blue
                | m_Alpha * Alpha | BGRed * m_BGRed | BGGreen * m_BGGreen 
                | BGBlue * m_BGBlue | BGAlpha * m_BGAlpha;
}
#elif defined(RGE_UNIX)
int Engine::CColor::GetBGColor() const
{
    int br = m_BGRed;
    int bg = m_BGGreen << 1;
    int bb = m_BGBlue << 2;
    return (br | bg | bb) * m_BGAlpha;
}

int Engine::CColor::GetColor() const
{
    int r = m_Red;
    int g = m_Green << 1;
    int b = m_Blue << 2;
    return (r | g | b) * m_Alpha;
}
#endif
