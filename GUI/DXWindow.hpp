#pragma once
#include "helper.hpp"
namespace UniCoil {
	class DXWindow
	{
	public:
		ID3D11Device* pd3dDevice{};
		ID3D11DeviceContext* pd3dDeviceContext{};
		IDXGISwapChain* pSwapChain{};
		ID3D11RenderTargetView* mainRenderTargetView{};
		WNDCLASSEX wc{};
		HWND hwnd{};
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		explicit DXWindow();
		~DXWindow() noexcept = default;

		DXWindow(DXWindow const&) = delete;
		DXWindow(DXWindow&&) = delete;
		DXWindow& operator=(DXWindow const&) = delete;
		DXWindow& operator=(DXWindow&&) = delete;

		void Initialize();
		bool CreateDeviceD3D(HWND hWnd);
		void CleanupDeviceD3D();
		void CreateRenderTarget();
		void CleanupRenderTarget();
		void Exit();

		//	MENU LOOPS
		void UpdateWindow();
		static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
	inline std::unique_ptr<DXWindow> g_Window;
}