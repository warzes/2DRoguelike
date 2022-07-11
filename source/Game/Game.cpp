#include "stdafx.h"
#include "Game.h"
#include "Engine.h"
//-----------------------------------------------------------------------------
Engine* currentEngine = nullptr;
//-----------------------------------------------------------------------------
RenderTarget rt;
Sprite spr;
//-----------------------------------------------------------------------------
bool GameInit(Engine* engine)
{
	currentEngine = engine;

	rt = currentEngine->CreateRenderTarget(480, 480);
	spr = currentEngine->CreateSprite("../floor.png");


	return true;
}
//-----------------------------------------------------------------------------
void GameUpdate(float deltaTime)
{
	if (currentEngine->KeyDown(GameKey::A))
		SDL_Log("A down");
	if (currentEngine->KeyPress(GameKey::B))
		SDL_Log("B press");
}
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
void GameClose()
{
	currentEngine->DestroyResource(rt);
	currentEngine->DestroyResource(spr);
	currentEngine = nullptr;
}
//-----------------------------------------------------------------------------