#include "pch.h"
#include "directx11.h"

#pragma comment(lib, "DXGI") 
#pragma comment(lib, "D3D11")

#define DX_RELEASE(ptr) if (ptr) { ptr->Release(); ptr = nullptr; }

namespace {
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> context = nullptr;
	ComPtr<IDXGISwapChain> swap_chain = nullptr;
	ComPtr<ID3D11RenderTargetView> back_buffer = nullptr;
}

bool directx11::initialize() {
	if(!window::handle) return false;

	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc = {};
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = window::handle;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.Windowed = !window::is_exclusive_fullscreen();

	UINT creation_flags = 0;
#if defined(REPORT_DX_WARNINGS)
	creation_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creation_flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swap_chain_desc,
		&swap_chain,
		&device,
		nullptr,
		&context
	);

	ID3D11Texture2D *back_buffer_texture;
	result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&back_buffer_texture);
	if (FAILED(result)) return false;

	result = device->CreateRenderTargetView(back_buffer_texture, nullptr, &back_buffer);
	if (FAILED(result)) return false;

	D3D11_TEXTURE2D_DESC texture_desc;
	back_buffer_texture->GetDesc(&texture_desc);
	back_buffer_texture->Release();

	context->OMSetRenderTargets(1, back_buffer.GetAddressOf(), nullptr);
	D3D11_VIEWPORT viewport = { 0 };
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = static_cast<float>(texture_desc.Width);
	viewport.Height = static_cast<float>(texture_desc.Height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	context->RSSetViewports(1, &viewport);

	return true; 
}

void directx11::cleanup() {
	DX_RELEASE(back_buffer);
	DX_RELEASE(swap_chain);
	DX_RELEASE(context);
	DX_RELEASE(device);
}

void directx11::Render() {
	float color[4] = { 1.0f,0.8f,0.5f,1.0f }; // RGBA
	context->ClearRenderTargetView(back_buffer.Get(), color);

	swap_chain->Present(1, 0);
}