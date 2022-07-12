#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void GameUpdate(float deltaTime)
{
	if (currentEngine->KeyDown(GameKey::A))
		PrintLog("A down");
	if (currentEngine->KeyPress(GameKey::B))
		PrintLog("B press");
}
//-----------------------------------------------------------------------------