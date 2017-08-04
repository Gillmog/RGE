#include "Archive.h"

Engine::CArchive::CArchive(const string &FileName, bool bIn)
{
	Close();

	if (bIn)
	{
		m_pFile = fopen(FileName.c_str(), "rb");
		m_bStoring = false;
	}
	else
	{
		m_pFile = fopen(FileName.c_str(), "wb");
		m_bStoring = true;
	}
}

Engine::CArchive::~CArchive()
{
	Close();
}

void Engine::CArchive::Close()
{
	if (m_pFile)
	{
		fclose(m_pFile);
		m_pFile = NULL;
	}
}
