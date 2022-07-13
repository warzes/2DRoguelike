#pragma once

void PrintLog(const std::string& text);
void ErrorLog(const std::string& text);

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

constexpr uint32_t firstCharENG = ' ';
constexpr uint32_t charCountENG = '~' - ' ' + 1;
constexpr uint32_t firstCharRUS = 0x400;
constexpr uint32_t charCountRUS = 0x452 - 0x400;

struct Font
{
	int size = 0;
	uint32_t atlasSize = 256;

	SDL_Texture* atlas = nullptr;

	stbtt_fontinfo info;
	stbtt_packedchar charInfo[charCountENG + charCountRUS];

	float scale = 0.0f;
	int ascent = 0;
	int baseline = 0;
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
	Font CreateFont(const std::string& fileName, int fontSize);

	void DestroyResource(RenderTarget& rt) const;
	void DestroyResource(Sprite& sprite);
	void DestroyResource(Font& font);
		
	void SetRenderTarget(const Color& colorBackground = { 0,0,0,255 }) const;
	void SetRenderTarget(const RenderTarget& rt, const Color& colorBackground = { 0,0,0,255 }) const;

	void Draw(const RenderTarget& rt, int posX, int posY) const;
	void Draw(const Sprite& sprite, int posX, int posY) const;
	void Draw(const Sprite& sprite, int posX, int posY, const SDL_Rect& rect) const;
	void Draw(const Font& font, const std::wstring& text, int posX, int posY, const Color& color = { 0,0,0,255 }) const;
	void Draw(const Font& fontAtlas, int posX, int posY, const Color& color = { 0,0,0,255 }) const; // отрисовка атласа

	/* Return the length in pixels of a text.
	 * You can get the height of a line by using font->baseline.*/
	float MeasureText(const Font& font, const std::wstring& text) const;

	bool KeyDown(GameKey key) const;
	bool KeyPress(GameKey key);

private:
	void setKey(bool state);
	size_t getFontIndex(int ch) const;
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Event m_sdlEvent = {};

	std::unordered_map<std::string, Sprite> m_spriteCache;
	std::unordered_map<std::string, Font> m_fontCache;

	std::map<SDL_Keycode, GameKey> m_keyMapping;

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

extern Engine* gEngine;