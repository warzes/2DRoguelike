#include "stdafx.h"
#include "Engine.h"
#include "Game.h"
//-----------------------------------------------------------------------------
#if defined(_MSC_VER)
#pragma comment( lib, "SDL2.lib" )
#pragma comment( lib, "SDL2main.lib" )
#endif
//-----------------------------------------------------------------------------
/*
размер видимой карты - 15х15 (или 11х11).
для каждого элемента своя рендертекстура. то есть например карта рендерится в квадрат 240х240, а например гуи поля боя в 640х480. это позволит делать ретро стиль карты, но при этом нормально выводить большие спрайты в бою или текст в диалогах.
*/
//-----------------------------------------------------------------------------

#if defined(__EMSCRIPTEN__)
void UpdateDrawFrame()
{
	if (!gEngine->Update()) emscripten_cancel_main_loop();
	gGame->Update(gEngine->GetDeltaTime());
	gGame->Render();
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
		Game game;

		if (game.Init())
		{
#if defined(__EMSCRIPTEN__)
			emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
			while (engine.Update())
			{
				game.Update(engine.GetDeltaTime());
				game.Render();
			}
#endif
		}
		game.Close();
	}
	engine.Destroy();
	return 0;
}
//-----------------------------------------------------------------------------