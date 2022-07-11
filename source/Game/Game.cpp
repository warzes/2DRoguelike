#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
RenderTarget rt;
Sprite spr;
//-----------------------------------------------------------------------------
bool GameInit()
{
	rt = currentEngine->CreateRenderTarget(480, 480);
	spr = currentEngine->CreateSprite("../floor.png");

	return true;
}
//-----------------------------------------------------------------------------
void GameClose()
{
	currentEngine->DestroyResource(rt);
	currentEngine->DestroyResource(spr);
}
//-----------------------------------------------------------------------------