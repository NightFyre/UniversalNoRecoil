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
		fout << g_LauncherVariables->m_CustomColors.x << "\n";
		fout << g_LauncherVariables->m_CustomColors.y << "\n";
		fout << g_LauncherVariables->m_CustomColors.z << "\n";
		fout << g_LauncherVariables->m_CustomColors.w << std::endl;
		fout.close();
		return;
	}

	void Console::LoadCFG()
	{
		std::ifstream fin;
		std::string Word = "";
		fin.open("settings.ini", std::ifstream::in);
		for (int i = 0; i <= 3; i++) {		
			fin >> Word;
			g_LauncherVariables->cfgColors.push_back(std::stof(Word));
		}

		g_LauncherVariables->m_CustomColors.x = g_LauncherVariables->cfgColors[0];
		g_LauncherVariables->m_CustomColors.y = g_LauncherVariables->cfgColors[1];
		g_LauncherVariables->m_CustomColors.z = g_LauncherVariables->cfgColors[2];
		g_LauncherVariables->m_CustomColors.w = g_LauncherVariables->cfgColors[3];
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
