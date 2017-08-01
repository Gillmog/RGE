#include "Application.h"

Engine::CApplication::CApplication(CPoint WindowSize)
{
	m_pGraphics = make_shared<CGraphics>(WindowSize);
	m_pGraphics->ShowCursor(false);
	m_pKeyboard = make_shared<CKeyboard>(this);
}

Engine::CApplication::~CApplication()
{

}

void Engine::CApplication::Terminate()
{
	m_pKeyboard.reset();
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
		m_pGraphics->SetCursorPosition(CPoint(0, 0));
		m_pKeyboard->OnUpdate();
		Callback();
		OnUpdate(Timer.GetDurationInSeconds(), TimeDelta / Timer.GetDuration());
		OnRenderBegin();
		OnRender();
		OnRenderEnd();
		m_pGraphics->Restore();
		m_pKeyboard->ClearBufferedEnvents();
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
	GetGraphics()->Flush();
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
