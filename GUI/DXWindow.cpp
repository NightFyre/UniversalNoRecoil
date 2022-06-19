#include "DXWindow.hpp"
#include "Launcher.hpp"
#include "resource.h"
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace UniCoil {
	DXWindow::DXWindow()
	{
		Initialize();
	}

	void DXWindow::Initialize()
	{
        wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), LoadIcon(g_Profile->hInstance, MAKEINTRESOURCE(IDI_ICON1)),
            NULL, NULL, NULL, _T("NightFyre DirextX Window"),
            LoadIcon(g_Profile->hInstance, MAKEINTRESOURCE(IDI_APPLICATION))
        };

        ::RegisterClassEx(&wc);
        hwnd = ::CreateWindow(wc.lpszClassName, _T("UniCoil"), WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
        if (!CreateDeviceD3D(hwnd)) {
            CleanupDeviceD3D();
            ::UnregisterClass(wc.lpszClassName, wc.hInstance);
            return;
        }
        ::ShowWindow(hwnd, SW_HIDE);
        ::UpdateWindow(hwnd);



        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;        // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        io.IniFilename = NULL;                                     // Disable Ini File

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX11_Init(pd3dDevice, pd3dDeviceContext);
	}

    void DXWindow::UpdateWindow()
    {
        MSG msg;
        while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                g_Launcher->m_LauncherRunning = FALSE;
        }

        if (!g_Launcher->m_LauncherRunning) {
            g_Running = FALSE;
            return;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //  RENDER OUR CUSTOM WINDOW HERE
        //  - Passing our boolean to close when done
        g_Launcher->Draw();

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        pd3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
        pd3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        pSwapChain->Present(1, 0); // Present with vsync
    }

    bool DXWindow::CreateDeviceD3D(HWND hWnd)
    {
        // Setup swap chain
        DXGI_SWAP_CHAIN_DESC sd;
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        UINT createDeviceFlags = 0;
        D3D_FEATURE_LEVEL featureLevel;
        const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
        if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &pSwapChain, &pd3dDevice, &featureLevel, &pd3dDeviceContext) != S_OK)
            return false;

        CreateRenderTarget();
        return true;
    }

    void DXWindow::CleanupDeviceD3D()
    {
        CleanupRenderTarget();
        if (pSwapChain) { pSwapChain->Release(); pSwapChain = NULL; }
        if (pd3dDeviceContext) { pd3dDeviceContext->Release(); pd3dDeviceContext = NULL; }
        if (pd3dDevice) { pd3dDevice->Release(); pd3dDevice = NULL; }
    }

    void DXWindow::CreateRenderTarget()
    {
        ID3D11Texture2D* pBackBuffer;
        pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
        pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
        pBackBuffer->Release();
    }

    void DXWindow::CleanupRenderTarget()
    {
        if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
    }


    void DXWindow::Exit()
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        g_Window->CleanupDeviceD3D();
        DestroyWindow(g_Window->hwnd);
        UnregisterClass(g_Window->wc.lpszClassName, g_Window->wc.hInstance);
    }

    LRESULT WINAPI DXWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        switch (msg)
        {
        case WM_SIZE:
            if (g_Window->pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
            {
                g_Window->CleanupRenderTarget();
                g_Window->pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                g_Window->CreateRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
        case WM_DPICHANGED:
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
            {
                const RECT* suggested_rect = (RECT*)lParam;
                ::SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
            }
            break;
        }
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }
}