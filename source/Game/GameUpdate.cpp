#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void Game::Update(float deltaTime)
{
	if (gEngine->KeyDown(GameKey::A))
		PrintLog("A down");
	if (gEngine->KeyPress(GameKey::B))
		PrintLog("B press");
}
//-----------------------------------------------------------------------------