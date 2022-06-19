#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define DEVELOPER 0
#include <windows.h>
#include <Psapi.h>
#include <memory>
#include <iostream>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <STDLIB.H>
#include <string>
#include <thread>
#include <chrono>
#include <TlHelp32.h>
#include <vector>

//	DirectX
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

//	ImGui
#include "../libs/ImGui/imgui.h"
#include "../libs/ImGui/imgui_internal.h"
#include "../libs/ImGui/imgui_impl_win32.h"
#include "../libs/ImGui/imgui_impl_dx11.h"

namespace UniCoil {
	using namespace std::chrono_literals;

	inline HMODULE g_Module{};
	inline LPCWSTR g_ModuleName{};
	inline std::atomic_bool g_Running = TRUE;
}