#include "stdafx.h"
#include "Game.h"
#define STB_RECT_PACK_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_rect_pack.h"
#include "stb_truetype.h"
//-----------------------------------------------------------------------------
RenderTarget rt;
Sprite spr;
Font font2;
//-----------------------------------------------------------------------------
bool GameInit()
{
	rt = currentEngine->CreateRenderTarget(480, 480);
#if defined(__EMSCRIPTEN__)
	spr = currentEngine->CreateSprite("data/floor.png");
//	font2 = currentEngine->CreateFont("OpenSans-Regular.ttf", 32);
#else
	spr = currentEngine->CreateSprite("../floor.png");
//	font2 = currentEngine->CreateFont("../OpenSans-Regular.ttf", 32);
#endif

	return true;
}
//-----------------------------------------------------------------------------
void GameClose()
{
	//currentEngine->DestroyResource(font2);
	//currentEngine->DestroyResource(rt);
	currentEngine->DestroyResource(spr);
}
//-----------------------------------------------------------------------------