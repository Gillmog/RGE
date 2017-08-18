#ifndef UI_H
#define UI_H

#pragma once

#include "Core.h"
#include "Application.h"
#include "Graphics.h"

namespace Engine
{
	class CControlMouseMessage
	{
	public:

		enum Type
		{
			EMPTY,
			ON_MOUSE_LBUTTON_DOWN,
			ON_MOUSE_LBUTTON_UP,
			ON_MOUSE_MOVE,
			ON_MOUSE_WHEEL,
			ON_MOUSE_RBUTTON_DOWN,
			ON_MOUSE_RBUTTON_UP,
		};

		Type m_Type = EMPTY;
		CPoint m_Position;
		int m_WheelDelta = 0;

		CControlMouseMessage()
		{

		}

		CControlMouseMessage(Type Type, CPoint Position, int WheelDelta) : m_Type(Type), m_Position(Position), m_WheelDelta(WheelDelta)
		{

		}
	};

	class CControlKeyboardMessage
	{
	public:

		enum Type
		{
			EMPTY,
			ON_KEYBOARD_KEY_DOWN,
			ON_KEYBOARD_KEY_UP,
		};

		Type m_Type = EMPTY;
		int m_KeyCode = -1;
		string m_Char;

		CControlKeyboardMessage()
		{

		}

		CControlKeyboardMessage(Type Type,  int KeyCode, const string &Char) : m_Type(Type), m_KeyCode(KeyCode), m_Char(Char)
		{

		}
	};

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

#define F_MODAL 1

		int m_Flags = 0;

		int m_CurrentFocusedControl = 0;
		shared_ptr<ÑControl> m_pCurrentFocusedControl;
		shared_ptr<ÑControl> m_pChildFocusedControl;

		shared_ptr<ÑControl> GetCurrentFocusedControl() { return m_pCurrentFocusedControl; };
		shared_ptr<ÑControl> GetPrevFocusedControl() { return m_pCurrentFocusedControl; };

		void Reset()
		{
			m_pChildFocusedControl = nullptr;
			m_pCurrentFocusedControl = nullptr;
			m_CurrentFocusedControl = 0;
		}

	public:

		~ÑControl()
		{
			Destroy();
		}

		void ResetFlags()
		{
			m_Flags = 0;
		}

		shared_ptr<ÑControl> GetPrevControl(bool bFromParent = false)
		{
			if (!m_Controls.size())
				return nullptr;

			auto Iter = m_Controls.begin() + m_CurrentFocusedControl;

			int Index = m_CurrentFocusedControl;

			while (Index >= 0)
			{
				shared_ptr<ÑControl> pControl = *Iter;

				if (!pControl->IsModal() && pControl->CanFocus() && pControl != m_pCurrentFocusedControl)
				{
					m_pCurrentFocusedControl = pControl;
					m_CurrentFocusedControl = Index;
					return pControl;
				}
				else
				if (pControl->CanFocus())
				{
					shared_ptr<ÑControl> pChildControl = pControl->GetPrevControl(true);

					if (pChildControl != m_pChildFocusedControl)
					{
						m_pChildFocusedControl = pChildControl;

						if (m_pChildFocusedControl)
						{
							m_CurrentFocusedControl = Index;
							return m_pChildFocusedControl;
						}
						else
						{
							m_CurrentFocusedControl = Index;
							return m_pCurrentFocusedControl;
						}
					}
					else
					if (pChildControl)
					{
						m_pCurrentFocusedControl->Reset();
						pChildControl->Reset();
						m_pChildFocusedControl->Reset();
						m_pChildFocusedControl = nullptr;

						if (Index - 1 >= 0)
							m_CurrentFocusedControl = Index - 1;
						return m_pCurrentFocusedControl;
					}
				}

				Index--;

				if (Index >= 0)
				--Iter;
			}

			return m_pCurrentFocusedControl;
		}

		shared_ptr<ÑControl> GetNextControl(bool bFromParent = false)
		{
			if (!m_Controls.size())
				return nullptr;

			auto Iter = m_Controls.begin() + m_CurrentFocusedControl;

			int Index = m_CurrentFocusedControl;

			while (Iter != m_Controls.end())
			{
				shared_ptr<ÑControl> pControl = *Iter;

				if (!pControl->IsModal() && pControl->CanFocus() && pControl != m_pCurrentFocusedControl)
				{
					m_pCurrentFocusedControl = pControl;
					m_CurrentFocusedControl = Index;
					return pControl;
				}
				else
				if (pControl->CanFocus())
				{
					shared_ptr<ÑControl> pChildControl = pControl->GetNextControl(true);

					if (pChildControl != m_pChildFocusedControl)
					{
						m_pChildFocusedControl = pChildControl;

						if (m_pChildFocusedControl)
						{
							m_CurrentFocusedControl = Index;
							return m_pChildFocusedControl;
						}
						else
						{
							m_CurrentFocusedControl = Index;
							return m_pCurrentFocusedControl;
						}
					}
					else
					if (pChildControl)
					{
						m_pCurrentFocusedControl->Reset();
						pChildControl->Reset();
						m_pChildFocusedControl->Reset();
						m_pChildFocusedControl = nullptr;

						if (Index - 1 >= 0)
							m_CurrentFocusedControl = Index - 1;
						return m_pCurrentFocusedControl;
					}
				}

				Index++;

				++Iter;
			}

			return m_pCurrentFocusedControl;
		}

		shared_ptr<ÑControl> GetParent() const { return m_pParent; }
		void SetParent(shared_ptr<ÑControl> val) { m_pParent = val; }

		CRect GetRect() const { return m_Rect; }
		void SetRect(CRect val) { m_Rect = val; }

		bool GetHasFocus() {
			return m_bHasFocus;
		}
		void SetHasFocus(bool val)
		{ 
			if (!CanFocus() && val)
				return;

			m_bHasFocus = val;
		}

		shared_ptr<ÑControl> GetFocusedControl()
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->GetHasFocus())
					return pControl;
				else
				{
					shared_ptr<ÑControl> pChildControl = pControl->GetFocusedControl();

					if (pChildControl)
						return pChildControl;
				}
			}

			if (GetHasFocus())
				return shared_from_this();

			return nullptr;
		}

		int GetID() const { return m_ID; }
		void SetID(int val) { m_ID = val; }

		void Destroy()
		{
			m_pParent.reset();

			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				pControl->Destroy();

				pControl.reset();
			}

			m_Controls.clear();
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

		virtual void OnDraw(shared_ptr<CGraphics> pGraphics)
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				pControl->OnDraw(pGraphics);
			}
		}

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

		virtual void ProcessMouseMessage(const CControlMouseMessage &Message);
		virtual void ProcessKeyboardMessage(const CControlKeyboardMessage &Message);

		virtual void OnMouseEnter(){}

		virtual void OnMouseLeave(){}

		virtual void OnMouseDown(){}

		virtual void OnMouseUp(){}

		virtual void OnMouseRightDown(){}

		virtual void OnMouseRightUp(){}

		virtual void OnMouseWheel(int Delta) {}

		int GetFlags() const { return m_Flags; }
		void SetFlags(int val) { m_Flags = val; }
		
		void SetModal()
		{
			m_Flags = m_Flags | F_MODAL;
		}

		bool IsModal()
		{
			return m_Flags & F_MODAL;
		}
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

			ÑControl::OnDraw(pGraphics);
		}
	};

	class CButton : public ÑControl
	{
		string m_Text;
		CColor m_TextColor;

	public:

		void OnDraw(shared_ptr<CGraphics> pGraphics) override
		{
			CColor BackGroundColor = m_BackgroundColor;

			if (m_bHasFocus)
			{
				BackGroundColor.m_BGRed = m_HighlightColor.m_BGRed;
				BackGroundColor.m_BGGreen = m_HighlightColor.m_BGGreen;
				BackGroundColor.m_BGBlue = m_HighlightColor.m_BGBlue;
				BackGroundColor.m_BGAlpha = m_HighlightColor.m_BGAlpha;
			}

			for (int j = 0; j < m_Rect.GetHeight(); j++)
			{
				for (int i = 0; i < m_Rect.GetWidth(); i++)
				{
					CPoint Position(i + m_Rect.m_Left, j + m_Rect.m_Top);
					pGraphics->Draw(" ", Position, BackGroundColor);
				}
			}

			CColor TextColor = m_TextColor;

			if (m_bHasFocus)
			{
				TextColor.m_BGRed = m_HighlightColor.m_BGRed;
				TextColor.m_BGGreen = m_HighlightColor.m_BGGreen;
				TextColor.m_BGBlue = m_HighlightColor.m_BGBlue;
				TextColor.m_BGAlpha = m_HighlightColor.m_BGAlpha;
			}

			if (m_Text.length() > 0)
			{
				CPoint Position(m_Rect.m_Left, m_Rect.m_Top);

				pGraphics->Draw(m_Text, Position, TextColor);
			}

			ÑControl::OnDraw(pGraphics);
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

			ÑControl::OnDraw(pGraphics);
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
		shared_ptr<ÑControl> m_pCurrentControl;
		shared_ptr<ÑControl> m_pInputControl;
		shared_ptr<ÑControl> m_pPrevControl;
		shared_ptr<ÑControl> m_pNextControl;
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

		shared_ptr<ÑControl> GetFocusedControl()
		{
			for (int nControl = 0; nControl < m_Controls.size(); nControl++)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				shared_ptr<ÑControl> pChildControl = pControl->GetFocusedControl();

				if (pChildControl)
					return pChildControl;
			}

			return nullptr;
		}


		shared_ptr<ÑControl> GetPrevControl()
		{
			for (int nControl = m_Controls.size() - 1; nControl >= 0; nControl--)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->IsModal())
					return pControl->GetPrevControl();
			}

			return nullptr;
		}

		shared_ptr<ÑControl> GetNextControl()
		{
			for (int nControl = m_Controls.size() - 1; nControl >= 0; nControl--)
			{
				shared_ptr<ÑControl> pControl = m_Controls[nControl];

				if (pControl->IsModal())
					return pControl->GetNextControl();
			}

			return nullptr;
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

		shared_ptr<ÑControl> PickControlFromPoint(CPoint Position);

		void ProcessMouseMessage(const CControlMouseMessage &Message);
		void ProcessKeyboardMessage(const CControlKeyboardMessage &Message);
		void ProcessMessage(CApplication *pApplication);
	};
}

#endif //UI_H