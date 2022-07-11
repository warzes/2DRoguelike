#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void GameRender()
{
	currentEngine->SetRenderTarget(rt, { 255,0,120,255 });
	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{
			const int posX = x * spr.width;
			const int posY = y * spr.height;
			currentEngine->Draw(spr, posX, posY);
		}
	}

	currentEngine->SetRenderTarget();
	currentEngine->Draw(rt, 0, 0);
}
//-----------------------------------------------------------------------------