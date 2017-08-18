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


std::shared_ptr<Engine::ÑControl> Engine::CControlsManager::PickControlFromPoint(CPoint Position)
{
	for (int nControl = 0; nControl < GetNumControls(); nControl++)
	{
		shared_ptr<ÑControl> pControl = GetControl(nControl);

		shared_ptr<ÑControl> pPickedControl = pControl->PickControlFromPoint(Position);

		if (pPickedControl)
		{
			return pPickedControl;
		}
	}

	return nullptr;
}

void Engine::CControlsManager::ProcessMouseMessage(const CControlMouseMessage &Message)
{
	return;
	shared_ptr<ÑControl> pControl = nullptr;

	if (Message.m_Type != CControlKeyboardMessage::EMPTY)
	{
		pControl = PickControlFromPoint(Message.m_Position);
	}

	switch (Message.m_Type)
	{
	case CControlMouseMessage::ON_MOUSE_LBUTTON_DOWN:
		if (pControl)
		{
			pControl->SetHasFocus(true);
			pControl->OnMouseDown();
			m_pInputControl = pControl;
		}
		break;
	case CControlMouseMessage::ON_MOUSE_LBUTTON_UP:
		if (pControl && m_pInputControl == pControl)
		{
			pControl->OnMouseUp();
		}
		break;
	case CControlMouseMessage::ON_MOUSE_MOVE:
		if (pControl)
		{
			pControl->SetHasFocus(true);
		}
		break;
	case CControlMouseMessage::ON_MOUSE_RBUTTON_DOWN:
		if (pControl)
		{
			pControl->OnMouseRightDown();
			m_pInputControl = pControl;
		}
		break;
	case CControlMouseMessage::ON_MOUSE_RBUTTON_UP:
		if (pControl && m_pInputControl == pControl)
		{
			pControl->OnMouseRightUp();
		}
		break;
	case CControlMouseMessage::ON_MOUSE_WHEEL:
		if (pControl && m_pCurrentControl == pControl)
		{
			pControl->OnMouseWheel(Message.m_WheelDelta);
		}
		break;
	}

	if (pControl)
	{
		pControl->ProcessMouseMessage(Message);
	}

	if (m_pCurrentControl && m_pCurrentControl->GetHasFocus() && m_pCurrentControl != pControl)
	{
		m_pCurrentControl->SetHasFocus(false);
	}

	if (m_pInputControl != m_pCurrentControl)
		m_pInputControl = nullptr;

	m_pCurrentControl = pControl;
}

void Engine::CControlsManager::ProcessKeyboardMessage(const CControlKeyboardMessage &Message)
{
	shared_ptr<ÑControl> pControl = nullptr;

	if (Message.m_Type != CControlKeyboardMessage::EMPTY)
		pControl = GetFocusedControl();

	switch (Message.m_Type)
	{
	case CControlKeyboardMessage::ON_KEYBOARD_KEY_DOWN:
	{
		
	}
		break;
	case CControlKeyboardMessage::ON_KEYBOARD_KEY_UP:
	{
		if (Message.m_KeyCode == CKeyboard::K_UP)
		{
			pControl = GetPrevControl();

			if (pControl)
				pControl->SetHasFocus(true);
	
		}
		else
		if (Message.m_KeyCode == CKeyboard::K_DOWN)
		{
			pControl = GetNextControl();

			if (pControl)
				pControl->SetHasFocus(true);
		}
	}
		break;
	}

	if (pControl)
	{
		pControl->ProcessKeyboardMessage(Message);
	}

	if (m_pCurrentControl && m_pCurrentControl->GetHasFocus() && m_pCurrentControl != pControl)
	{
		m_pCurrentControl->SetHasFocus(false);
	}

	m_pCurrentControl = pControl;
}

void Engine::CControlsManager::ProcessMessage(CApplication *pApplication)
{
	/*
	pApplication->GetMouse()->SetLock(false);
	pApplication->GetKeyboard()->SetLock(false);

	CControlMessage Message;

	if (pApplication->GetMouse()->IsPressed(0))
	{
		Message.m_Type = CControlMessage::ON_MOUSE_LBUTTON_DOWN;
	}

	if (pApplication->GetMouse()->IsReleased(0))
	{
		Message.m_Type = CControlMessage::ON_MOUSE_LBUTTON_UP;
	}

	if (pApplication->GetKeyboard()->IsKeyPressed)
	{
		Message.m_Type = CControlMessage::ON_MOUSE_LBUTTON_DOWN;
	}

	if (pApplication->GetMouse()->IsReleased(0))
	{
		Message.m_Type = CControlMessage::ON_MOUSE_LBUTTON_UP;
	}

		for (int nControl = 0; nControl < GetNumControls(); nControl++)
		{
			shared_ptr<ÑControl> pControl = GetControl(nControl);

			pControl->SetHasFocus(false);

			shared_ptr<ÑControl> pPickedControl = pControl->PickControlFromPoint(pApplication->GetMouse()->GetPosition());

			if (pPickedControl)
			{
				pApplication->GetMouse()->SetLock(true);
				pApplication->GetKeyboard()->SetLock(true);
				pPickedControl->SetHasFocus(true);
				break;
			}
		}
	}
	*/
}

void Engine::ÑControl::ProcessMouseMessage(const CControlMouseMessage &Message)
{

}

void Engine::ÑControl::ProcessKeyboardMessage(const CControlKeyboardMessage &Message)
{

}
