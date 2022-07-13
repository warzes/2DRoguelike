#pragma once

#include "Engine.h"

namespace GameConstant
{
	constexpr auto SizeTileMap = 16;
	constexpr auto NumViewTileMap = 29;
	constexpr auto ViewMapSize = NumViewTileMap * SizeTileMap;

	constexpr auto NumberTileInMap = 100;
}

enum class TileRenderType
{
	Player,
	Glass,
	DungeonFloor,
	DungeonWall,
	Tree
};

class TileRender
{
public:
	TileRender() = default;
	TileRender(SDL_Rect tileSrcRect);

	static TileRender Create(TileRenderType type);

private:
	SDL_Rect m_tileSrcRect;
};

struct Tile
{

};

struct Map
{
	Tile tile[GameConstant::NumberTileInMap][GameConstant::NumberTileInMap];
};

struct Player
{

};

struct World
{
	Player player;
	Map map;
};