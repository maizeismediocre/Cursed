/****************************************************************************
GFC - Games Fundamental Classes version 2.70
Copyright (C) 2009-2022 Jarek Francik, Kingston University London

This work is licensed under a Creative Commons Attribution-ShareAlike 4.0 International License:
http://creativecommons.org/licenses/by-sa/4.0/

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Created by Jarek Francik
jarek@kingston.ac.uk
****************************************************************************/
#pragma once


#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#endif

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#include <windows.h>

#define WINDOWS_IGNORE_PACKING_MISMATCH	  // Necessary for Visual Studio 2019 to work with Win32 (required by SDL)

#undef M_PI

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef GFC_VERSION
#define GFC_VERSION	270
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_net.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_syswm.h"

#ifndef max
#define max(x, y)	((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef RAD2DEG
#define RAD2DEG(x)	((float)(x) * 180.0f / (float)M_PI)
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)M_PI / 180.0f)
#endif

#include <sstream>

#ifdef _USRDLL
#define EXT_DECL		__declspec(dllexport)
#else
#define EXT_DECL		__declspec(dllimport)
#endif



#ifndef GFC_VERSION
#define GFC_VERSION	160
#endif

#ifndef max
#define max(x, y)	((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)	((x) < (y) ? (x) : (y))
#endif

#ifndef RAD2DEG
#define RAD2DEG(x)	((float)(x) * 180.0f / (float)M_PI)
#endif

#ifndef DEG2RAD
#define DEG2RAD(x)  ((float)(x) * (float)M_PI / 180.0f)
#endif

#include <sstream>

#ifdef _USRDLL
   #define EXT_DECL		__declspec(dllexport)
#else
   #define EXT_DECL		__declspec(dllimport)
#endif


#include "Color.h"
#include "Vector.h"
#include "Rectangle.h"
#include "GameApp.h"
#include "Game.h"
#include "Graphics.h"
#include "Sprite.h"
#include "SpriteRect.h"
#include "SpriteOval.h"
#include "SpriteText.h"
#include "SpriteContainer.h"
#include "Sound.h"
#include "Font.h"


