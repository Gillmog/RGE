#ifndef ARCHIVE_H
#define ARCHIVE_H

#pragma once

#include "Core.h"

namespace Engine
{
	class CArchive
	{
		FILE *m_pFile = NULL;
		bool m_bStoring = false;;

	public:

		CArchive(const string &FileName, bool bIn);

		~CArchive();

		void Close();
		
		template<typename T>
		CArchive &operator>>(T &Value)
		{
			fread((void*)(&Value), sizeof(T), 1, m_pFile);
			return *this;
		}

		template<typename T>
		CArchive &operator<<(T Value)
		{
			fwrite((void*)(&Value), sizeof(T), 1, m_pFile);
			return *this;
		}

		bool IsStoring() const { return m_bStoring; }
	};
}
#endif //ARCHIVE_H