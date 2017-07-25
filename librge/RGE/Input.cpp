#include "Input.h"

Engine::CKeyboard::CKeyboard()
{
#ifdef RGE_WIN
	m_InputHandle = GetStdHandle(STD_INPUT_HANDLE);
#endif
}

void Engine::CKeyboard::OnUpdate()
{
#ifdef RGE_WIN
	DWORD cc;
	INPUT_RECORD InputRecord;

	GetNumberOfConsoleInputEvents(m_InputHandle, &m_NumEvents);

	if (m_NumEvents != 0)
	{
		ReadConsoleInput(m_InputHandle, &InputRecord, 1, &cc);

		if (InputRecord.EventType == KEY_EVENT && ((KEY_EVENT_RECORD&)InputRecord.Event).bKeyDown)
		{
			KEY_EVENT_RECORD KeyRecord = (KEY_EVENT_RECORD&)InputRecord.Event;
			CKey Key;
			Key.m_Ascii = KeyRecord.uChar.AsciiChar;
			Key.m_KeyCode = KeyRecord.wVirtualKeyCode;
			Key.m_bState = true;
			m_BufferedEvents[Key.m_KeyCode] = Key;
		}
	}
#endif
}

void Engine::CKeyboard::ClearBufferedEnvents()
{
	for (int i = 0; i < 256; i++)
		m_PrevBufferedEvents[i] = m_BufferedEvents[i];

	for (int i = 0; i < 256; i++)
		m_BufferedEvents[i].m_bState = false;
}

bool Engine::CKeyboard::IsKeyPressed(int KeyCode)
{
	return m_BufferedEvents[KeyCode].m_bState;
}

bool Engine::CKeyboard::IsKeyReleased(int KeyCode)
{
	return !m_BufferedEvents[KeyCode].m_bState && m_PrevBufferedEvents[KeyCode].m_bState;
}