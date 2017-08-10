#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CApplication;
	class CEvents;

	class CMouse
	{
		struct CButton
		{
			CPoint m_Position;
			bool m_bState = false;
		};

		CButton m_BufferedEvents[5];
		CButton m_PrevBufferedEvents[5];

		CPoint m_MousePosition;
		int m_MouseWheel = 0;
		bool m_bLock = false;

	public:

		CMouse(CApplication *pApp);

		~CMouse()
		{
			
		}

		bool IsPressed(int Button);

		bool IsReleased(int Button);

#if defined(RGE_WIN)
		void OnEvent(const INPUT_RECORD &Event);
#endif

		void OnUpdate(CEvents *pEvents);

		void ClearBufferedEnvents();

		CPoint GetPosition() const { return m_MousePosition; }
	
		int GetWheel() const { return m_MouseWheel; }

		bool IsLock() const { return m_bLock; }
		void SetLock(bool val) { m_bLock = val; }
	};

	class CKeyboard
	{
		map<int, int> m_MappedKeys;

		bool m_bLock = false;

		void AddMappedKey(int Key, int KeyCode)
		{
			m_MappedKeys.insert(make_pair(Key, KeyCode));
		}

		int ToMappedKey(int Key)
		{
			auto iter = m_MappedKeys.find(Key);

			if (iter != m_MappedKeys.end())
			{
				return iter->second;
			}

			iter = m_MappedKeys.find(toupper(Key));

			if (iter != m_MappedKeys.end())
			{
				return iter->second;
			}

			return -1;
		}

	public:

		enum
		{
			K_RESERVED = 0,
			K_ESC = 1,
			K_1 = 2,
			K_2 = 3,
			K_3 = 4,
			K_4 = 5,
			K_5 = 6,
			K_6 = 7,
			K_7 = 8,
			K_8 = 9,
			K_9 = 10,
			K_0 = 11,
			K_MINUS = 12,
			K_EQUAL = 13,
			K_BACKSPACE = 14,
			K_TAB = 15,
			K_Q = 16,
			K_W = 17,
			K_E = 18,
			K_R = 19,
			K_T = 20,
			K_Y = 21,
			K_U = 22,
			K_I = 23,
			K_O = 24,
			K_P = 25,
			K_LEFTBRACE = 26,
			K_RIGHTBRACE = 27,
			K_ENTER = 28,
			K_LEFTCTRL = 29,
			K_A = 30,
			K_S = 31,
			K_D = 32,
			K_F = 33,
			K_G = 34,
			K_H = 35,
			K_J = 36,
			K_K = 37,
			K_L = 38,
			K_SEMICOLON = 39,
			K_APOSTROPHE = 40,
			K_GRAVE = 41,
			K_LEFTSHIFT = 42,
			K_BACKSLASH = 43,
			K_Z = 44,
			K_X = 45,
			K_C = 46,
			K_V = 47,
			K_B = 48,
			K_N = 49,
			K_M = 50,
			K_COMMA = 51,
			K_DOT = 52,
			K_SLASH = 53,
			K_RIGHTSHIFT = 54,
			K_KPASTERISK = 55,
			K_LEFTALT = 56,
			K_SPACE = 57,
			K_CAPSLOCK = 58,
			K_F1 = 59,
			K_F2 = 60,
			K_F3 = 61,
			K_F4 = 62,
			K_F5 = 63,
			K_F6 = 64,
			K_F7 = 65,
			K_F8 = 66,
			K_F9 = 67,
			K_F10 = 68,
			K_NUMLOCK = 69,
			K_SCROLLLOCK = 70,
			K_KP7 = 71,
			K_KP8 = 72,
			K_KP9 = 73,
			K_KPMINUS = 74,
			K_KP4 = 75,
			K_KP5 = 76,
			K_KP6 = 77,
			K_KPPLUS = 78,
			K_KP1 = 79,
			K_KP2 = 80,
			K_KP3 = 81,
			K_KP0 = 82,
			K_KPDOT = 83,
			K_ZENKAKUHANKAKU = 85,
			K_102ND = 86,
			K_F11 = 87,
			K_F12 = 88,
			K_RO = 89,
			K_KATAKANA = 90,
			K_HIRAGANA = 91,
			K_HENKAN = 92,
			K_KATAKANAHIRAGANA = 93,
			K_MUHENKAN = 94,
			K_KPJPCOMMA = 95,
			K_KPENTER = 96,
			K_RIGHTCTRL = 97,
			K_KPSLASH = 98,
			K_SYSRQ = 99,
			K_RIGHTALT = 100,
			K_LINEFEED = 101,
			K_HOME = 102,
			K_UP = 103,
			K_PAGEUP = 104,
			K_LEFT = 105,
			K_RIGHT = 106,
			K_END = 107,
			K_DOWN = 108,
			K_PAGEDOWN = 109,
			K_INSERT = 110,
			K_DELETE = 111,
			K_MACRO = 112,
			K_MUTE = 113,
			K_VOLUMEDOWN = 114,
			K_VOLUMEUP = 115,
			K_POWER = 116,
			K_KPEQUAL = 117,
			K_KPPLUSMINUS = 118,
			K_PAUSE = 119,
			K_SCALE = 120,
			K_KPCOMMA = 121,
			K_HANGEUL = 122,
			K_HANGUEL = 122,
			K_HANJA = 123,
			K_YEN = 124,
			K_LEFTMETA = 125,
			K_RIGHTMETA = 126,
			K_COMPOSE = 127,
			K_STOP = 128,
			K_AGAIN = 129,
			K_PROPS = 130,
			K_UNDO = 131,
			K_FRONT = 132,
			K_COPY = 133,
			K_OPEN = 134,
			K_PASTE = 135,
			K_FIND = 136,
			K_CUT = 137,
			K_HELP = 138,
			K_MENU = 139,
			K_CALC = 140,
			K_SETUP = 141,
			K_SLEEP = 142,
			K_WAKEUP = 143,
			K_FILE = 144,
			K_SENDFILE = 145,
			K_DELETEFILE = 146,
			K_XFER = 147,
			K_PROG1 = 148,
			K_PROG2 = 149,
			K_WWW = 150,
			K_MSDOS = 151,
			K_COFFEE = 152,
			K_SCREENLOCK = 152,
			K_ROTATE_DISPLAY = 153,
			K_DIRECTION = 153,
			K_CYCLEWINDOWS = 154,
			K_MAIL = 155,
			K_BOOKMARKS = 156,
			K_COMPUTER = 157,
			K_BACK = 158,
			K_FORWARD = 159,
			K_CLOSECD = 160,
			K_EJECTCD = 161,
			K_EJECTCLOSECD = 162,
			K_NEXTSONG = 163,
			K_PLAYPAUSE = 164,
			K_PREVIOUSSONG = 165,
			K_STOPCD = 166,
			K_RECORD = 167,
			K_REWIND = 168,
			K_PHONE = 169,
			K_ISO = 170,
			K_CONFIG = 171,
			K_HOMEPAGE = 172,
			K_REFRESH = 173,
			K_EXIT = 174,
			K_MOVE = 175,
			K_EDIT = 176,
			K_SCROLLUP = 177,
			K_SCROLLDOWN = 178,
			K_KPLEFTPAREN = 179,
			K_KPRIGHTPAREN = 180,
			K_NEW = 181,
			K_REDO = 182,
			K_F13 = 183,
			K_F14 = 184,
			K_F15 = 185,
			K_F16 = 186,
			K_F17 = 187,
			K_F18 = 188,
			K_F19 = 189,
			K_F20 = 190,
			K_F21 = 191,
			K_F22 = 192,
			K_F23 = 193,
			K_F24 = 194,
			K_PLAYCD = 200,
			K_PAUSECD = 201,
			K_PROG3 = 202,
			K_PROG4 = 203,
			K_DASHBOARD = 204,
			K_SUSPEND = 205,
			K_CLOSE = 206,
			K_PLAY = 207,
			K_FASTFORWARD = 208,
			K_BASSBOOST = 209,
			K_PRINT = 210,
			K_HP = 211,
			K_CAMERA = 212,
			K_SOUND = 213,
			K_QUESTION = 214,
			K_EMAIL = 215,
			K_CHAT = 216,
			K_SEARCH = 217,
			K_CONNECT = 218,
			K_FINANCE = 219,
			K_SPORT = 220,
			K_SHOP = 221,
			K_ALTERASE = 222,
			K_CANCEL = 223,
			K_BRIGHTNESSDOWN = 224,
			K_BRIGHTNESSUP = 225,
			K_MEDIA = 226,
			K_SWITCHVIDEOMODE = 227,
			K_KBDILLUMTOGGLE = 228,
			K_KBDILLUMDOWN = 229,
			K_KBDILLUMUP = 230,
			K_SEND = 231,
			K_REPLY = 232,
			K_FORWARDMAIL = 233,
			K_SAVE = 234,
			K_DOCUMENTS = 235,
			K_BATTERY = 236,
			K_BLUETOOTH = 237,
			K_WLAN = 238,
			K_UWB = 239,
			K_UNKNOWN = 240,
			K_VIDEO_NEXT = 241,
			K_VIDEO_PREV = 242,
			K_BRIGHTNESS_CYCLE = 243,
			K_BRIGHTNESS_AUTO = 244,
			K_BRIGHTNESS_ZERO = 244,
			K_DISPLAY_OFF = 245,
			K_WWAN = 246,
			K_WIMAX = 246,
			K_RFKILL = 247,
			K_MICMUTE = 248
		};

	private:

		struct CKey
		{
			char m_Ascii;
			int m_KeyCode;
			bool m_bState = false;
		};

		CKey m_BufferedEvents[256];
		CKey m_PrevBufferedEvents[256];

	public:

		CKeyboard(CApplication *pApp);

		~CKeyboard()
		{
			
		}

#if defined(RGE_WIN)
		void OnEvent(const INPUT_RECORD &Event);
#endif

		void OnUpdate(CEvents *pEvents);

		void ClearBufferedEnvents();

		bool IsKeyPressed(int KeyCode);

		bool IsKeyReleased(int KeyCode);

		bool IsLock() const { return m_bLock; }
		void SetLock(bool val) { m_bLock = val; }
	};
}

#endif

