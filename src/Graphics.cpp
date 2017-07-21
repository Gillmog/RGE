#include "stdafx.h"
#include "Graphics.h"

Engine::CGraphics::CGraphics(CPoint WindowSize)
{
	m_WindowHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	m_WindowSize = WindowSize;

	Restore();
}

Engine::CGraphics::~CGraphics()
{

}

void Engine::CGraphics::Clear()
{
	COORD TopLeft = { 0, 0 };

	SetConsoleCursorPosition(m_WindowHandle, TopLeft);
}

void Engine::CGraphics::ClearColor()
{
	COORD TopLeft = { 0, 0 };

	CONSOLE_SCREEN_BUFFER_INFO Screen;
	DWORD Written;

	GetConsoleScreenBufferInfo(m_WindowHandle, &Screen);
	FillConsoleOutputCharacterA(
		m_WindowHandle, ' ', Screen.dwSize.X * Screen.dwSize.Y, TopLeft, &Written
	);
	FillConsoleOutputAttribute(
		m_WindowHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		Screen.dwSize.X * Screen.dwSize.Y, TopLeft, &Written
	);
}

void Engine::CGraphics::Restore()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(m_WindowHandle, &csbi);

	int CurrentWindowSizeX = csbi.srWindow.Right - csbi.srWindow.Left;
	int CurrentWindowSizeY = csbi.srWindow.Bottom - csbi.srWindow.Top;

	if (CurrentWindowSizeX != m_WindowSize.m_X - 1 || CurrentWindowSizeY != m_WindowSize.m_Y - 1)
	{
		COORD WindowSize = { (SHORT)m_WindowSize.m_X, (SHORT)m_WindowSize.m_Y };
		::SetConsoleScreenBufferSize(m_WindowHandle, WindowSize);
		SMALL_RECT rc = { 0, 0, (SHORT)m_WindowSize.m_X - 1, (SHORT)m_WindowSize.m_Y - 1 };
		::SetConsoleWindowInfo(m_WindowHandle, TRUE, &rc);
		ClearColor();
		Clear();
	}
}

void Engine::CGraphics::ShowCursor(bool bShow)
{
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(m_WindowHandle, &CursorInfo);
	CursorInfo.bVisible = bShow;
	SetConsoleCursorInfo(m_WindowHandle, &CursorInfo);
}

void Engine::CGraphics::Draw(const string &Value, CPoint Position, WORD ColorAttr)
{
	CBuffer Buffer;
	Buffer.m_Value = Value;
	Buffer.m_Position = Position;
	Buffer.m_ColorAttr = ColorAttr;
	m_Buffer.push_back(Buffer);
}

void Engine::CGraphics::Flush()
{
	for (auto &Buffer : m_Buffer)
	{
		COORD Position = { (SHORT)Buffer.m_Position.m_X, (SHORT)Buffer.m_Position.m_Y };
		SetConsoleCursorPosition(m_WindowHandle, Position);
		SetConsoleTextAttribute(m_WindowHandle, Buffer.m_ColorAttr);
		cout << Buffer.m_Value.c_str();
	}

	COORD TopLeft = { 0, 0 };
	SetConsoleCursorPosition(m_WindowHandle, TopLeft);

	m_Buffer.clear();
}

void * Engine::CGraphics::GetWindowHandle() const
{
	return m_WindowHandle;
}
