#include "stdafx.h"
#include "Graphics.h"

Engine::CGraphics::CGraphics(CPoint WindowSize)
{
	m_WindowHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	m_WindowSize = WindowSize;

	m_FontSize.m_X = 8;
	m_FontSize.m_Y = 16;

	InitBuffer();

	Restore();
}

Engine::CGraphics::~CGraphics()
{

}

void Engine::CGraphics::InitBuffer()
{
	m_Buffer.clear();

	for (int y = 0; y < m_WindowSize.m_Y; y++)
	{
		for (int x = 0; x < m_WindowSize.m_X; x++)
		{
			CBuffer Buffer;
			Buffer.m_Value = "";
			Buffer.m_Position = CPoint(x, y);
			Buffer.m_ColorAttr = 15;

			m_Buffer.insert(make_pair(make_pair(x, y), Buffer));
		}
	}
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
		InitBuffer();
	}

	//Restore font size

	CONSOLE_FONT_INFO GETFONT;

	HWND  StdHandle = (HWND)GetStdHandle(STD_OUTPUT_HANDLE);

	GetCurrentConsoleFont(StdHandle, FALSE, &GETFONT);

	COORD Fontsize = GetConsoleFontSize(StdHandle, GETFONT.nFont);

	if (m_FontSize.m_X != Fontsize.X || m_FontSize.m_Y != Fontsize.Y)
	{
		CONSOLE_FONT_INFOEX consoleFont;
		memset(&consoleFont, 0, sizeof(consoleFont));
		consoleFont.cbSize = sizeof(consoleFont);
		GetCurrentConsoleFontEx(StdHandle, FALSE, &consoleFont);
		//Sets new font sizes
		consoleFont.dwFontSize.X = m_FontSize.m_X;
		consoleFont.dwFontSize.Y = m_FontSize.m_Y;

		if (!SetCurrentConsoleFontEx(StdHandle, true, &consoleFont))
		{
			assert(0);
		}
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

	//Clip
	if (Position.m_X < 0)
		return;
	if (Position.m_Y < 0)
		return;
	if (Position.m_X >= m_WindowSize.m_X)
		return;
	if (Position.m_Y >= m_WindowSize.m_Y)
		return;

	string CurrentValue = m_Buffer[make_pair(Position.m_X, Position.m_Y)].m_Value;

	if (CurrentValue != Value)
		Buffer.m_bDirty = true;
	
	m_Buffer[make_pair(Position.m_X, Position.m_Y)] = Buffer;
}

void Engine::CGraphics::Flush()
{
	for (auto &Buffer : m_Buffer)
	{
		if (!Buffer.second.m_bDirty)
			continue;
		COORD Position = { (SHORT)Buffer.second.m_Position.m_X, (SHORT)Buffer.second.m_Position.m_Y };
		SetConsoleCursorPosition(m_WindowHandle, Position);
		SetConsoleTextAttribute(m_WindowHandle, Buffer.second.m_ColorAttr);
		cout << Buffer.second.m_Value.c_str();
		Buffer.second.m_bDirty = false;
	}

	COORD TopLeft = { 0, 0 };
	SetConsoleCursorPosition(m_WindowHandle, TopLeft);
}

void * Engine::CGraphics::GetWindowHandle() const
{
	return m_WindowHandle;
}
