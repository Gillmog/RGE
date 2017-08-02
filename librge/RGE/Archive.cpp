#include "Archive.h"

Engine::CArchive::CArchive(const string &FileName, bool bIn)
{
	Close();

	if (bIn)
	{
		m_pFile = fopen(FileName.c_str(), "rb");
	}
	else
	{
		m_pFile = fopen(FileName.c_str(), "wb");
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
