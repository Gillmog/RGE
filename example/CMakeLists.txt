CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

INCLUDE(../librge/cmake/Config.cmake)

ADD_RGE(../librge/)

SET(GAME_SOURCE
	src/main.cpp
	src/GameApplication.h
	src/GameApplication.cpp
)

SETUP_APP(Example ${GAME_SOURCE})