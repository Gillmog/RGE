#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CKeyboard
	{
		void* m_InputHandle;
		DWORD m_NumEvents = 0;

	public:

		enum
		{
			//Mappable codes
			K_ABNT_C1 = 0xC1, //Abnt C1
			K_ABNT_C2 = 0xC2, //Abnt C2
			K_ADD = 0x6B, //Numpad +
			K_ATTN = 0xF6, //Attn
			K_BACK = 0x08, //Backspace
			K_CANCEL = 0x03, //Break
			K_CLEAR = 0x0C, //Clear
			K_CRSEL = 0xF7, //Cr Sel
			K_DECIMAL = 0x6E, //Numpad .
			K_DIVIDE = 0x6F, //Numpad /
			K_EREOF = 0xF9, //Er Eof
			K_ESCAPE = 0x1B, //Esc
			K_EXECUTE = 0x2B, //Execute
			K_EXSEL = 0xF8, //Ex Sel
			K_ICO_CLEAR = 0xE6, //IcoClr
			K_ICO_HELP = 0xE3, //IcoHlp
			K_KEY_0 = 0x30, //('0')	0
			K_KEY_1 = 0x31, //('1')	1
			K_KEY_2 = 0x32, //('2')	2
			K_KEY_3 = 0x33, //('3')	3
			K_KEY_4 = 0x34, //('4')	4
			K_KEY_5 = 0x35, //('5')	5
			K_KEY_6 = 0x36, //('6')	6
			K_KEY_7 = 0x37, //('7')	7
			K_KEY_8 = 0x38, //('8')	8
			K_KEY_9 = 0x39, //('9')	9
			K_KEY_A = 0x41, //('A')	A
			K_KEY_B = 0x42, //('B')	B
			K_KEY_C = 0x43, //('C')	C
			K_KEY_D = 0x44, //('D')	D
			K_KEY_E = 0x45, //('E')	E
			K_KEY_F = 0x46, //('F')	F
			K_KEY_G = 0x47, //('G')	G
			K_KEY_H = 0x48, //('H')	H
			K_KEY_I = 0x49, //('I')	I
			K_KEY_J = 0x4A, //('J')	J
			K_KEY_K = 0x4B, //('K')	K
			K_KEY_L = 0x4C, //('L')	L
			K_KEY_M = 0x4D, //('M')	M
			K_KEY_N = 0x4E, //('N')	N
			K_KEY_O = 0x4F, //('O')	O
			K_KEY_P = 0x50, //('P')	P
			K_KEY_Q = 0x51, //('Q')	Q
			K_KEY_R = 0x52, //('R')	R
			K_KEY_S = 0x53, //('S')	S
			K_KEY_T = 0x54, //('T')	T
			K_KEY_U = 0x55, //('U')	U
			K_KEY_V = 0x56, //('V')	V
			K_KEY_W = 0x57, //('W')	W
			K_KEY_X = 0x58, //('X')	X
			K_KEY_Y = 0x59, //('Y')	Y
			K_KEY_Z = 0x5A, //('Z')	Z
			K_MULTIPLY = 0x6A, //Numpad *
			K_NONAME = 0xFC, //NoName
			K_NUMPAD0 = 0x60, //Numpad 0
			K_NUMPAD1 = 0x61, //Numpad 1
			K_NUMPAD2 = 0x62, //Numpad 2
			K_NUMPAD3 = 0x63, //Numpad 3
			K_NUMPAD4 = 0x64, //Numpad 4
			K_NUMPAD5 = 0x65, //Numpad 5
			K_NUMPAD6 = 0x66, //Numpad 6
			K_NUMPAD7 = 0x67, //Numpad 7
			K_NUMPAD8 = 0x68, //Numpad 8
			K_NUMPAD9 = 0x69, //Numpad 9
			K_OEM_1 = 0xBA, //OEM_1(:;)
			K_OEM_102 = 0xE2, //OEM_102(> < )
			K_OEM_2 = 0xBF, //OEM_2(? / )
			K_OEM_3 = 0xC0, //OEM_3(~`)
			K_OEM_4 = 0xDB, //OEM_4({ [)
			K_OEM_5 = 0xDC, //OEM_5(| \)
			K_OEM_6 = 0xDD, //OEM_6(}])
			K_OEM_7 = 0xDE, //OEM_7(" ')
			K_OEM_8 = 0xDF, //OEM_8(§ !)
			K_OEM_ATTN = 0xF0, //Oem Attn
			K_OEM_AUTO = 0xF3, //Auto
			K_OEM_AX = 0xE1, //Ax
			K_OEM_BACKTAB = 0xF5, //Back Tab
			K_OEM_CLEAR = 0xFE, //OemClr
			K_OEM_COMMA = 0xBC, //OEM_COMMA(< , )
			K_OEM_COPY = 0xF2, //Copy
			K_OEM_CUSEL = 0xEF, //Cu Sel
			K_OEM_ENLW = 0xF4, //Enlw
			K_OEM_FINISH = 0xF1, //Finish
			K_OEM_FJ_LOYA = 0x95, //Loya
			K_OEM_FJ_MASSHOU = 0x93, //Mashu
			K_OEM_FJ_ROYA = 0x96, //Roya
			K_OEM_FJ_TOUROKU = 0x94, //Touroku
			K_OEM_JUMP = 0xEA, //Jump
			K_OEM_MINUS = 0xBD, //OEM_MINUS(_ - )
			K_OEM_PA1 = 0xEB, //OemPa1
			K_OEM_PA2 = 0xEC, //OemPa2
			K_OEM_PA3 = 0xED, //OemPa3
			K_OEM_PERIOD = 0xBE, //OEM_PERIOD(> .)
			K_OEM_PLUS = 0xBB, //OEM_PLUS(+= )
			K_OEM_RESET = 0xE9, //Reset
			K_OEM_WSCTRL = 0xEE, //WsCtrl
			K_PA1 = 0xFD, //Pa1
			K_PACKET = 0xE7, //Packet
			K_PLAY = 0xFA, //Play
			K_PROCESSKEY = 0xE5, //Process
			K_RETURN = 0x0D, //Enter
			K_SELECT = 0x29, //Select
			K_SEPARATOR = 0x6C, //Separator
			K_SPACE = 0x20, //Space
			K_SUBTRACT = 0x6D, //Num -
			K_TAB = 0x09, //Tab
			K_ZOOM = 0xFB,
			//Non-mappable codes
			K__none_ = 0xFF,//no VK mapping
			K_ACCEPT = 0x1E,//Accept
			K_APPS = 0x5D,//Context Menu
			K_BROWSER_BACK = 0xA6,//Browser Back
			K_BROWSER_FAVORITES = 0xAB,//Browser Favorites
			K_BROWSER_FORWARD = 0xA7,//Browser Forward
			K_BROWSER_HOME = 0xAC,//Browser Home
			K_BROWSER_REFRESH = 0xA8,//Browser Refresh
			K_BROWSER_SEARCH = 0xAA,//Browser Search
			K_BROWSER_STOP = 0xA9,//Browser Stop
			K_CAPITAL = 0x14,//Caps Lock
			K_CONVERT = 0x1C,//Convert
			K_DELETE = 0x2E,//Delete
			K_DOWN = 0x28,//Arrow Down
			K_END = 0x23,//End
			K_F1 = 0x70,//F1
			K_F10 = 0x79,//F10
			K_F11 = 0x7A,//F11
			K_F12 = 0x7B,//F12
			K_F13 = 0x7C,//F13
			K_F14 = 0x7D,//F14
			K_F15 = 0x7E,//F15
			K_F16 = 0x7F,//F16
			K_F17 = 0x80,//F17
			K_F18 = 0x81,//F18
			K_F19 = 0x82,//F19
			K_F2 = 0x71,//F2
			K_F20 = 0x83,//F20
			K_F21 = 0x84,//F21
			K_F22 = 0x85,//F22
			K_F23 = 0x86,//F23
			K_F24 = 0x87,//F24
			K_F3 = 0x72,//F3
			K_F4 = 0x73,//F4
			K_F5 = 0x74,//F5
			K_F6 = 0x75,//F6
			K_F7 = 0x76,//F7
			K_F8 = 0x77,//F8
			K_F9 = 0x78,//F9
			K_FINAL = 0x18,//Final
			K_HELP = 0x2F,//Help
			K_HOME = 0x24,//Home
			K_ICO_00 = 0xE4,//Ico00 *
			K_INSERT = 0x2D,//Insert
			K_JUNJA = 0x17,//Junja
			K_KANA = 0x15,//Kana
			K_KANJI = 0x19,//Kanji
			K_LAUNCH_APP1 = 0xB6,//App1
			K_LAUNCH_APP2 = 0xB7,//App2
			K_LAUNCH_MAIL = 0xB4,//Mail
			K_LAUNCH_MEDIA_SELECT = 0xB5,//Media
			K_LBUTTON = 0x01,//Left Button **
			K_LCONTROL = 0xA2,//Left Ctrl
			K_LEFT = 0x25,//Arrow Left
			K_LMENU = 0xA4,//Left Alt
			K_LSHIFT = 0xA0,//Left Shift
			K_LWIN = 0x5B,//Left Win
			K_MBUTTON = 0x04,//Middle Button **
			K_MEDIA_NEXT_TRACK = 0xB0,//Next Track
			K_MEDIA_PLAY_PAUSE = 0xB3,//Play / Pause
			K_MEDIA_PREV_TRACK = 0xB1,//Previous Track
			K_MEDIA_STOP = 0xB2,//Stop
			K_MODECHANGE = 0x1F,//Mode Change
			K_NEXT = 0x22,//Page Down
			K_NONCONVERT = 0x1D,//Non Convert
			K_NUMLOCK = 0x90,//Num Lock
			K_OEM_FJ_JISHO = 0x92,//Jisho
			K_PAUSE = 0x13,//Pause
			K_PRINT = 0x2A,//Print
			K_PRIOR = 0x21,//Page Up
			K_RBUTTON = 0x02,//Right Button **
			K_RCONTROL = 0xA3,//Right Ctrl
			K_RIGHT = 0x27,//Arrow Right
			K_RMENU = 0xA5,//Right Alt
			K_RSHIFT = 0xA1,//Right Shift
			K_RWIN = 0x5C,//Right Win
			K_SCROLL = 0x91,//Scrol Lock
			K_SLEEP = 0x5F,//Sleep
			K_SNAPSHOT = 0x2C,//Print Screen
			K_UP = 0x26,//Arrow Up
			K_VOLUME_DOWN = 0xAE,//Volume Down
			K_VOLUME_MUTE = 0xAD,//Volume Mute
			K_VOLUME_UP = 0xAF,//Volume Up
			K_XBUTTON1 = 0x05,//X Button 1 **
			K_XBUTTON2 = 0x06//X Button 2 **
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

		CKeyboard();

		void OnUpdate();

		void ClearBufferedEnvents();

		bool IsKeyPressed(int KeyCode);

		bool IsKeyReleased(int KeyCode);
	};
}

#endif

