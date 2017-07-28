#include "Input.h"

Engine::CKeyboard::CKeyboard()
{
#if defined(RGE_WIN)
	m_InputHandle = GetStdHandle(STD_INPUT_HANDLE);
#elif defined(RGE_UNIX)
        
#endif
}

#if defined(RGE_UNIX)
bool kbhit()
{
    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);
    return byteswaiting > 0;
}

int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}
#endif

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
			CKey Key;
			Key.m_Ascii = KeyRecord.uChar.AsciiChar;
			Key.m_KeyCode = KeyRecord.wVirtualKeyCode;
			Key.m_bState = true;
			m_BufferedEvents[Key.m_KeyCode] = Key;
		}
	}
#elif defined(RGE_UNIX)
        if (kbhit())
        {
            char ch = (char)getkey();
            if (ch == 0 || ch == 224)
            {
                ch = (char)getkey();
            }
            else
            {
                ch = toupper(ch);
            }
            ch = toupper(ch);
            int KeyCode = (int)ch;
            CKey Key;
            Key.m_Ascii = ch;
            Key.m_KeyCode = KeyCode;
            Key.m_bState = true;
            m_BufferedEvents[Key.m_KeyCode] = Key;
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
