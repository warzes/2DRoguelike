#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void Game::Render()
{
	// Set Map View Render Target
	gEngine->SetRenderTarget(m_viewMap);
	//for (int x = 0; x < 15; x++)
	//{
	//	for (int y = 0; y < 15; y++)
	//	{
	//		const int posX = x * spr.width;
	//		const int posY = y * spr.height;
	//		gEngine->Draw(spr, posX, posY);
	//	}
	//}

	// Set Main Render Target
	gEngine->SetRenderTarget({100,100,255,255});
	gEngine->Draw(m_viewMap, 0, 0);

	gEngine->Draw(font2, L"~Текст работает 123 Hello~", 50, 50, {255,0,60,255});
	gEngine->Draw(font2, 50, 70);
}
//-----------------------------------------------------------------------------