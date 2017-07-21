#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#pragma once

#include "CoreBase.h"
#include "Application.h"

class CGameApplication : public Engine::CApplication
{
	vector<int> m_Map = { 1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,
	};

	int m_MapWidth = 8;
	int m_MapHeight = 8;

	Engine::CPoint m_PlayerPosition;

	void DrawMap(const vector<int> &Chunk, int ChunkWidth, int ChunkHeight);

	bool IsCanMove(const Engine::CPoint &Position, const vector<int> &Chunk, int ChunkWidth, int ChunkHeight);

public:

	CGameApplication(const Engine::CPoint &WindowSize);
	~CGameApplication();

	void OnUpdate() override;
};

#endif GAME_APPLICATION_H

