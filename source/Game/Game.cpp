#include "stdafx.h"
#include "Game.h"
//-----------------------------------------------------------------------------
Game* gGame = nullptr;
//-----------------------------------------------------------------------------
bool Game::Init()
{
	gGame = this;
	m_viewMap = gEngine->CreateRenderTarget(GameConstant::ViewMapSize, GameConstant::ViewMapSize);
	m_tileset00 = gEngine->CreateSprite(FolderRoot + "data/Textures-16.png");

	m_worldData = new World();

	spr = gEngine->CreateSprite(FolderRoot + "data/floor.png");
	font2 = gEngine->CreateFont(FolderRoot + "data/OpenSans-Regular.ttf", 32);

	return true;
}
//-----------------------------------------------------------------------------
void Game::Close()
{
	delete m_worldData;
	gEngine->DestroyResource(font2);
	gEngine->DestroyResource(m_viewMap);
	gEngine->DestroyResource(spr);
	gEngine->DestroyResource(m_tileset00);
	gGame = nullptr;
}
//-----------------------------------------------------------------------------