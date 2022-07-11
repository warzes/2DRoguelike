#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void GameUpdate(float deltaTime)
{
	if (currentEngine->KeyDown(GameKey::A))
		SDL_Log("A down");
	if (currentEngine->KeyPress(GameKey::B))
		SDL_Log("B press");
}
//-----------------------------------------------------------------------------