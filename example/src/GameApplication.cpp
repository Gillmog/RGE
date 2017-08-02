#include "GameApplication.h"
#include "RGE/Archive.h"

void CGameApplication::DrawMap(const vector<int> &Chunk, int ChunkWidth, int ChunkHeight)
{
	assert(ChunkWidth * ChunkHeight == Chunk.size());

	for (int nCellY = 0; nCellY < ChunkHeight; nCellY++)
	{
		for (int nCellX = 0; nCellX < ChunkWidth; nCellX++)
		{
			int CellValue = Chunk[nCellX + nCellY * ChunkHeight];

			if (CellValue > 0)
			{
				GetGraphics()->Draw("#", Engine::CPoint(nCellX, nCellY), Engine::CColor(1, 1, 1));
			}
			else
			{
				GetGraphics()->Draw(".", Engine::CPoint(nCellX, nCellY), Engine::CColor(1, 1, 1));
			}
		}
	}
}

bool CGameApplication::IsCanMove(const Engine::CPoint &Position, const vector<int> &Chunk, int ChunkWidth, int ChunkHeight)
{
	assert(ChunkWidth * ChunkHeight == Chunk.size());

	int CellValue = Chunk[Position.m_X + Position.m_Y * ChunkHeight];

	if (CellValue == 0)
		return true;

	return false;
}

void CGameApplication::UpdateMenu()
{
	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_UP))
	{
		if (m_MenuState > 0)
			m_MenuState--;
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_DOWN))
	{
		if (m_MenuState < STATE_MENU_EXIT_GAME)
			m_MenuState++;
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_BACKSPACE))
	{
		switch (m_MenuState)
		{
		case STATE_MENU_NEW_GAME:
			m_GameState = STATE_GAME;
			break;
		case STATE_MENU_EXIT_GAME:
			Terminate();
			break;
		}
	}
}

void CGameApplication::RenderMenu()
{
	GetGraphics()->SetViewPosition(Engine::CPoint(0, 0));
	Engine::CPoint HalfWinSize = GetGraphics()->GetWindowSize() / 2;

	Engine::CColor NewGameColor = m_MenuTextColor;
	Engine::CColor ExitGameColor = m_MenuTextColor;

	switch (m_MenuState)
	{
	case STATE_MENU_NEW_GAME:
		NewGameColor = m_MenuSelectedColor;
		break;
	case STATE_MENU_EXIT_GAME:
		ExitGameColor = m_MenuSelectedColor;
		break;
	}

	GetGraphics()->Draw("New Game", Engine::CPoint(HalfWinSize.m_X - 4, HalfWinSize.m_Y), NewGameColor);
	GetGraphics()->Draw("Exit", Engine::CPoint(HalfWinSize.m_X - 2, HalfWinSize.m_Y + 1), ExitGameColor);
}

CGameApplication::CGameApplication(const Engine::CPoint &WindowSize, const string &WindowTitle) : CApplication(WindowSize, WindowTitle)
{
	m_PlayerPosition = Engine::CPoint(16, 16);
	m_ScrollPosition = Engine::CPoint(4, 0);

	m_GameState = STATE_MENU;
	m_MenuState = STATE_MENU_NEW_GAME;

	m_MenuSelectedColor = Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1);
	m_MenuTextColor = Engine::CColor(1, 0, 1, 1);
}


CGameApplication::~CGameApplication()
{
}

void CGameApplication::OnUpdate(double Time, double TimeDelta)
{
	CApplication::OnUpdate(Time, TimeDelta);

	if (m_GameState == STATE_MENU)
	{
		UpdateMenu();
	}
	else
	if (m_GameState == STATE_GAME)
	{
		ostringstream TimeString;
		TimeString << Time;
		ostringstream TimeDeltaString;
		TimeDeltaString << TimeDelta;
		m_TimerValue = "Time: " + TimeString.str() + " TimeDelta: " + TimeDeltaString.str();

		if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_LEFT))
		{
			if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X - 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
			{
				m_PlayerPosition.m_X--;
				m_ScrollPosition.m_X++;
			}
		}

		if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_RIGHT))
		{
			if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X + 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
			{
				m_PlayerPosition.m_X++;
				m_ScrollPosition.m_X--;
			}
		}

		if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_UP))
		{
			if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y - 1), m_Map, m_MapWidth, m_MapHeight))
			{
				m_PlayerPosition.m_Y--;
				m_ScrollPosition.m_Y++;
			}
		}

		if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_DOWN))
		{
			if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y + 1), m_Map, m_MapWidth, m_MapHeight))
			{
				m_PlayerPosition.m_Y++;
				m_ScrollPosition.m_Y--;
			}
		}

		if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_F12))
		{
			Terminate();
		}
	}
}

void CGameApplication::OnRender()
{
	CApplication::OnRender();
	if (m_GameState == STATE_MENU)
	{
		RenderMenu();
	}
	else
	if (m_GameState == STATE_GAME)
	{
		GetGraphics()->SetViewPosition(m_ScrollPosition);
		DrawMap(m_Map, m_MapWidth, m_MapHeight);
		GetGraphics()->Draw("@", m_PlayerPosition, Engine::CColor(0, 1, 0, 1));
		//Draw UI
		GetGraphics()->SetViewPosition(Engine::CPoint(0, 0));
		GetGraphics()->Draw("UI Draw", Engine::CPoint(20, 0), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
		GetGraphics()->Draw(m_TimerValue, Engine::CPoint(20, 1), Engine::CColor(1, 0, 1, 0, 0, 1, 1, 1));
	}
}
