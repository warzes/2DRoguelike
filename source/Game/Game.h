#pragma once

#include "GameData.h"

class Game
{
public:
	bool Init();
	void Close();

	void Update(float deltaTime);
	void Render();

private:
	RenderTarget m_viewMap;
	Sprite m_tileset00;

	World* m_worldData;

	Sprite spr;
	Font font2;
};

extern Game* gGame;