#include "Sprite.h"

void Engine::CSprite::CSpriteFrame::Serialize(CArchive &Archive)
{
	if (Archive.IsStoring())
	{
		Archive << m_Width;
		Archive << m_Height;

		int BufferSize = (int)m_Buffer.size();
		Archive << BufferSize;

		for (int n = 0; n < BufferSize; n++)
		{
			const CSpriteBuffer &Buffer = m_Buffer[n];
			Archive << Buffer.m_Valid;
			if (!Buffer.m_Valid)
				continue;
			Archive << Buffer.m_Char;
			Archive << Buffer.m_Color.m_Red;
			Archive << Buffer.m_Color.m_Green;
			Archive << Buffer.m_Color.m_Blue;
			Archive << Buffer.m_Color.m_Alpha;
			Archive << Buffer.m_Color.m_BGRed;
			Archive << Buffer.m_Color.m_BGGreen;
			Archive << Buffer.m_Color.m_BGBlue;
			Archive << Buffer.m_Color.m_BGAlpha;

			Archive << Buffer.m_Position.m_X;
			Archive << Buffer.m_Position.m_Y;
		}
	}
	else
	{
		Archive >> m_Width;
		Archive >> m_Height;

		int BufferSize = 0;
		Archive >> BufferSize;

		for (int n = 0; n < BufferSize; n++)
		{
			CSpriteBuffer Buffer;
			Archive >> Buffer.m_Valid;
			if (!Buffer.m_Valid)
			{
				m_Buffer.push_back(Buffer);
				continue;
			}

			Archive >> Buffer.m_Char;
			Archive >> Buffer.m_Color.m_Red;
			Archive >> Buffer.m_Color.m_Green;
			Archive >> Buffer.m_Color.m_Blue;
			Archive >> Buffer.m_Color.m_Alpha;
			Archive >> Buffer.m_Color.m_BGRed;
			Archive >> Buffer.m_Color.m_BGGreen;
			Archive >> Buffer.m_Color.m_BGBlue;
			Archive >> Buffer.m_Color.m_BGAlpha;

			Archive >> Buffer.m_Position.m_X;
			Archive >> Buffer.m_Position.m_Y;

			m_Buffer.push_back(Buffer);
		}
	}
}

void Engine::CSprite::CSpriteFrame::SetBuffer(const CSpriteBuffer &Buffer)
{
	CPoint Position = Buffer.m_Position;

	if (Position.m_X >= m_Width || Position.m_Y >= m_Height)
		return;

	if (Position.m_X < 0 || Position.m_Y < 0)
		return;

	m_Buffer[Position.m_X * m_Height + Position.m_Y] = Buffer;
}

void Engine::CSprite::CSpriteFrame::SetBuffer(const CPoint &Position, const CColor &Color, const string &Char)
{
	if (Position.m_X >= m_Width || Position.m_Y >= m_Height)
		return;

	if (Position.m_X < 0 || Position.m_Y < 0)
		return;

	CSpriteBuffer Buffer;
	Buffer.m_Position = Position;
	Buffer.m_Color = Color;
	Buffer.m_Char = Char;
	Buffer.m_Valid = true;
	m_Buffer[Position.m_X * m_Height + Position.m_Y] = Buffer;
}

Engine::CSpriteManager::~CSpriteManager()
{
	Free();
}

void Engine::CSpriteManager::Free()
{
	for (int nSprite = 0; nSprite < m_Sprites.size(); nSprite++)
	{
		CSprite *pSprite = m_Sprites[nSprite];

		delete pSprite;
	}

	m_Sprites.clear();
}

Engine::CSprite * Engine::CSpriteManager::FindSprite(const string &Name)
{
	for (int nSprite = 0; nSprite < m_Sprites.size(); nSprite++)
	{
		CSprite *pSprite = m_Sprites[nSprite];

		if (pSprite->GetName() == Name)
			return pSprite;
	}

	return NULL;
}

int Engine::CSpriteManager::GetNumSprites()
{
	return (int)m_Sprites.size();
}

Engine::CSprite * Engine::CSpriteManager::GetSprite(int Index)
{
	assert(Index >= 0);
	assert(Index < m_Sprites.size());

	return m_Sprites[Index];
}

bool Engine::CSpriteManager::RemoveSprite(const string &Name)
{
	for (int nSprite = 0; nSprite < m_Sprites.size(); nSprite++)
	{
		CSprite *pSprite = m_Sprites[nSprite];

		if (pSprite->GetName() == Name)
		{
			delete pSprite;
			m_Sprites.erase(m_Sprites.begin() + nSprite);
			return true;
		}
	}

	return false;
}

bool Engine::CSpriteManager::AddSprite(CSprite *pSprite)
{
	assert(pSprite);

	if (!FindSprite(pSprite->GetName()))
	{
		m_Sprites.push_back(pSprite);
		return true;
	}

	return false;
}

Engine::CSprite * Engine::CSpriteManager::CreateSprite(const string &Name, int Width, int Height)
{
	if (FindSprite(Name))
		return NULL;

	if (Width == 0 && Height == 0)
		return NULL;

	if (Name.length() == 0)
		return NULL;

	CSprite *pSprite = new CSprite(Name, Width, Height);

	m_Sprites.push_back(pSprite);

	return pSprite;
}

Engine::CSpriteManager* Engine::CSpriteManager::m_pInstance = NULL;

Engine::CSpriteManager* Engine::CSpriteManager::GetSingleton()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSpriteManager();
	}

	return m_pInstance;
}

void Engine::CSpriteManager::Save(const string &FilePath)
{
	CArchive Archive(FilePath, false);

	Archive << GetNumSprites();

	for (int nSprite = 0; nSprite < GetNumSprites(); nSprite++)
	{
		CSprite *pSprite = GetSprite(nSprite);

		pSprite->Serialize(Archive);
	}

	Archive.Close();
}

void Engine::CSpriteManager::Load(const string &FilePath)
{
	CArchive Archive(FilePath, true);

	if (!Archive.IsValid())
		return;

	int nSprites = 0;
	Archive >> nSprites;

	if (nSprites > 0)
		Free();

	for (int nSprite = 0; nSprite < nSprites; nSprite++)
	{
		CSprite *pSprite = new CSprite();

		pSprite->Serialize(Archive);

		m_Sprites.push_back(pSprite);
	}

	Archive.Close();
}

void Engine::CSpriteManager::RemoveSprite(int Index)
{
	assert(Index >= 0);
	assert(Index < m_Sprites.size());

	CSprite *pSprite = m_Sprites[Index];
	m_Sprites.erase(m_Sprites.begin() + Index);
}

Engine::CSprite::CSprite(const string &Name, int Width, int Height) : m_Name(Name)
{
	CSpriteFrame Frame;
	Frame.SetWidth(Width);
	Frame.SetHeight(Height);
	Frame.InitBuffer();
	m_Frames.push_back(Frame);
}

Engine::CSprite::CSpriteFrame& Engine::CSprite::GetSpriteFrame()
{
	assert(GetFrame() >= 0);
	assert(GetFrame() < m_Frames.size());

	return m_Frames[GetFrame()];
}

void Engine::CSprite::Serialize(CArchive &Archive)
{
	if (Archive.IsStoring())
	{
		Archive << m_Name;
		Archive << m_Position.m_X;
		Archive << m_Position.m_Y;

		int FramesSize = (int)m_Frames.size();
		Archive << FramesSize;
		for (int n = 0; n < FramesSize; n++)
		{
			CSpriteFrame &Frame = m_Frames[n];

			Frame.Serialize(Archive);
		}
	}
	else
	{
		Archive >> m_Name;
		Archive >> m_Position.m_X;
		Archive >> m_Position.m_Y;

		int FramesSize = 0;
		Archive >> FramesSize;

		for (int n = 0; n < FramesSize; n++)
		{
			CSpriteFrame Frame;
			Frame.Serialize(Archive);
			m_Frames.push_back(Frame);
		}
	}
}

void Engine::CSprite::AddFrame(int Width, int Height)
{
	CSpriteFrame Frame;
	Frame.SetWidth(Width);
	Frame.SetHeight(Height);
	Frame.InitBuffer();
	m_Frames.push_back(Frame);
}

void Engine::CSprite::RemoveFrame(int nFrame)
{
	assert(nFrame >= 0);
	assert(nFrame < m_Frames.size());

	if (m_Frames.size() > 1)
		m_Frames.erase(m_Frames.begin() + nFrame);

	m_Frame = (int)m_Frames.size() - 1;
}

void Engine::CSprite::Update(double Time, double TimeDelta)
{
	if (IsPlay())
	{
		int Frame = GetFrame();
		m_FrameTime += 1.0f * (float)TimeDelta;
		Frame = int(m_FrameTime / 15.0);

		if (Frame >= GetNumFrames())
		{
			m_FrameTime = 0.0;
			m_Frame = 0;
		}
		else
		{
			SetFrame(Frame);
		}
	}
}
