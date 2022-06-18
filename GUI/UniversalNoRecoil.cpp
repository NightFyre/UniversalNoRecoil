#include "helper.hpp"
#include "Console.hpp"
#include "DXWindow.hpp"
#include "Launcher.hpp"

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WinMain(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	using namespace UniCoil;

	g_Console = std::make_unique<Console>();
#if DEVELOPER
	g_Console->Init();
#endif
	g_LauncherVariables = std::make_unique<LauncherVariables>();
	g_LauncherVariables->hInstance = hInstance;
	//g_Console->LoadCFG();

	g_Window = std::make_unique<DXWindow>();
	g_Launcher = std::make_unique<Launcher>();

	while (g_Running) {
		g_Window->UpdateWindow();
		std::this_thread::sleep_for(1ms);
		std::this_thread::yield();
	}

	g_Console->SaveCFG();
	g_Window->Exit();
#if DEVELOPER
	g_Console->Free();
#endif
	return 0;
}

