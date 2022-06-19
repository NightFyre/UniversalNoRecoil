#include "helper.hpp"
#include "Console.hpp"
#include "DXWindow.hpp"
#include "Launcher.hpp"

void BackgroundWorker()
{
	using namespace UniCoil;
	while (g_Running) {
		g_Launcher->Loops();
		std::this_thread::sleep_for(1ms);
		std::this_thread::yield();
	}
	return;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	using namespace UniCoil;

	g_Console = std::make_unique<Console>();
#if DEVELOPER
	g_Console->Init();
#endif
	g_Profile = std::make_unique<Profile>();
	g_Profile->hInstance = hInstance;

	g_Window = std::make_unique<DXWindow>();
	g_Launcher = std::make_unique<Launcher>();
	g_Console->LoadCFG();

	std::thread UPDATE(BackgroundWorker);
	while (g_Running) {
		g_Window->UpdateWindow();
		std::this_thread::sleep_for(1ms);
		std::this_thread::yield();
	}

	UPDATE.join();
	g_Console->SaveCFG();
	g_Window->Exit();
#if DEVELOPER
	g_Console->Free();
#endif
	return 0;
}

