#include "stdafx.h"
#include "Engine.h"

emrun site/game.html


@call emcc - std = c++20 - s USE_SDL = 2 - s USE_SDL_IMAGE = 2 - s SDL2_IMAGE_FORMATS = '["bmp","png"]' - s STB_IMAGE = 1 main.cpp Game.cpp Engine.cpp GameRender.cpp GameUpdate.cpp - o site / game.html --preload - file data - Os - Wall

// без SDL image


//-----------------------------------------------------------------------------
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
//-----------------------------------------------------------------------------
/*
размер видимой карты - 15х15 (или 11х11).
для каждого элемента своя рендертекстура. то есть например карта рендерится в квадрат 240х240, а например гуи поля боя в 640х480. это позволит делать ретро стиль карты, но при этом нормально выводить большие спрайты в бою или текст в диалогах.
*/
//-----------------------------------------------------------------------------
bool GameInit();
void GameUpdate(float deltaTime);
void GameRender();
void GameClose();
#if defined(__EMSCRIPTEN__)
inline void OnIterFrame()
{
	GameUpdate(currentEngine->GetDeltaTime());
	GameRender();
}
#endif
//-----------------------------------------------------------------------------
int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	Engine engine;

	constexpr auto getConfig = []() { return EngineCreateInfo
	{
		.windowSize = {800, 600},
		.windowTitle = "Game",
		.renderSize = {640, 480},
	}; };
	if (engine.Create(getConfig()))
	{
		if (GameInit())
		{
#if defined(__EMSCRIPTEN__)
			// void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
			//emscripten_set_main_loop(OnIterFrame, 60, 1);
			emscripten_set_main_loop(OnIterFrame, 0, 1);
#else
			while (engine.Update())
			{
				GameUpdate(engine.GetDeltaTime());
				GameRender();
			}
#endif
		}
		GameClose();
	}
	engine.Destroy();
	return 0;
}
//-----------------------------------------------------------------------------