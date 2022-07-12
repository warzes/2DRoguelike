#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
RenderTarget rt;
Sprite spr;
Font font2;
//-----------------------------------------------------------------------------
bool GameInit()
{
	rt = currentEngine->CreateRenderTarget(480, 480);
	spr = currentEngine->CreateSprite(FolderRoot + "data/floor.png");
	font2 = currentEngine->CreateFont(FolderRoot + "data/OpenSans-Regular.ttf", 32);

	return true;
}
//-----------------------------------------------------------------------------
void GameClose()
{
	currentEngine->DestroyResource(font2);
	currentEngine->DestroyResource(rt);
	currentEngine->DestroyResource(spr);
}
//-----------------------------------------------------------------------------