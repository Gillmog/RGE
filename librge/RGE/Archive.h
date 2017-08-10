#ifndef ARCHIVE_H
#define ARCHIVE_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CArchive
	{
		FILE *m_pFile = NULL;
		bool m_bStoring = false;

	public:

		CArchive(const string &FileName, bool bIn);

		~CArchive();

		void Close();

		bool IsValid()
		{
			return m_pFile != NULL;
		}
		
		template<typename T>
		CArchive &operator>>(T &Value)
		{
			fread((void*)(&Value), sizeof(T), 1, m_pFile);
			return *this;
		}

		CArchive &operator >> (string &Value)
		{
			unsigned int N(0);
			fread(&N, sizeof(N), 1, m_pFile);
			if (N > 0)
			{
				std::vector<char> content(N, 0);
				fread(&content[0], 1, N, m_pFile);
				std::string s(content.begin(), content.end());
				Value = s;
			}

			return *this;
		}

		template<typename T>
		CArchive &operator<<(T Value)
		{
			fwrite((void*)(&Value), sizeof(T), 1, m_pFile);
			return *this;
		}

		CArchive &operator<<(string Value)
		{
			unsigned int N((unsigned int)Value.size());
			fwrite(&N, sizeof(N), 1, m_pFile);

			if (Value.length() > 0)
			{
				fwrite(Value.c_str(), 1, N, m_pFile);
			}

			return *this;
		}

		bool IsStoring() const { return m_bStoring; }
	};
}
#endif //ARCHIVE_H