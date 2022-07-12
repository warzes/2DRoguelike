#pragma once

#include "Engine.h"
#include "stb_rect_pack.h"
#include "stb_truetype.h"

extern RenderTarget rt;
extern Sprite spr;

/* STBTTF: A quick and dirty SDL2 text renderer based on stb_truetype and stdb_rect_pack.
 * Benoit Favre 2019
 *
 * This header-only addon to the stb_truetype library allows to draw text with SDL2 from
 * TTF fonts with a similar API to SDL_TTF without the bloat.
 * The renderer is however limited by the integral positioning of SDL blit functions.
 * It also does not parse utf8 text and only prints ASCII characters.
 *
 * This code is public domain.
 */

struct STBTTF_Font  {
	stbtt_fontinfo* info;
	stbtt_packedchar* chars;
	SDL_Texture* atlas;
	int texture_size;
	float size;
	float scale;
	int ascent;
	int baseline;
} ;



extern STBTTF_Font* font;

/* Release the memory and textures associated with a font */
void STBTTF_CloseFont(STBTTF_Font* font);

/* Open a TTF font given a SDL abstract IO handler, for a given renderer and a given font size.
 * Returns NULL on failure. The font must be deallocated with STBTTF_CloseFont when not used anymore.
 * This function creates a texture atlas with prerendered ASCII characters (32-128).
 */
STBTTF_Font* STBTTF_OpenFontRW(SDL_Renderer* renderer, SDL_RWops* rw, float size);

/* Open a TTF font given a filename, for a given renderer and a given font size.
 * Convinience function which calls STBTTF_OpenFontRW.
 */
STBTTF_Font* STBTTF_OpenFont(SDL_Renderer* renderer, const char* filename, float size);

/* Draw some text using the renderer draw color at location (x, y).
 * Characters are copied from the texture atlas using the renderer SDL_RenderCopy function.
 * Since that function only supports integral coordinates, the result is not great.
 * Only ASCII characters (32 <= c < 128) are supported. Anything outside this range is ignored.
 */
void STBTTF_RenderText(SDL_Renderer* renderer, STBTTF_Font* font, float x, float y, const char* text);

/* Return the length in pixels of a text.
 * You can get the height of a line by using font->baseline.
 */
float STBTTF_MeasureText(STBTTF_Font* font, const char* text);
