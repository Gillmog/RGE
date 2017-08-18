#include "Application.h"

Engine::CApplication::CApplication(CPoint WindowSize, const string &WindowTitle)
{
	m_pGraphics = make_shared<CGraphics>(WindowSize);
	m_pGraphics->ShowCursor(false);
	m_pInputEvents = make_shared<CEvents>(this);
	m_pKeyboard = make_shared<CKeyboard>(this);
	m_pMouse = make_shared<CMouse>(this);
	m_pGraphics->SetWindowTitle(WindowTitle);
}

Engine::CApplication::~CApplication()
{

}

void Engine::CApplication::Terminate()
{
	m_pKeyboard.reset();
	m_pMouse.reset();
	m_pInputEvents.reset();
	m_pGraphics.reset();
}

void Engine::CApplication::EventLoop(function<void()> &&Callback)
{
	CTimer Timer;
	Timer.Start();
	double TimeDelta = Timer.GetDuration();
	
	m_pGraphics->Init();
	
	while (true)
	{
		m_pGraphics->Restore();
		m_pGraphics->SetCursorPosition(CPoint(0, 0));

		m_pInputEvents->ReadEvents();
#if defined(RGE_WIN)
		
		for (int i = 0; i < m_pInputEvents->m_NumberOfEventsRead; i++)
		{
			m_pKeyboard->OnEvent(m_pInputEvents->m_InputRecord[i]);
			m_pMouse->OnEvent(m_pInputEvents->m_InputRecord[i]);
		}
#endif
		m_pKeyboard->SetLock(false);
		m_pMouse->SetLock(false);
		m_pKeyboard->OnUpdate(m_pInputEvents.get());
		m_pMouse->OnUpdate(m_pInputEvents.get());

		CControlsManager::GetSingleton()->ProcessMessage(this);

		Callback();
		OnUpdate(Timer.GetDurationInSeconds(), TimeDelta / Timer.GetDuration());
		OnRenderBegin();
		OnRender();
		OnRenderEnd();
		m_pKeyboard->ClearBufferedEnvents();
		m_pMouse->ClearBufferedEnvents();
		TimeDelta = Timer.GetDuration();
#if defined(RGE_WIN)
		Sleep(10);
#elif defined(RGE_UNIX)
		refresh();
		sleep(0.01);
#endif
	}
}

void Engine::CApplication::OnRenderBegin()
{
	GetGraphics()->Clear();
}

void Engine::CApplication::OnRender()
{

}

void Engine::CApplication::OnRenderEnd()
{
	CControlsManager::GetSingleton()->OnDraw(m_pGraphics);
	GetGraphics()->Flush();
}

std::string Engine::CApplication::GetPath()
{
#ifdef RGE_WIN

	char Path[MAX_PATH + 1];

	if (GetModuleFileNameA(NULL, Path, MAX_PATH))
	{
		if (PathRemoveFileSpecA(Path))
		{
			return Path;
		}
	}
#elif RGE_UNIX
	char Path[1024];

	size_t Size = sizeof(Path);

	int n = readlink("/proc/self/exe", Path, Size - 1);
	if (n == -1)
		return "";

	Path[n] = '\0';

	return dirname(Path);
#endif
}

Engine::CTimer::CTimer() : m_Start(0), m_bStart(false)
{

}

void Engine::CTimer::Start()
{
	m_Start = clock();
	m_bStart = true;
}

void Engine::CTimer::Stop()
{
	m_bStart = false;
	m_Start = 0;
}

double Engine::CTimer::GetDurationInSeconds() const
{
	return (clock() - m_Start) / (double)CLOCKS_PER_SEC;
}

double Engine::CTimer::GetDuration() const
{
	return double(clock() - m_Start);
}

#if defined(RGE_WIN)

VOID Engine::CEvents::ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(m_InputHandle, m_fdwSaveOldMode);

	m_pApplication->Terminate();
}

#endif

Engine::CEvents::CEvents(CApplication *pApp) : m_pApplication(pApp)
{
#if defined(RGE_WIN)
	m_InputHandle = GetStdHandle(STD_INPUT_HANDLE);

	if (m_InputHandle == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(m_InputHandle, &m_fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	DWORD ConsoleMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(m_InputHandle, ConsoleMode))
		ErrorExit("SetConsoleMode");
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
#elif defined(RGE_UNIX)
	WINDOW* win = static_cast<WINDOW*>(pApp->GetGraphics()->GetWindowHandle());
	keypad(win, TRUE);
	meta(win, TRUE);
	m_InputHandle = win;
#endif
}

Engine::CEvents::~CEvents()
{
#if defined(RGE_WIN)
	SetConsoleMode(m_InputHandle, m_fdwSaveOldMode);
	m_InputHandle = NULL;
#endif
}

void Engine::CEvents::ReadEvents()
{
#if defined(RGE_WIN)
	m_NumberOfEventsRead = 0;
	m_NumEvents = 0;

	GetNumberOfConsoleInputEvents(m_InputHandle, &m_NumEvents);

	if (m_NumEvents != 0)
	{
		ReadConsoleInput(m_InputHandle, m_InputRecord, 128, &m_NumberOfEventsRead);
	}
#elif defined(RGE_UNIX)

#endif
}
