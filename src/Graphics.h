#ifndef GRAPHICS_H
#define GRAPHICS_H

#pragma once

#include "CoreBase.h"

namespace Engine
{
	class CGraphics
	{
		HANDLE m_WindowHandle;
		CPoint m_WindowSize;
		CPoint m_FontSize;

		class CBuffer
		{
		public:

			string m_Value;
			CPoint m_Position;
			WORD m_ColorAttr;
			bool m_bDirty = false;

			CBuffer(){}

			CBuffer(const CBuffer &Other) : m_Value(std::move(Other.m_Value)), m_Position(Other.m_Position), m_ColorAttr(Other.m_ColorAttr)
			{

			}
		};

		typedef pair<int, int> Key;
		map<Key, CBuffer> m_Buffer;

		void InitBuffer();

	public:

		CGraphics(CPoint WindowSize);

		~CGraphics();

		void Clear();

		void ClearColor();

		void Restore();

		void ShowCursor(bool bShow);

		void Draw(const string &Value, CPoint Position, WORD ColorAttr);

		void Flush();

		void *GetWindowHandle() const;
	};
}

#endif // !GRAPHICS_H