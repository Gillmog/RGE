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

void CGameApplication::UpdateMenu()
{
	Engine::CPoint HalfWinSize = GetGraphics()->GetWindowSize() / 2;
	Engine::CRect NewGameRect(HalfWinSize.m_X - 4, HalfWinSize.m_Y, HalfWinSize.m_X - 4 + 8, HalfWinSize.m_Y + 1);
	Engine::CRect EditorRect(HalfWinSize.m_X - 2, HalfWinSize.m_Y + 1, HalfWinSize.m_X - 2 + 5, HalfWinSize.m_Y + 2);
	Engine::CRect ExitGameRect(HalfWinSize.m_X - 2, HalfWinSize.m_Y + 2, HalfWinSize.m_X - 2 + 5, HalfWinSize.m_Y + 3);
	
	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_UP))
	{
		if (m_MenuState == -1)
			m_MenuState = 0;

		if (m_MenuState > 0)
			m_MenuState--;
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_DOWN))
	{
		if (m_MenuState == -1)
			m_MenuState = 0;

		if (m_MenuState < STATE_MENU_EXIT_GAME)
			m_MenuState++;
	}

	if (GetMouse()->IsPressed(0))
	{
		if (NewGameRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
			m_MenuState = 0;
		else
		if (EditorRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
			m_MenuState = 1;
		else
		if (ExitGameRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
			m_MenuState = 2;
	}

	if (GetMouse()->IsReleased(0))
	{
		if (NewGameRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
		{
			m_GameState = STATE_GAME;
			GetGraphics()->Init();
			return;
		}
		else
		if (EditorRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
		{
			m_GameState = STATE_EDITOR;
			GetGraphics()->Init();
			return;
		}
		else
		if (ExitGameRect.IsInside(GetMouse()->GetPosition().m_X, GetMouse()->GetPosition().m_Y))
			Terminate();
		else
			m_MenuState = -1;
	}

	if (GetKeyboard()->IsKeyPressed(Engine::CKeyboard::K_BACKSPACE))
	{
		switch (m_MenuState)
		{
		case STATE_MENU_NEW_GAME:
			m_GameState = STATE_GAME;
			GetGraphics()->Init();
			break;
		case STATE_MENU_EDITOR:
			m_GameState = STATE_EDITOR;
			GetGraphics()->Init();
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
	Engine::CColor EditorColor = m_MenuTextColor;
	Engine::CColor ExitGameColor = m_MenuTextColor;

	switch (m_MenuState)
	{
	case STATE_MENU_NEW_GAME:
		NewGameColor = m_MenuSelectedColor;
		break;
	case STATE_MENU_EDITOR:
		EditorColor = m_MenuSelectedColor;
		break;
	case STATE_MENU_EXIT_GAME:
		ExitGameColor = m_MenuSelectedColor;
		break;
	}

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			int CellValue = m_ExampleLogo[i + j * 14];

			if (CellValue > 0)
			{
				GetGraphics()->Draw("#", Engine::CPoint(i + HalfWinSize.m_X - 7, j + 3), Engine::CColor(1, 1, 1));
			}
		}
	}

	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 14; i++)
		{
			int CellValue = m_ExampleLogoFrame1[i + j * 14];

			if (m_Frame == 1)
				CellValue = m_ExampleLogoFrame2[i + j * 14];

			if (m_Frame == 2)
				CellValue = m_ExampleLogoFrame3[i + j * 14];

			if (CellValue > 0)
			{
				GetGraphics()->Draw("#", Engine::CPoint(i + HalfWinSize.m_X - 7, j + 3), Engine::CColor(1, 0, 0));
			}
		}
	}

	GetGraphics()->Draw("New Game", Engine::CPoint(HalfWinSize.m_X - 4, HalfWinSize.m_Y), NewGameColor);
	GetGraphics()->Draw("Sprite Editor", Engine::CPoint(HalfWinSize.m_X - 6, HalfWinSize.m_Y + 1), EditorColor);
	GetGraphics()->Draw("Exit", Engine::CPoint(HalfWinSize.m_X - 2, HalfWinSize.m_Y + 2), ExitGameColor);
}

void CGameApplication::UpdateEditor(double Time, double TimeDelta)
{
	if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_F12))
	{
		m_GameState = STATE_MENU;
		GetGraphics()->Init();
		return;
	}

	if (!m_pCurrentEditorSprite && GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_S))
	{
		m_pCurrentEditorSprite = Engine::CSpriteManager::GetSingleton()->CreateSprite("Test", 20, 10);
	}

	if (m_pCurrentEditorSprite && !m_pCurrentEditorSprite->IsPlay())
	{
		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_F))
		{
			if (m_pCurrentEditorSprite)
			{
				m_pCurrentEditorSprite->AddFrame(20, 10);
				m_pCurrentEditorSprite->SetFrame(m_pCurrentEditorSprite->GetFrame() + 1);
			}
		}

		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_D))
		{
			if (m_pCurrentEditorSprite)
			{
				if (m_pCurrentEditorSprite->GetNumFrames() > 0)
					m_pCurrentEditorSprite->RemoveFrame(m_pCurrentEditorSprite->GetFrame());
			}
		}

		//save
		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_F2))
		{
			string Path = GetPath() + "/" + "Sprites.pak";
			Engine::CSpriteManager::GetSingleton()->Save(Path);
		}

		//load
		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_F3))
		{
			string Path = GetPath() + "/" + "Sprites.pak";
			Engine::CSpriteManager::GetSingleton()->Load(Path);

			if (Engine::CSpriteManager::GetSingleton()->GetNumSprites() > 0)
				m_pCurrentEditorSprite = Engine::CSpriteManager::GetSingleton()->GetSprite(0);
			else
				m_pCurrentEditorSprite = NULL;
		}

		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_LEFT))
		{
			if (m_pCurrentEditorSprite)
			{
				if (m_pCurrentEditorSprite->GetFrame() - 1 >= 0)
					m_pCurrentEditorSprite->SetFrame(m_pCurrentEditorSprite->GetFrame() - 1);
			}
		}

		if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_RIGHT))
		{
			if (m_pCurrentEditorSprite)
			{
				if (m_pCurrentEditorSprite->GetFrame() + 1 < m_pCurrentEditorSprite->GetNumFrames())
					m_pCurrentEditorSprite->SetFrame(m_pCurrentEditorSprite->GetFrame() + 1);
			}
		}
	}

	if (GetKeyboard()->IsKeyReleased(Engine::CKeyboard::K_P))
	{
		m_pCurrentEditorSprite->SetPlay(m_pCurrentEditorSprite->IsPlay() ? false : true);
	}

	if (m_pCurrentEditorSprite)
	{
		m_pCurrentEditorSprite->Update(Time, TimeDelta);

		if (GetMouse()->IsPressed(0))
		{
			Engine::CSprite::CSpriteFrame &SpriteBuffer = m_pCurrentEditorSprite->GetSpriteFrame();

			Engine::CPoint MousePosition = GetMouse()->GetPosition();
			SpriteBuffer.SetBuffer(MousePosition, Engine::CColor(1, 1, 1), "#");
		}

		if (GetMouse()->IsPressed(1))
		{
			Engine::CSprite::CSpriteFrame &SpriteBuffer = m_pCurrentEditorSprite->GetSpriteFrame();
			Engine::CSprite::CSpriteFrame::CSpriteBuffer Buffer;
			Buffer.m_Position = GetMouse()->GetPosition();
			SpriteBuffer.SetBuffer(Buffer);
		}
	}
}

void CGameApplication::RenderEditor()
{
	int Row = 0;
	int Col = 0;
	if (m_pCurrentEditorSprite)
	{
		Col = m_pCurrentEditorSprite->GetPosition().m_X + m_pCurrentEditorSprite->GetSpriteFrame().GetWidth() + 1;

		//draw grid
		const Engine::CSprite::CSpriteFrame &SpriteBuffer = m_pCurrentEditorSprite->GetSpriteFrame();

		for (int j = 0; j < SpriteBuffer.GetHeight(); j++)
		{
			for (int i = 0; i < SpriteBuffer.GetWidth(); i++)
			{
				GetGraphics()->Draw(".", Engine::CPoint(i, j) + m_pCurrentEditorSprite->GetPosition(), Engine::CColor(1, 1, 1));
			}
		}

		GetGraphics()->Draw(m_pCurrentEditorSprite);

		GetGraphics()->Draw("Current Frame            " + to_string(m_pCurrentEditorSprite->GetFrame()), Engine::CPoint(Col, Row), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
		Row++;
	}

	GetGraphics()->Draw("Keys:                     ", Engine::CPoint(Col, Row), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));

	if (!m_pCurrentEditorSprite)
	{
		GetGraphics()->Draw("S: Create sprite          ", Engine::CPoint(Col, Row + 1), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
	}

	if (m_pCurrentEditorSprite)
	{
		if (!m_pCurrentEditorSprite->IsPlay())
		{
			GetGraphics()->Draw("F:     Add frame          ", Engine::CPoint(Col, Row + 1), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("D:     Delete frame       ", Engine::CPoint(Col, Row + 2), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("Left:  Set prev key       ", Engine::CPoint(Col, Row + 3), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("Right: Set next key       ", Engine::CPoint(Col, Row + 4), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("P:     Play/Stop animation", Engine::CPoint(Col, Row + 5), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("MLB:   Add point          ", Engine::CPoint(Col, Row + 6), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
			GetGraphics()->Draw("MRB:   Remove point       ", Engine::CPoint(Col, Row + 7), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
		}
		else
			GetGraphics()->Draw("P:     Play/Stop animation", Engine::CPoint(Col, Row + 1), Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1));
	}
}

CGameApplication::CGameApplication(const Engine::CPoint &WindowSize, const string &WindowTitle) : CApplication(WindowSize, WindowTitle)
{
	m_PlayerPosition = Engine::CPoint(16, 16);
	m_ScrollPosition = Engine::CPoint(4, 0);

	m_GameState = STATE_MENU;
	m_MenuState = STATE_MENU_NEW_GAME;

	m_MenuSelectedColor = Engine::CColor(1, 0, 1, 1, 0, 0, 1, 1);
	m_MenuTextColor = Engine::CColor(1, 0, 1, 1);

	m_pDialog = Engine::CControlsManager::GetSingleton()->Create<Engine::CDialog>(nullptr, 1001, Engine::CRect(0, 0, 20, 10));
	m_pDialog->Move(Engine::CPoint(20, 10));
	m_pDialog->SetBackgroundColor(Engine::CColor(0, 0, 0, 0, 0, 0, 1, 1));

	shared_ptr<Engine::CButton> pButton = Engine::CControlsManager::GetSingleton()->Create<Engine::CButton>(m_pDialog, 1002, Engine::CRect(0, 0, 5, 1));
	pButton->Move(Engine::CPoint(1, 1));
	pButton->SetBackgroundColor(Engine::CColor(0, 0, 0, 0, 0, 0, 0, 1));
	pButton->SetText("Button");
	pButton->SetTextColor(Engine::CColor(1, 1, 1, 1, 1, 1, 0, 1));

	shared_ptr<Engine::CLabel> pLabel = Engine::CControlsManager::GetSingleton()->Create<Engine::CLabel>(m_pDialog, 1003, Engine::CRect(0, 0, 5, 1));
	pLabel->Move(Engine::CPoint(1, 3));
	pLabel->SetText("Label");
	pLabel->SetTextColor(Engine::CColor(1, 1, 1, 1));

	m_pDialog->SetVisible(false);
}


CGameApplication::~CGameApplication()
{
}

void CGameApplication::OnUpdate(double Time, double TimeDelta)
{
	m_FrameTime += 1.0f * TimeDelta;
	m_Frame = m_FrameTime / 15.0;

	if (m_Frame > 2)
	{
		m_FrameTime = 0.0;
		m_Frame = 0;
	}

	CApplication::OnUpdate(Time, TimeDelta);

	if (m_GameState == STATE_EDITOR)
	{
		UpdateEditor(Time, TimeDelta);
	}
	else
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
			m_GameState = STATE_MENU;
			GetGraphics()->Init();
		}
	}
}

void CGameApplication::OnRender()
{
	CApplication::OnRender();

	if (m_GameState == STATE_EDITOR)
	{
		RenderEditor();
	}
	else
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
