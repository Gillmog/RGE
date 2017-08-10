#ifndef UI_H
#define UI_H

#pragma once

#include "Core.h"
#include "Application.h"
#include "Graphics.h"

namespace Engine
{
	class ÑControl : public std::enable_shared_from_this<ÑControl>
	{
	protected:

		shared_ptr<ÑControl> m_pParent;
		std::vector<shared_ptr<ÑControl> > m_Controls;

		CRect m_Rect;
		bool m_bHasFocus;
		int m_ID;
		CColor m_BackgroundColor;
		CColor m_HighlightColor;
		bool m_bVisible = true;

	public:

		~ÑControl()
		{
			Destroy();
		}

		shared_ptr<ÑControl> GetParent() const { return m_pParent; }
		void SetParent(shared_ptr<ÑControl> val) { m_pParent = val; }

		CRect GetRect() const { return m_Rect; }
		void SetRect(CRect val) { m_Rect = val; }

		bool GetHasFocus() const { return m_bHasFocus; }
		void SetHasFocus(bool val) { m_bHasFocus = val; }

		int GetID() const { return m_ID; }
		void SetID(int val) { m_ID = val; }

		void Destroy()
		{
			m_pParent.reset();

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				pControl.reset();
			}
		}

		virtual void Move(const CPoint &Position)
		{
			m_Rect.Move(Position.m_X, Position.m_Y);

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				CRect Rect = pControl->GetRect();

				Rect.Move(Position.m_X, Position.m_Y);

				pControl->SetRect(Rect);
			}
		}

		virtual void AddControl(shared_ptr<ÑControl> pControl)
		{
			assert(pControl);

			if (pControl == nullptr)
				return;

			pControl->SetParent(shared_from_this());

			CRect Rect = pControl->GetRect();
			Rect.Move(m_Rect.m_Left, m_Rect.m_Top);
			pControl->SetRect(Rect);
			m_Controls.push_back(pControl);
		}

		int GetNumControls()
		{
			return (int)m_Controls.size();
		}

		shared_ptr<ÑControl> GetControl(int Index)
		{
			assert(Index >= 0);
			assert(Index < m_Controls.size());

			return m_Controls[Index];
		}

		shared_ptr<ÑControl> FindControlByID(int ID)
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->GetID() == ID)
					return pControl;
			}

			return nullptr;
		}

		Engine::CColor GetBackgroundColor() const { return m_BackgroundColor; }
		void SetBackgroundColor(Engine::CColor val) { m_BackgroundColor = val; }

		virtual void OnDraw(shared_ptr<CGraphics> pGraphics) = 0;

		shared_ptr<ÑControl> PickControlFromPoint(CPoint Position)
		{
			for (int nControl = m_Controls.size() - 1; nControl >= 0; nControl--)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (!pControl->CanFocus())
					continue;

				if (!pControl->IsVisible())
					continue;

				if (pControl->GetRect().IsInside(Position.m_X, Position.m_Y))
				{
					return pControl;
				}
				else
				{
					pControl = pControl->PickControlFromPoint(Position);

					if (pControl)
						return pControl;
				}
			}

			if (!IsVisible())
				return nullptr;

			if (m_Rect.IsInside(Position.m_X, Position.m_Y))
				return shared_from_this();

			return nullptr;
		}

		virtual bool CanFocus() { return true; }

		bool IsVisible() const { return m_bVisible; }

		void SetVisible(bool val) 
		{ 
			m_bVisible = val;

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				pControl->SetVisible(val);
			}
		}

		Engine::CColor GetHighlightColor() const { return m_HighlightColor; }
		void SetHighlightColor(Engine::CColor val) { m_HighlightColor = val; }
	};

	class CDialog : public ÑControl
	{
	public:

		void OnDraw(shared_ptr<CGraphics> pGraphics) override
		{
			for (int j = 0; j < m_Rect.GetHeight(); j++)
			{
				for (int i = 0; i < m_Rect.GetWidth(); i++)
				{
					CPoint Position(i + m_Rect.m_Left, j + m_Rect.m_Top);
					pGraphics->Draw(" ", Position, m_BackgroundColor);
				}
			}

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				pControl->OnDraw(pGraphics);
			}
		}
	};

	class CButton : public ÑControl
	{
		string m_Text;
		CColor m_TextColor;

	public:

		void OnDraw(shared_ptr<CGraphics> pGraphics) override
		{
			for (int j = 0; j < m_Rect.GetHeight(); j++)
			{
				for (int i = 0; i < m_Rect.GetWidth(); i++)
				{
					CPoint Position(i + m_Rect.m_Left, j + m_Rect.m_Top);
					pGraphics->Draw(" ", Position, m_BackgroundColor);
				}
			}

			
			if (m_Text.length() > 0)
			{
				CPoint Position(m_Rect.m_Left, m_Rect.m_Top);

				pGraphics->Draw(m_Text, Position, m_TextColor);
			}
		}

		std::string GetText() const { return m_Text; }
		void SetText(std::string val) 
		{ 
			int Width = m_Rect.GetWidth();

			if (val.length() > Width)
				m_Rect.m_Right = m_Rect.m_Left + val.length();

			m_Text = val; 
		}

		Engine::CColor GetTextColor() const { return m_TextColor; }
		void SetTextColor(Engine::CColor val)
		{
			m_TextColor = val;
			m_TextColor.m_BGRed = m_BackgroundColor.m_BGRed;
			m_TextColor.m_BGGreen = m_BackgroundColor.m_BGGreen;
			m_TextColor.m_BGBlue = m_BackgroundColor.m_BGBlue;
			m_TextColor.m_BGAlpha = m_BackgroundColor.m_BGAlpha;
		}
	};

	class CLabel : public ÑControl
	{
		string m_Text;
		CColor m_TextColor;

	public:

		void OnDraw(shared_ptr<CGraphics> pGraphics) override
		{
			if (m_Text.length() > 0)
			{
				CPoint Position(m_Rect.m_Left, m_Rect.m_Top);

				pGraphics->Draw(m_Text, Position, m_TextColor);
			}
		}

		std::string GetText() const { return m_Text; }
		void SetText(std::string val) { m_Text = val; }

		Engine::CColor GetTextColor() const { return m_TextColor; }
		void SetTextColor(Engine::CColor val) 
		{ 
			m_TextColor = val;
			CColor ParentColor = m_pParent->GetBackgroundColor();
			m_TextColor.m_BGRed = ParentColor.m_BGRed;
			m_TextColor.m_BGGreen = ParentColor.m_BGGreen;
			m_TextColor.m_BGBlue = ParentColor.m_BGBlue;
			m_TextColor.m_BGAlpha = ParentColor.m_BGAlpha;
		}

		bool CanFocus() override { return false; }
	};

	class CControlsManager
	{
		static CControlsManager* m_pInstance;

		std::vector<shared_ptr<ÑControl> > m_Controls;

	public:

		static CControlsManager* GetSingleton();

		shared_ptr<ÑControl> FindControlByID(int ID)
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->GetID() == ID)
					return pControl;
			}

			return nullptr;
		}

		bool Destroy(int ID)
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->GetID() == ID)
				{
					pControl->Destroy();
					pControl.reset();
					m_Controls.erase(m_Controls.begin() + nControl);
					return true;
				}
			}

			return false;
		}

		template<typename T>
		shared_ptr<T> Create(shared_ptr<ÑControl> pParent, int ID, const CRect &Rect)
		{
			if (FindControlByID(ID))
				return nullptr;

			shared_ptr<T> pCreatedControl = make_shared<T>();
			shared_ptr<ÑControl> pControl = pCreatedControl;
			pControl->SetParent(pParent);
			pControl->SetID(ID);
			pControl->SetRect(Rect);

			if (pParent == nullptr)
				m_Controls.push_back(pControl);
			else
				pParent->AddControl(pControl);

			return pCreatedControl;
		}

		void OnDraw(shared_ptr<CGraphics> pGraphics)
		{
			CPoint ViewSavePosition = pGraphics->GetViewPosition();

			pGraphics->SetViewPosition(CPoint());

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (!pControl->IsVisible())
					continue;

				pControl->OnDraw(pGraphics);
			}

			pGraphics->SetViewPosition(ViewSavePosition);
		}

		int GetNumControls() const
		{
			return (int)m_Controls.size();
		}

		shared_ptr<ÑControl> GetControl(int Index)
		{
			assert(Index >= 0);
			assert(Index < m_Controls.size());

			shared_ptr<ÑControl> pControl = m_Controls[Index];

			return pControl;
		}
	};
}

#endif //UI_H