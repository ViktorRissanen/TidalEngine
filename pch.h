#pragma once

// win
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;

// cstd
#include <cassert>
#include <cmath>
#include <cstdlib>

// std
#include "string"
//TODO: add additional libraries here: imgui, assimp, entt, nlohmann/json, etc.