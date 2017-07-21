#include "stdafx.h"
#include "GameApplication.h"

void CGameApplication::DrawMap(const vector<int> &Chunk, int ChunkWidth, int ChunkHeight)
{
	assert(ChunkWidth * ChunkHeight == Chunk.size());

	for (int nCellY = 0; nCellY < ChunkHeight; nCellY++)
	{
		for (int nCellX = 0; nCellX < ChunkWidth; nCellX++)
		{
			int CellValue = Chunk[nCellY + nCellX * ChunkWidth];

			if (CellValue > 0)
			{
				GetGraphics()->Draw("#", Engine::CPoint(nCellX, nCellY), 7 | FOREGROUND_INTENSITY);
			}
			else
			{
				GetGraphics()->Draw(".", Engine::CPoint(nCellX, nCellY), 8 | FOREGROUND_INTENSITY);
			}
		}
	}

	GetGraphics()->Draw("@", m_PlayerPosition, 10 | FOREGROUND_INTENSITY);
}

bool CGameApplication::IsCanMove(const Engine::CPoint &Position, const vector<int> &Chunk, int ChunkWidth, int ChunkHeight)
{
	assert(ChunkWidth * ChunkHeight == Chunk.size());

	int CellValue = Chunk[Position.m_Y + Position.m_X * ChunkWidth];

	if (CellValue == 0)
		return true;

	return false;
}

CGameApplication::CGameApplication(const Engine::CPoint &WindowSize) : CApplication(WindowSize)
{
	m_PlayerPosition = Engine::CPoint(1, 1);
}


CGameApplication::~CGameApplication()
{
}

void CGameApplication::OnUpdate()
{
	if (GetKeyBoard()->IsKeyReleased(Engine::CKeyboard::K_KEY_A))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X - 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
			m_PlayerPosition.m_X--;
	}

	if (GetKeyBoard()->IsKeyReleased(Engine::CKeyboard::K_KEY_D))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X + 1, m_PlayerPosition.m_Y), m_Map, m_MapWidth, m_MapHeight))
			m_PlayerPosition.m_X++;
	}

	if (GetKeyBoard()->IsKeyReleased(Engine::CKeyboard::K_KEY_W))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y - 1), m_Map, m_MapWidth, m_MapHeight))
			m_PlayerPosition.m_Y--;
	}

	if (GetKeyBoard()->IsKeyReleased(Engine::CKeyboard::K_KEY_S))
	{
		if (IsCanMove(Engine::CPoint(m_PlayerPosition.m_X, m_PlayerPosition.m_Y + 1), m_Map, m_MapWidth, m_MapHeight))
			m_PlayerPosition.m_Y++;
	}

	DrawMap(m_Map, m_MapWidth, m_MapHeight);
	GetGraphics()->Flush();
}
