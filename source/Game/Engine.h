#pragma once

struct Color
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;
};

struct RenderTarget
{
	SDL_Texture* target = nullptr;
	int width = 0;
	int height = 0;
};

struct Sprite
{
	SDL_Texture* texture = nullptr;
	int width = 0;
	int height = 0;
	std::string fileName;
};

enum class GameKey
{
	A,
	B,
	C,
	X,
	Y,

	UP,
	DOWN,
	LEFT,
	RIGHT
};
constexpr size_t MaxGameKey = 9;

struct EngineCreateInfo
{
	SDL_Point windowSize = { 0 };
	const char* windowTitle = nullptr;

	SDL_Point renderSize = { 0 };
};

class Engine
{
public:
	bool Create(const EngineCreateInfo& createInfo);
	void Destroy();

	bool Update();

	float GetDeltaTime() const;

	RenderTarget CreateRenderTarget(int width, int height) const;
	Sprite CreateSprite(const std::string& fileName, bool inCaches = true);

	void DestroyResource(RenderTarget& rt) const;
	void DestroyResource(Sprite& sprite);
		
	void SetRenderTarget(const Color& colorBackground = { 0,0,0,255 }) const;
	void SetRenderTarget(const RenderTarget& rt, const Color& colorBackground = { 0,0,0,255 }) const;

	void Draw(const RenderTarget& rt, int posX, int posY) const;
	void Draw(const Sprite& sprite, int posX, int posY) const;

	bool KeyDown(GameKey key) const;
	bool KeyPress(GameKey key);

private:
	void setKey(SDL_Keycode sdlKey, GameKey gameKey, bool state);
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Event m_sdlEvent = {};

	std::unordered_map<std::string, Sprite> m_spriteCache;

	std::chrono::steady_clock::time_point m_startTime;
	int64_t m_frameTimeCurrent = 0;
	int64_t m_frameTimeLast = 0;
	int64_t m_frameTimeDelta = 0;
	float m_deltaTime = 0.0f;

	bool m_keyDown[MaxGameKey] = { false };
	bool m_keyPress[MaxGameKey] = { false };

	// чтобы не ругалось
	struct
	{
		char c[2];
	} m_unused;
};

extern Engine* currentEngine;