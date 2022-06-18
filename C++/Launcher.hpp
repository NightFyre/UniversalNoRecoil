#pragma once
#include "helper.hpp"
#include "Console.hpp"
#include "DXWindow.hpp"
namespace UniCoil {

	class Launcher
	{
	public:
		explicit Launcher();
		~Launcher() noexcept = default;
		Launcher(Launcher const&) = delete;
		Launcher(Launcher&&) = delete;
		Launcher& operator=(Launcher const&) = delete;
		Launcher& operator=(Launcher&&) = delete;

		void InitStyle();							//	Window Style
		void Draw();								//	Main draw function
		void Menu();
		void MenuOptions();
	};

	class LauncherVariables
	{
	public:
		//	EXTERNAL PROCESS & WINDOW 
		HINSTANCE hInstance{};			//	Variable for Process Icon

		//	LAUNCHER
		bool m_LauncherRunning{};		//	
		bool m_ShowWindow{};			//	
		bool m_DemoWindow{};			//	

		//	MENU VARIABLES & FLAGS
		bool m_MainMenu{};
		bool m_MenuOptions{};

		// Rainbow Variables
		ImColor cRainbow;	
		ImVec2 BUTTONS{ 200, 30 };		//	Button Size
		ImVec4 m_CustomColors{};
		std::vector<float> cfgColors{};

		int selectedPRESET;
		const char* presets[3]{ "PRESET 1", "PRESET 2", "PRESET 3" };

		// Recoil Variables
		bool bRAPID;
		bool bRECOIL;
		int recoilStrength1;
		int recoilDelay1;
		int recoilStrength2;
		int recoilDelay2;
		int recoilStrength3;
		int recoilDelay3;
		int rapidFireDelay;

		//	INIT
		explicit LauncherVariables();
		~LauncherVariables() noexcept = default;
		LauncherVariables(LauncherVariables const&) = delete;
		LauncherVariables(LauncherVariables&&) = delete;
		LauncherVariables& operator=(LauncherVariables const&) = delete;
		LauncherVariables& operator=(LauncherVariables&&) = delete;
	};

	inline std::unique_ptr<Launcher> g_Launcher;
	inline std::unique_ptr<LauncherVariables> g_LauncherVariables;
}