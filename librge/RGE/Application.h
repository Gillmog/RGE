#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "Core.h"
#include "Graphics.h"
#include "Input.h"
#include "UI.h"

namespace Engine
{
	class CTimer
	{
		clock_t m_Start;
		bool m_bStart;

	public:

		CTimer();

		void Start();

		void Stop();

		double GetDurationInSeconds() const;

		double GetDuration() const;

	};

	class CApplication
	{
		shared_ptr<CGraphics> m_pGraphics;
		shared_ptr<CKeyboard> m_pKeyboard;
		shared_ptr<CMouse> m_pMouse;
		shared_ptr<CEvents> m_pInputEvents;

	public:

		CApplication(CPoint WindowSize, const string &WindowTitle);

		~CApplication();

		void Terminate();

		void EventLoop(function<void()> &&Callback);

		std::shared_ptr<Engine::CGraphics> GetGraphics() const { return m_pGraphics; }
		std::shared_ptr<Engine::CKeyboard> GetKeyboard() const { return m_pKeyboard; }
		std::shared_ptr<Engine::CMouse> GetMouse() const { return m_pMouse; }

		virtual void OnUpdate(double Time, double TimeDelta) {}
		virtual void OnRenderBegin();
		virtual void OnRender();
		virtual void OnRenderEnd();

		string GetPath();
	};

	class CEvents
	{
		DWORD m_fdwSaveOldMode;
		CApplication *m_pApplication;

#if defined(RGE_WIN)
		VOID ErrorExit(LPSTR lpszMessage);
#endif

	public:

		void* m_InputHandle;
#if defined(RGE_WIN)
		INPUT_RECORD m_InputRecord[128];
		DWORD m_NumEvents = 0;
		DWORD m_NumberOfEventsRead = 0;
#endif

		CEvents(CApplication *pApp);

		~CEvents();

		void ReadEvents();
	};
}


#endif // !APPLICATION_H
