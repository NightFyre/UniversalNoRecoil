#include "Console.hpp"
#include <fstream>
#include "Launcher.hpp"

namespace UniCoil {

	Console::Console() {
		return;
	}

	void Console::Init() {
		AllocConsole();
		g_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
		g_hWnd = GetConsoleWindow();
		freopen_s(&stream_in, "CONIN$", "r", stdin);
		freopen_s(&stream_out, "CONOUT$", "w", stdout);
		freopen_s(&stream_error, "CONOUT$", "w", stderr);
		SetConsoleTitleA("NightFyre Launcher - Debug Console");
		ShowWindow(g_hWnd, SW_SHOW);
		return;
	}

	void Console::printdbg(const char* Text, int Color, ...)
	{
		SetConsoleTextAttribute(g_Handle, Color);
		va_list arg;
		va_start(arg, Color);
		vfprintf(stream_out, Text, arg);
		va_end(arg);
		SetConsoleTextAttribute(g_Handle, 15);
		return;
	}

	void Console::scandbg(const char* Text, ...)
	{
		va_list arg;
		va_start(arg, Text);
		vfscanf(stream_in, Text, arg);
		va_end(arg);
		return;
	}

	void Console::SaveCFG()
	{
		std::ofstream fout;
		fout.open("settings.ini", std::ios::trunc);
		fout << "MENU THEME\n";
		fout << "//Colors range from 0 - 255\n";
		fout << ("COLORR =" + std::to_string(g_Profile->m_CustomColors.x * 255)) + "\n";
		fout << ("COLORG =" + std::to_string(g_Profile->m_CustomColors.y * 255)) + "\n";
		fout << ("COLORB =" + std::to_string(g_Profile->m_CustomColors.z * 255)) + "\n";
		fout << ("COLORA =" + std::to_string(g_Profile->m_CustomColors.w * 255)) + "\n\n";

		fout << "Toggle Keys\n";
		fout << "// 1 for Numpad keys | 2 for Function Keys\n";
		fout << "keys = 1\n\n";

		fout << "Preset1\n";
		fout << "recoilStrength1 =" + std::to_string(g_Profile->config.recoilStrength[0]) + "\n";
		fout << "recoilDelay1 =" + std::to_string(g_Profile->config.recoilDelay[0]) + "\n";
		fout << "recoilADSFlag1 =" + std::to_string(g_Profile->config.recoilADSFlag[0]) + "\n";
		fout << "rapidFireDelay1 =" + std::to_string(g_Profile->config.rapidFireDelay[0]) + "\n";
		fout << "rapidADSFlag1 =" + std::to_string(g_Profile->config.rapidADSFlag[0]) + "\n\n";

		fout << "Preset2\n";
		fout << "recoilStrength2 =" + std::to_string(g_Profile->config.recoilStrength[1]) + "\n";
		fout << "recoilDelay2 =" + std::to_string(g_Profile->config.recoilDelay[1]) + "\n";
		fout << "recoilADSFlag2 =" + std::to_string(g_Profile->config.recoilADSFlag[1]) + "\n";
		fout << "rapidFireDelay2 =" + std::to_string(g_Profile->config.rapidFireDelay[1]) + "\n\n";
		fout << "rapidADSFlag2 =" + std::to_string(g_Profile->config.rapidADSFlag[2]) + "\n\n";

		fout << "Preset3\n";
		fout << "recoilStrength3 =" + std::to_string(g_Profile->config.recoilStrength[2]) + "\n";
		fout << "recoilDelay3 =" + std::to_string(g_Profile->config.recoilDelay[2]) + "\n";
		fout << "recoilADSFlag3 =" + std::to_string(g_Profile->config.recoilADSFlag[2]) + "\n";
		fout << "rapidFireDelay3 =" + std::to_string(g_Profile->config.rapidFireDelay[2]) << std::endl;
		fout << "rapidADSFlag3 =" + std::to_string(g_Profile->config.rapidADSFlag[2]) + "\n\n";
		fout.close();
		return;
	}

	void Console::LoadCFG()
	{
		std::ifstream fin;
		std::string Word;
		
		//	Open config file
		fin.open("settings.ini", std::ifstream::in);

		// Read line by line until end of file is reached
		while (getline(fin, Word)) {
			
			//	Retrieve contents after '='
			std::istringstream sin(Word.substr(Word.find("=") + 1));

			//	Convert the contents to a string
			std::string input = sin.str();

			/// <summary>
			/// MENU THEME
			if (Word.find("COLORR") != -1) {
				float var = std::stof(input);
				g_Profile->m_CustomColors.x = (var / 255);
			}
			
			if (Word.find("COLORG") != -1) {
				float var = std::stof(input);
				g_Profile->m_CustomColors.y = (var / 255);
			}
			
			if (Word.find("COLORB") != -1) {
				float var = std::stof(input);
				g_Profile->m_CustomColors.z = (var / 255);
			}
			
			if (Word.find("COLORA") != -1) {
				float var = std::stof(input);
				g_Profile->m_CustomColors.w = (var / 255);
			}

			/// <summary>
			/// RECOIL & RAPID FIRE
			if (Word.find("recoilStrength1") != -1)
				g_Profile->config.recoilStrength[0] = std::stoi(input);
			if (Word.find("recoilDelay1") != -1)
				g_Profile->config.recoilDelay[0] = std::stoi(input);
			if (Word.find("recoilADSFlag1") != -1)
				g_Profile->config.recoilADSFlag[0] = std::stoi(input);
			if (Word.find("rapidFireDelay1") != -1)
				g_Profile->config.rapidFireDelay[0] = std::stoi(input);
			if (Word.find("rapidADSFlag1") != -1)
				g_Profile->config.rapidADSFlag[0] = std::stoi(input);

			if (Word.find("recoilStrength2") != -1)
				g_Profile->config.recoilStrength[1] = std::stoi(input);
			if (Word.find("recoilDelay2") != -1)
				g_Profile->config.recoilDelay[1] = std::stoi(input);
			if (Word.find("recoilADSFlag2") != -1)
				g_Profile->config.recoilADSFlag[01] = std::stoi(input);
			if (Word.find("rapidFireDelay2") != -1)
				g_Profile->config.rapidFireDelay[1] = std::stoi(input);
			if (Word.find("rapidADSFlag2") != -1)
				g_Profile->config.rapidADSFlag[1] = std::stoi(input);

			if (Word.find("recoilStrength3") != -1)
				g_Profile->config.recoilStrength[2] = std::stoi(input);
			if (Word.find("recoilDelay3") != -1)
				g_Profile->config.recoilDelay[2] = std::stoi(input);
			if (Word.find("recoilADSFlag3") != -1)
				g_Profile->config.recoilADSFlag[2] = std::stoi(input);
			if (Word.find("rapidFireDelay3") != -1)
				g_Profile->config.rapidFireDelay[2] = std::stoi(input);
			if (Word.find("rapidADSFlag3") != -1)
				g_Profile->config.rapidADSFlag[2] = std::stoi(input);
		}
		fin.close();
		return;
	}

	void Console::Free()
	{
		//  FREE CONSOLE
		fclose(stream_in);
		fclose(stream_out);
		fclose(stream_error);
		DestroyWindow(g_hWnd);
		FreeConsole();
		return;
	}
}
