#ifndef SPRITE_H
#define SPRITE_H

#pragma once

#include "Core.h"
#include "Archive.h"

namespace Engine
{
	class CSprite
	{
		string m_Name;
		int m_Frame = 0;
		CPoint m_Position;
		bool m_bPlay = false;
		float m_FrameTime = 0.0f;

	public:

		class CSpriteFrame
		{
			int m_Width;
			int m_Height;

		public:

			struct CSpriteBuffer
			{
				CColor m_Color;
				CPoint m_Position;
				string m_Char;
				bool m_Valid = false;
			};

		private:

			vector<CSpriteBuffer> m_Buffer;

		public:

			CSpriteFrame()
			{
			}

			void InitBuffer()
			{
				m_Buffer.resize(m_Width * m_Height);
			}

			void Serialize(CArchive &Archive);

			int GetBufferSize() const {
				return (int)m_Buffer.size();
			}

			const CSpriteBuffer &GetBuffer(int n) const { return m_Buffer[n]; }

			void SetBuffer(const CSpriteBuffer &Buffer);

			void SetBuffer(const CPoint &Position, const CColor &Color, const string &Char);

			int GetWidth() const { return m_Width; }
			void SetWidth(int val) { m_Width = val; }
			int GetHeight() const { return m_Height; }
			void SetHeight(int val) { m_Height = val; }

			void ReleaseBuffer(int nBufferIndex)
			{
				m_Buffer[nBufferIndex] = CSpriteBuffer();
			}
		};

	private:

		vector<CSpriteFrame> m_Frames;

	public:

		CSprite(const string &Name, int Width, int Height);

		string GetName() const { return m_Name; }
		void SetName(string val) { m_Name = val; }

		int GetNumFrames() { return (int)m_Frames.size(); }

		CSpriteFrame& GetSpriteFrame();

		void Serialize(CArchive &Archive);

		int GetFrame() const { return m_Frame; }
		void SetFrame(int val) { m_Frame = val; }

		void AddFrame(int Width, int Height);

		void RemoveFrame(int nFrame);

		CPoint GetPosition() const { return m_Position; }
		void SetPosition(CPoint val) { m_Position = val; }

		bool IsPlay() const { return m_bPlay; }
		void SetPlay(bool val) { m_bPlay = val; }

		void Update(double Time, double TimeDelta);
	};

	class CSpriteManager
	{
		vector<CSprite*> m_Sprites;

		static CSpriteManager* m_pInstance;

	public:

		CSpriteManager()
		{

		}

		~CSpriteManager();

		void Free();

		CSprite *FindSprite(const string &Name);

		int GetNumSprites();

		CSprite *GetSprite(int Index);

		bool RemoveSprite(const string &Name);

		void RemoveSprite(int Index);

		bool AddSprite(CSprite *pSprite);

		CSprite *CreateSprite(const string &Name, int Width, int Height);

		static CSpriteManager* GetSingleton();
	};
}

#endif //SPRITE_H