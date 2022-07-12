#pragma once

#if defined(__EMSCRIPTEN__)
const std::string FolderRoot = "";
#else
const std::string FolderRoot = "../";
#endif