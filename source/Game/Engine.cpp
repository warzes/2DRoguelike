#include "stdafx.h"
#include "Engine.h"
#pragma warning(push, 0)
#pragma warning(disable:5045)
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#pragma warning(pop)
//-----------------------------------------------------------------------------
Engine* currentEngine = nullptr;
//-----------------------------------------------------------------------------
bool Engine::Create(const EngineCreateInfo& createInfo)
{
	if (createInfo.windowSize.x == 0 || createInfo.windowSize.y == 0) return false;
	if (createInfo.windowTitle == nullptr) return false;

	SDL_Log("SDL Init");
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");

	SDL_Log("SDL create window");
	m_window = SDL_CreateWindow(createInfo.windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, createInfo.windowSize.x, createInfo.windowSize.y, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	if (!m_window)
		return false;

	SDL_Log("SDL create renderer");
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_renderer)
		return false;

	SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND); // TODO: ????

	if (createInfo.renderSize.x != 0 && createInfo.renderSize.y != 0)
		SDL_RenderSetLogicalSize(m_renderer, createInfo.renderSize.x, createInfo.renderSize.y);

	m_startTime = std::chrono::high_resolution_clock::now();

	// заполнение клавиш (должно быть идентично порядку в GameKey
	// TODO: из файла
	m_keyMapping[SDLK_z] = GameKey::A;
	m_keyMapping[SDLK_x] = GameKey::B;
	m_keyMapping[SDLK_c] = GameKey::C;
	m_keyMapping[SDLK_a] = GameKey::X;
	m_keyMapping[SDLK_s] = GameKey::Y;
	m_keyMapping[SDLK_UP] = GameKey::UP;
	m_keyMapping[SDLK_DOWN] = GameKey::DOWN;
	m_keyMapping[SDLK_LEFT] = GameKey::LEFT;
	m_keyMapping[SDLK_RIGHT] = GameKey::RIGHT;

	SDL_Log("Engine Init Success");
	currentEngine = this;
	return true;
}
//-----------------------------------------------------------------------------
void Engine::Destroy()
{
	currentEngine = nullptr;
	for (auto it = m_spriteCache.begin(); it != m_spriteCache.end(); it++)
		SDL_DestroyTexture(it->second.texture);
	m_spriteCache.clear();

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
//-----------------------------------------------------------------------------
bool Engine::Update()
{
	constexpr float MicrosecondsToSeconds = 1.0f / 1000000.0f;
	const auto curTime = std::chrono::high_resolution_clock::now();
	m_frameTimeCurrent = std::chrono::duration_cast<std::chrono::microseconds>(curTime - m_startTime).count();
	m_frameTimeDelta = m_frameTimeCurrent - m_frameTimeLast;
	m_frameTimeLast = m_frameTimeCurrent;
	m_deltaTime = static_cast<float>(m_frameTimeDelta) * MicrosecondsToSeconds;

	SDL_RenderPresent(m_renderer);

	while (SDL_PollEvent(&m_sdlEvent))
	{
		switch (m_sdlEvent.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			setKey(true);
			break;
		case SDL_KEYUP:
			setKey(false);
			break;
		}
	}

	return true;
}
//-----------------------------------------------------------------------------
float Engine::GetDeltaTime() const
{
	return m_deltaTime;
}
//-----------------------------------------------------------------------------
RenderTarget Engine::CreateRenderTarget(int width, int height) const
{
	RenderTarget rt;
	rt.width = width;
	rt.height = height;
	rt.target = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(rt.target, SDL_BLENDMODE_BLEND); // TODO: ????
	return rt;
}
//-----------------------------------------------------------------------------
Sprite Engine::CreateSprite(const std::string& fileName, bool inCaches)
{
	if (inCaches && m_spriteCache.find(fileName) != m_spriteCache.end() && m_spriteCache[fileName].texture)
	{
		return m_spriteCache[fileName];
	}
	else
	{
		Sprite sprite;
		sprite.fileName = fileName;
#if 1
		int channels;
		stbi_uc* image = stbi_load(fileName.c_str(), &sprite.width, &sprite.height, &channels, STBI_default);
		const Uint32 fmt = channels == 3 ? SDL_PIXELFORMAT_RGB24 : SDL_PIXELFORMAT_RGBA32;
		const int pitch = sprite.width * channels;
		sprite.texture = SDL_CreateTexture(m_renderer, fmt, SDL_TEXTUREACCESS_STATIC, sprite.width, sprite.height);
		SDL_UpdateTexture(sprite.texture, nullptr, (const void*)image, pitch);
		stbi_image_free(image);
#else
		SDL_Surface* loadedSurface = LoadImage(fileName.c_str());		
		sprite.texture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		sprite.width = loadedSurface->w;
		sprite.height = loadedSurface->h;
		SDL_FreeSurface(loadedSurface);
#endif

		if (inCaches) 
			m_spriteCache[fileName] = sprite;

		return sprite;
	}
}
//-----------------------------------------------------------------------------
void Engine::DestroyResource(RenderTarget& rt) const
{
	rt.width = 0;
	rt.height = 0;
	SDL_DestroyTexture(rt.target);
	rt.target = nullptr;
}
//-----------------------------------------------------------------------------
void Engine::DestroyResource(Sprite& sprite)
{
	sprite.width = 0;
	sprite.height = 0;
	if (m_spriteCache.find(sprite.fileName) == m_spriteCache.end()) // в кеше спрайты не удаляются
		SDL_DestroyTexture(sprite.texture);
	sprite.fileName = "";
	sprite.texture = nullptr;
}
//-----------------------------------------------------------------------------
void Engine::SetRenderTarget(const Color& colorBackground) const
{
	SDL_SetRenderTarget(m_renderer, nullptr);
	SDL_SetRenderDrawColor(m_renderer, colorBackground.r, colorBackground.g, colorBackground.b, colorBackground.a);
	SDL_RenderClear(m_renderer);
}
//-----------------------------------------------------------------------------
void Engine::SetRenderTarget(const RenderTarget& rt, const Color& colorBackground) const
{
	SDL_SetRenderTarget(m_renderer, rt.target);
	SDL_SetRenderDrawColor(m_renderer, colorBackground.r, colorBackground.g, colorBackground.b, colorBackground.a);
	SDL_RenderClear(m_renderer);
}
//-----------------------------------------------------------------------------
void Engine::Draw(const RenderTarget& rt, int posX, int posY) const
{
	const SDL_Rect dst = {posX, posY, rt.width, rt.height};
	SDL_RenderCopy(m_renderer, rt.target, nullptr, &dst);
}
//-----------------------------------------------------------------------------
void Engine::Draw(const Sprite& sprite, int posX, int posY) const
{
	const SDL_Rect dst = { posX, posY, sprite.width, sprite.height };
	SDL_RenderCopy(m_renderer, sprite.texture, nullptr, &dst);
}
//-----------------------------------------------------------------------------
bool Engine::KeyDown(GameKey key) const
{
	return m_keyDown[static_cast<size_t>(key)];
}
//-----------------------------------------------------------------------------
bool Engine::KeyPress(GameKey key)
{
	if (!KeyDown(key) || m_keyPress[static_cast<size_t>(key)]) return false;

	m_keyPress[static_cast<size_t>(key)] = true;
	return true;
}
//-----------------------------------------------------------------------------
void Engine::setKey(bool state)
{
	auto it = m_keyMapping.find(m_sdlEvent.key.keysym.sym);
	if (it != m_keyMapping.end())
	{
		const size_t id = static_cast<size_t>(it->second);

		m_keyDown[id] = state;
		if (!state) m_keyPress[id] = false;
	}
}
//-----------------------------------------------------------------------------