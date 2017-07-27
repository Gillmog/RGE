#include "Graphics.h"

Engine::CGraphics::CGraphics(CPoint WindowSize)
{
#ifdef RGE_WIN
	m_WindowHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	m_WindowSize = WindowSize;

	m_FontSize.m_X = 8;
	m_FontSize.m_Y = 16;

	InitBuffer();

	Restore();
}

Engine::CGraphics::~CGraphics()
{
	
}

void Engine::CGraphics::Terminate()
{
#ifdef RGE_WIN
	CloseHandle(m_WindowHandle);
#endif
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
	for (auto &Buffer : m_Buffer)
	{
		if (Buffer.second.m_bForce)
		{
			Buffer.second.m_bForce = false;
			continue;
		}

		Buffer.second.m_bFlush = false;
	}

	SetCursorPosition(CPoint());
}

void Engine::CGraphics::ClearColor()
{
#ifdef RGE_WIN
	CONSOLE_SCREEN_BUFFER_INFO Screen;
	DWORD Written;

	GetConsoleScreenBufferInfo(m_WindowHandle, &Screen);
	FillConsoleOutputCharacterA(
		m_WindowHandle, ' ', Screen.dwSize.X * Screen.dwSize.Y, {0, 0}, &Written
	);
	FillConsoleOutputAttribute(
		m_WindowHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		Screen.dwSize.X * Screen.dwSize.Y, { 0, 0 }, &Written
	);
#endif

	SetCursorPosition(CPoint());
}

void Engine::CGraphics::Restore()
{
#ifdef RGE_WIN
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
#elif defined(RGE_UNIX)
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	
	int CurrentWindowSizeY = w.ws_row;
	int CurrentWindowSizeX = w.ws_col;

	if (CurrentWindowSizeX != m_WindowSize.m_X - 1 || CurrentWindowSizeY != m_WindowSize.m_Y - 1)
	{
		cout << "\e[8;" << m_WindowSize.m_Y << ";" << m_WindowSize.m_X << "t";
	}
#endif
}

void Engine::CGraphics::ShowCursor(bool bShow)
{
#ifdef RGE_WIN
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(m_WindowHandle, &CursorInfo);
	CursorInfo.bVisible = bShow;
	SetConsoleCursorInfo(m_WindowHandle, &CursorInfo);
#elif defined(RGE_UNIX)
	if (bShow)
	{
		system("setterm -cursor on");
	}
	else
	{
		system("setterm -cursor off");
	}
#endif
}

void Engine::CGraphics::SetCursorPosition(CPoint Position)
{
#if defined(RGE_WIN)
	COORD TopLeft = { (SHORT)Position.m_X, (SHORT)Position.m_Y };
	SetConsoleCursorPosition(m_WindowHandle, TopLeft);
#elif defined(RGE_UNIX)
	printf("\033[%d;%dH", Position.m_Y + 1, Position.m_X + 1);
#endif
}

void Engine::CGraphics::SetColor(WORD Color)
{
#ifdef RGE_WIN
	SetConsoleTextAttribute(m_WindowHandle, Color);
#endif
}

void Engine::CGraphics::Draw(const string &Value, CPoint Position, WORD ColorAttr, bool bForce/* = false*/)
{
	if (Value.length() > 1)
	{
		const char * Char = Value.c_str();

		for (int i = 0; i < Value.length(); i++)
		{
			string CharString;
			CharString += Char[i];
			Draw(CharString, Position, ColorAttr, bForce);
			Position.m_X++;
		}

		return;
	}

	CPoint NewPosition = Position + m_ViewPosition;
	//Clip
	if (NewPosition.m_X < 0 || NewPosition.m_Y < 0 || NewPosition.m_X >= m_WindowSize.m_X || NewPosition.m_Y >= m_WindowSize.m_Y)
	{
		m_Buffer[make_pair(Position.m_X, Position.m_Y)] = CBuffer();
		return;
	}

	CBuffer Buffer = m_Buffer[make_pair(Position.m_X, Position.m_Y)];
	Buffer.m_Position = NewPosition;

	Buffer.m_bFlush = true;

	Buffer.m_Value = Value;
	Buffer.m_ColorAttr = ColorAttr;

	string CurrentValue = m_Buffer[make_pair(Position.m_X, Position.m_Y)].m_Value;

	if (CurrentValue != Value && Buffer.m_bDirty == false)
		Buffer.m_bDirty = true;

	Buffer.m_bForce = bForce;
	
	m_Buffer[make_pair(Position.m_X, Position.m_Y)] = Buffer;
	
}

void Engine::CGraphics::Flush()
{
	for (auto &Buffer : m_Buffer)
	{
		bool bClear = false;

		if (Buffer.second.m_bFlush == false && Buffer.second.m_Value.length() != 0)
		{
			Buffer.second.m_Value = "";
			bClear = true;
		}

		if (Buffer.second.m_bForce)
		{
			bClear = false;
			Buffer.second.m_bDirty = true;
		}

	    if (!Buffer.second.m_bDirty && !bClear)
			continue;

		SetCursorPosition(Buffer.second.m_Position);

		if (bClear)
		{
			SetColor(15);
			cout << ' ';
		}
		else
		{
			SetColor(Buffer.second.m_ColorAttr);
			cout << Buffer.second.m_Value.c_str();
		}

		Buffer.second.m_bDirty = false;
	}

	SetCursorPosition(CPoint());
	cout.flush();
}

void * Engine::CGraphics::GetWindowHandle() const
{
	return m_WindowHandle;
}
