add_library(RGE
	RGE/Input.h
	RGE/Input.cpp
	RGE/Graphics.h
	RGE/Graphics.cpp
	RGE/Geometry.h
	RGE/Geometry.cpp
	RGE/Core.h
	RGE/Application.h
	RGE/Application.cpp
	RGE/Archive.cpp
	RGE/Archive.h
	RGE/UI.cpp
	RGE/UI.h
	RGE/Sprite.cpp
	RGE/Sprite.h
)

IF (WIN32)
	add_definitions(-DRGE_WIN)
ENDIF()

if (UNIX)
	add_definitions(-DRGE_UNIX)
ENDIF()