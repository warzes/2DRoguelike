#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
void GameRender()
{
	currentEngine->SetRenderTarget(rt);
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


	//STBTTF_RenderText(currentEngine->GetRenderer(), font, 50, 50, "This is a test");
	// render the atlas to check its content
	SDL_Rect dest = {0, 0, font->texture_size, font->texture_size };
	SDL_RenderCopy(currentEngine->GetRenderer(), font->atlas, &dest, &dest);
}
//-----------------------------------------------------------------------------