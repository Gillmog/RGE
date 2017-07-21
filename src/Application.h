#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

#include "CoreBase.h"
#include "Graphics.h"
#include "Input.h"

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
		shared_ptr<CKeyboard> m_pKeyBoard;

	public:

		CApplication(CPoint WindowSize);

		~CApplication();

		void EventLoop(function<void()> &&Callback);

		std::shared_ptr<Engine::CGraphics> GetGraphics() const { return m_pGraphics; }
		std::shared_ptr<Engine::CKeyboard> GetKeyBoard() const { return m_pKeyBoard; }

		virtual void OnUpdate() {}
	};
}


#endif // !APPLICATION_H
