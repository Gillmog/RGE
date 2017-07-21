#include "stdafx.h"
#include "Application.h"

Engine::CApplication::CApplication(CPoint WindowSize)
{
	m_pGraphics = make_shared<CGraphics>(WindowSize);
	m_pGraphics->ShowCursor(false);
	m_pKeyBoard = make_shared<CKeyboard>();
}

Engine::CApplication::~CApplication()
{

}

void Engine::CApplication::EventLoop(function<void()> &&Callback)
{
	while (true)
	{
		m_pKeyBoard->OnUpdate();
		Callback();
		OnUpdate();
		m_pGraphics->Restore();
		//Sleep(1);
		m_pKeyBoard->ClearBufferedEnvents();
	}
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
