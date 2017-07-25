// BeyondTheBounds.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CoreBase.h"
#include "Application.h"
#include "GameApplication.h"

int main()
{
	shared_ptr<CGameApplication> pApplication = make_shared<CGameApplication>(Engine::CPoint(80, 26));

	pApplication->EventLoop([=]() 
	{
		
	});

    return 0;
}

