#include "stdafx.h"
#include "GameData.h"
//-----------------------------------------------------------------------------
TileRender::TileRender(SDL_Rect tileSrcRect)
	: m_tileSrcRect(tileSrcRect)
{
}
//-----------------------------------------------------------------------------
TileRender TileRender::Create(TileRenderType type)
{
	if (type == TileRenderType::Player) return TileRender({0, 240, 16, 16});
	else if (type == TileRenderType::Glass) return TileRender({ 32, 288, 16, 16 });
	else if (type == TileRenderType::DungeonFloor) return TileRender({ 208, 96, 16, 16 });
	else if (type == TileRenderType::DungeonWall) return TileRender({ 0, 112, 16, 16 });
	else if (type == TileRenderType::Tree) return TileRender({ 192, 304, 16, 16 });
	else return TileRender( { 0, 0, 16, 16 });
}
//-----------------------------------------------------------------------------