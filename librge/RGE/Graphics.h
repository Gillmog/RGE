#ifndef GRAPHICS_H
#define GRAPHICS_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CGraphics
	{
		void* m_WindowHandle;
		CPoint m_WindowSize;
		CPoint m_PrevWindowSize;
		CPoint m_FontSize;
		CPoint m_ViewPosition;

		class CBuffer
		{
		public:

			string m_Value;
			CPoint m_Position;
			CColor m_ColorAttr;
			bool m_bDirty = false;
			bool m_bFlush = false;
			bool m_bForce = false;

			CBuffer()
			{
			}

			CBuffer(const CBuffer &Other) :
				m_Value(std::move(Other.m_Value)),
				m_Position(Other.m_Position),
				m_ColorAttr(Other.m_ColorAttr),
				m_bDirty(Other.m_bDirty),
				m_bFlush(Other.m_bFlush),
				m_bForce(Other.m_bForce)
			{

			}
		};


		typedef pair<int, int> Key;

		map<Key, CBuffer> m_Buffer;

		void InitBuffer();

		void Fill(const CBuffer &Buffer);

#ifdef RGE_UNIX
		int InitColor(int BGColor, int Offset)
		{
			int StartIndex = 0;
			int i = Offset;
			for (i; i < (Offset + 8); i++)
			{
				init_pair(i, StartIndex, BGColor);
				StartIndex++;
			}

			return i;
		}
#endif
		void Terminate();

	public:

		CGraphics(CPoint WindowSize);

		~CGraphics();

		void Init();

		void Clear();

		void ClearColor();

		void Restore();

		void ShowCursor(bool bShow);

		void SetCursorPosition(CPoint Position);

		void Draw(const string &Value, CPoint Position, CColor ColorAttr, bool bForce = false);

		void Flush();

		void *GetWindowHandle() const;
		CPoint GetViewPosition() const { return m_ViewPosition; }
		void SetViewPosition(CPoint val) { m_ViewPosition = val; }
	};
}

#endif // !GRAPHICS_H