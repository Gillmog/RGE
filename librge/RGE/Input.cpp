#include "Input.h"
#include "Application.h"
#include "Graphics.h"

Engine::CKeyboard::CKeyboard(CApplication *pApp)
{
	AddMappedKey('A', K_A);
	AddMappedKey('B', K_B);
	AddMappedKey('C', K_C);
	AddMappedKey('D', K_D);
	AddMappedKey('E', K_E);
	AddMappedKey('F', K_F);
	AddMappedKey('G', K_G);
	AddMappedKey('H', K_H);
	AddMappedKey('I', K_I);
	AddMappedKey('J', K_J);
	AddMappedKey('K', K_K);
	AddMappedKey('L', K_L);
	AddMappedKey('M', K_M);
	AddMappedKey('N', K_N);
	AddMappedKey('O', K_O);
	AddMappedKey('P', K_P);
	AddMappedKey('Q', K_Q);
	AddMappedKey('R', K_R);
	AddMappedKey('S', K_S);
	AddMappedKey('T', K_T);
	AddMappedKey('U', K_U);
	AddMappedKey('V', K_V);
	AddMappedKey('W', K_W);
	AddMappedKey('X', K_X);
	AddMappedKey('Y', K_Y);
	AddMappedKey('Z', K_Z);
	AddMappedKey('0', K_0);
	AddMappedKey('1', K_1);
	AddMappedKey('2', K_2);
	AddMappedKey('3', K_3);
	AddMappedKey('4', K_4);
	AddMappedKey('5', K_5);
	AddMappedKey('6', K_6);
	AddMappedKey('8', K_8);
	AddMappedKey('9', K_9);
#if defined(RGE_WIN)
	m_InputHandle = GetStdHandle(STD_INPUT_HANDLE);
	AddMappedKey(VK_DOWN, K_DOWN);
	AddMappedKey(VK_UP, K_UP);
	AddMappedKey(VK_LEFT, K_LEFT);
	AddMappedKey(VK_RIGHT, K_RIGHT);
	AddMappedKey(VK_F1, K_F1);
	AddMappedKey(VK_F2, K_F2);
	AddMappedKey(VK_F3, K_F3);
	AddMappedKey(VK_F4, K_F4);
	AddMappedKey(VK_F5, K_F5);
	AddMappedKey(VK_F6, K_F6);
	AddMappedKey(VK_F7, K_F7);
	AddMappedKey(VK_F8, K_F8);
	AddMappedKey(VK_F9, K_F9);
	AddMappedKey(VK_F10, K_F10);
	AddMappedKey(VK_F11, K_F11);
	AddMappedKey(VK_F12, K_F12);
	AddMappedKey(VK_DELETE, K_DELETE);
	AddMappedKey(VK_ESCAPE, K_ESC);
#elif defined(RGE_UNIX)
	WINDOW* win = static_cast<WINDOW*>(pApp->GetGraphics()->GetWindowHandle());
	keypad(win, TRUE);
	meta(win, TRUE);
	m_InputHandle = win;
	AddMappedKey(258, K_DOWN);
	AddMappedKey(259, K_UP);
	AddMappedKey(260, K_LEFT);
	AddMappedKey(261, K_RIGHT);
	AddMappedKey(265, K_F1);
	AddMappedKey(266, K_F2);
	AddMappedKey(267, K_F3);
	AddMappedKey(268, K_F4);
	AddMappedKey(269, K_F5);
	AddMappedKey(270, K_F6);
	AddMappedKey(271, K_F7);
	AddMappedKey(272, K_F8);
	AddMappedKey(273, K_F9);
	AddMappedKey(274, K_F10);
	AddMappedKey(275, K_F11);
	AddMappedKey(276, K_F12);
	AddMappedKey(330, K_DELETE);
#endif
}

void Engine::CKeyboard::OnUpdate()
{
#if defined(RGE_WIN)
	DWORD cc;
	INPUT_RECORD InputRecord;

	GetNumberOfConsoleInputEvents(m_InputHandle, &m_NumEvents);

	if (m_NumEvents != 0)
	{
		ReadConsoleInput(m_InputHandle, &InputRecord, 1, &cc);

		if (InputRecord.EventType == KEY_EVENT && ((KEY_EVENT_RECORD&)InputRecord.Event).bKeyDown)
		{
			KEY_EVENT_RECORD KeyRecord = (KEY_EVENT_RECORD&)InputRecord.Event;

			int MappedKey = ToMappedKey(KeyRecord.wVirtualKeyCode);

			if (MappedKey)
			{
				CKey Key;
				Key.m_Ascii = KeyRecord.uChar.AsciiChar;
				Key.m_KeyCode = MappedKey;
				Key.m_bState = true;
				m_BufferedEvents[Key.m_KeyCode] = Key;
			}
		}
	}
#elif defined(RGE_UNIX)
	WINDOW* win = static_cast<WINDOW*>(m_InputHandle);
	int ch = wgetch(win);

	if (ch != ERR)
	{
		int MappedKey = ToMappedKey(ch);

		if (MappedKey != -1)
		{
			CKey Key;
			Key.m_Ascii = (char)ch;
			Key.m_KeyCode = MappedKey;
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
