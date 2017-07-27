#include "RGE/Core.h"
#include "RGE/Application.h"
#include "GameApplication.h"

int main()
{  
    shared_ptr<CGameApplication> pApplication = make_shared<CGameApplication>(Engine::CPoint(80, 26));
    
    pApplication->EventLoop([=]() 
    {
	
    });

    return 0;
}