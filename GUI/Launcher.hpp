#pragma once
#include "helper.hpp"
#include "Console.hpp"
#include "DXWindow.hpp"
namespace UniCoil {

	struct Config {
		int   key1;
		int   recoilStrength[3];
		int   recoilDelay[3];
		int   rapidFireDelay[3];
		bool  recoilADSFlag[3];
		bool  rapidADSFlag[3];
	};

	class Launcher
	{
	public:
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
		void Loops();
	};

	class Profile
	{
	public:
		Config config{};
		HINSTANCE hInstance{};			//	Variable for Process Icon
		ImVec4 m_CustomColors{};

		//	
		int selectedPRESET;
		int savePRESET;
		const char* presets[4]{ "CONFIGURATION", "PRESET 1", "PRESET 2", "PRESET 3" };
		const char* save_slots[3]{ "1", "2", "3" };

		// Recoil Variables
		bool bRECOIL;
		bool bRECOIL_SETTINGS;
		bool bADSFLAG_RECOIL;
		int recoilStrength;
		int recoilDelay;

		bool bRAPID;
		bool bRAPID_SETTINGS;
		bool bADSFLAG_RAPID;
		int rapidFireDelay;
		
		//	INIT
		explicit Profile();
		~Profile() noexcept = default;
		Profile(Profile const&) = delete;
		Profile(Profile&&) = delete;
		Profile& operator=(Profile const&) = delete;
		Profile& operator=(Profile&&) = delete;

		void UniCoil(int Speed, int Delay, bool flag = FALSE);
		void RapidFire(int delay);
	};

	inline std::unique_ptr<Launcher> g_Launcher;
	inline std::unique_ptr<Profile> g_Profile;
}