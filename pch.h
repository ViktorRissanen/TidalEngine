#pragma once

// win
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <wrl/client.h>

// dx11
#include <dxgi.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d11shader.h>
#include <DirectXMath.h>
#define REPORT_DX_WARNINGS
using Microsoft::WRL::ComPtr;

// cstd
#include <cassert>
#include <cmath>
#include <cstdlib>

// std
#include "string"
//TODO: add additional libraries here: imgui, assimp, entt, nlohmann/json, etc.

#include "window.h"