#include "GameApplication.h"

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

CGameApplication::CGameApplication(const Engine::CPoint &WindowSize) : CApplication(WindowSize)
{
	m_PlayerPosition = Engine::CPoint(16, 16);
	m_ScrollPosition = Engine::CPoint(4, 0);
}


CGameApplication::~CGameApplication()
{
}

void CGameApplication::OnUpdate(double Time, double TimeDelta)
{
	CApplication::OnUpdate(Time, TimeDelta);
	ostringstream TimeString;
	TimeString << Time;
	ostringstream TimeDeltaString;
	TimeDeltaString << TimeDelta;
	m_TimerValue = "Time: " + TimeString.str() + " TimeDelta: " + TimeDeltaString.str();

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_KEY_A))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X - 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
		{
			m_PlayerPosition.m_X--;
			m_ScrollPosition.m_X++;
		}
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_KEY_D))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X + 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
		{
			m_PlayerPosition.m_X++;
			m_ScrollPosition.m_X--;
		}
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_KEY_W))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y - 1), m_Map, m_MapWidth, m_MapHeight))
		{
			m_PlayerPosition.m_Y--;
			m_ScrollPosition.m_Y++;
		}
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_KEY_S))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y + 1), m_Map, m_MapWidth, m_MapHeight))
		{
			m_PlayerPosition.m_Y++;
			m_ScrollPosition.m_Y--;
		}
	}
        
        if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_F12))
	{
            GetGraphics()->Terminate();
        }
}

void CGameApplication::OnRender()
{
	CApplication::OnRender();
	GetGraphics()->SetViewPosition(m_ScrollPosition);
	DrawMap(m_Map, m_MapWidth, m_MapHeight);
	GetGraphics()->Draw("@", m_PlayerPosition, Engine::CColor(0, 1, 0, 1));
	//Draw UI
	GetGraphics()->SetViewPosition(Engine::CPoint(0, 0));
	GetGraphics()->Draw("UI Draw", Engine::CPoint(20, 0), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 0));
	GetGraphics()->Draw(m_TimerValue, Engine::CPoint(20, 1), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
}
