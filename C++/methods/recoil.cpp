#include "stdafx.h"

void _UniCoil(int speed, int delay)
{
    if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
    {
        mouse_event(MOUSEEVENTF_MOVE, 0, speed, NULL, NULL);
        Sleep(delay);
    }
}

void _flaggedCOIL(int speed, int delay)
{
    if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
    {
        if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
        {
            mouse_event(MOUSEEVENTF_MOVE, 0, speed, NULL, NULL);
            Sleep(delay);
        }
    }
}

void _rapidFire(int delay)
{
    if (GetAsyncKeyState(VK_MENU) < 0)
    {
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(1);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(delay);
    }
}

void _uniCustom(string& FLAG, int& speed, int& delay)
{
    if (FLAG == "Y" || FLAG == "y")
    {
        //Method
        if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
        {
            if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
            {
                mouse_event(MOUSEEVENTF_MOVE, 0, speed, NULL, NULL);
                Sleep(delay);
            }
        }
    }
    else if (FLAG == "N" || FLAG == "n")
    {
        //Method
        if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
        {
            mouse_event(MOUSEEVENTF_MOVE, 0, speed, NULL, NULL);
            Sleep(delay);
        }
    }
}