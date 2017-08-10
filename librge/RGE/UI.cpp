#include "UI.h"

Engine::CControlsManager* Engine::CControlsManager::m_pInstance = NULL;

Engine::CControlsManager* Engine::CControlsManager::GetSingleton()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CControlsManager();
	}

	return m_pInstance;
}