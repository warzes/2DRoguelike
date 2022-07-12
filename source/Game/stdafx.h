#pragma once

#pragma warning(push, 0)
#pragma warning(disable:4365)

#if defined(__EMSCRIPTEN__)
#	include <emscripten/emscripten.h>
#	include <SDL2/SDL.h>
#else
#	include <SDL2/SDL.h>
#endif

#include "stb_rect_pack.h"
#include "stb_truetype.h"

#include <chrono>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

#pragma warning(pop)