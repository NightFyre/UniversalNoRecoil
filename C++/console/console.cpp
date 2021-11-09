#include "stdafx.h"

void _clearConsole()
{
    system("cls");
}

void _setConsole()
{
    //Set Cursor to Draw From Beginning
    //Credit : Acidix -- Guided Hacking 
    COORD coords;
    coords.X = 0;
    coords.Y = 0;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(stdHandle, coords);
}

void _setWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}

void recoilSELECTION(string& HACK1 , string& HACK2, string& HACK3, string& HACK4, string& FLAG)
{
    _setConsole();
    std::cout << " ________________________ \n";
    std::cout << "|-------NO  RECOIL-------|\n";
    std::cout << "| [1] PRESET 1    => [" << HACK1 << "] |\n";
    std::cout << "| [2] PRESET 2    => [" << HACK2 << "] |\n";
    std::cout << "| [3] PRESET 3    => [" << HACK3 << "] |\n";
    std::cout << "| [4] RAPID FIRE  => [" << HACK4 << "] |\n";
    std::cout << "| [INS] REQ ADS   => [" << FLAG << "] |\n";
    std::cout << "| [HOME] CUSTOM          |\n";
    std::cout << "| [END] QUIT             |\n";
    std::cout << "|v2.0--------NightFyre---|" << std::endl;
}

void recoilSELECTION2(string& HACK1, string& HACK2, string& HACK3, string& HACK4, string& FLAG)
{
    _setConsole();
    std::cout << " ________________________ \n";
    std::cout << "|-------NO  RECOIL-------|\n";
    std::cout << "| [F5] PRESET 1   => [" << HACK1 << "] |\n";
    std::cout << "| [F6] PRESET 2   => [" << HACK2 << "] |\n";
    std::cout << "| [F7] PRESET 3   => [" << HACK3 << "] |\n";
    std::cout << "| [F8] RAPID FIRE => [" << HACK4 << "] |\n";
    std::cout << "| [INS] REQ ADS   => [" << FLAG << "] |\n";
    std::cout << "| [HOME] CUSTOM          |\n";
    std::cout << "| [END] QUIT             |\n";
    std::cout << "|v2.0--------NightFyre---|" << std::endl;
}

void recoilCUSTOM(int& HACK1, int& HACK2, string& HACK3, bool& HACK4)
{
    _clearConsole();
    std::cout << " _________________________\n";
    std::cout << "|------CUSTOM PRESET------|\n";
    std::cout << "| Speed        =>   [" << HACK1 << "]   |\n";
    std::cout << "| Delay        =>   [" << HACK2 << "]   |\n";
    std::cout << "| ADS Flag     =>   [" << HACK3 << "]   |\n";
    if (HACK4)
    {
        std::cout << "| Rapid Fire   =>   [ON]  |\n";

    }
    else
    {
        std::cout << "| Rapid Fire   =>   [OFF] |\n";

    }
    std::cout << "|v2.0----------NightFyre--|\n";
    std::cout << "PRESS [HOME] FOR MAIN MENU\n";
    std::cout << "PRESS [END] TO QUIT\n" << std::endl;;
}