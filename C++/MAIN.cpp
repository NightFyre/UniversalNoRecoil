#include "stdafx.h"

void _assignKeys(Config& config);

//Establish Variables
bool bMENU = false;
bool bPRESET1 = false, bPRESET2 = false, bPRESET3 = false, bRAPID = false;
string sPRESET1 = " ", sPRESET2 = " ", sPRESET3 = " ", sRAPID = " ";
bool bADSFLAG = false;
string sFLAG = "X";

//CUSTOM MENU
int custom();
bool bCUSTOM = false;
bool cMENU = false;
bool cRUN = false;

//CONFIG
int userSELECT;
short PRESET1;
short PRESET2;
short PRESET3;
short RAPIDFIRE;
int recoilStrength1;
int recoilDelay1;
int recoilStrength2;
int recoilDelay2;
int recoilStrength3;
int recoilDelay3;
int rapidFireDelay;

void _assignKeys(Config& config)
{
    //USER DEFINED KEYS (COMING SOON)
    if (userSELECT == 1)
    {
        PRESET1 = VK_NUMPAD1;         // PRESET 1 KEY
        PRESET2 = VK_NUMPAD2;        // PRESET 2 KEY
        PRESET3 = VK_NUMPAD3;       // PRESET 3 KEY
        RAPIDFIRE = VK_NUMPAD4;    // RAPID FIRE KEY
    }
    else if (userSELECT == 2)
    {
        PRESET1 = VK_F5;         // PRESET 1 KEY
        PRESET2 = VK_F6;        // PRESET 2 KEY
        PRESET3 = VK_F7;       // PRESET 3 KEY
        RAPIDFIRE = VK_F8;    // RAPID FIRE KEY
    }

    //USER DEFINED PRESETS
    recoilStrength1 = config.recoilStrength1;            // PRESET 1 Recoil Strength
    recoilDelay1 = config.recoilDelay1;                 // PRESET 1 Recoil DELAY
    recoilStrength2 = config.recoilStrength1;          // PRESET 2 Recoil Strength
    recoilDelay2 = config.recoilDelay2;               // PRESET 2 Recoil DELAY
    recoilStrength3 = config.recoilStrength1;        // PRESET 3 Recoil Strength
    recoilDelay3 = config.recoilDelay3;             // PRESET 4 Recoil DELAY
    rapidFireDelay = config.rapidFireDelay;        // Rapid Fire Delay
}

int main()
{
    Config config;
    _loadConfig(config, userSELECT);
    _assignKeys(config);

    //Prepare Console Window
    _setWindow(30, 12);
    SetConsoleTitle(L"uniCoil | v2.0");
    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
    bMENU = true;

    //Display Main Menu
    while (bMENU)
    {
        //Keybinds
        if (GetAsyncKeyState(PRESET1) & 1)
        {
            if (!bPRESET2 && !bPRESET3)
            {
                bPRESET1 = !bPRESET1;
                if (bPRESET1)
                {
                    sPRESET1 = "X";
                    _clearConsole();
                    cout << "\007" << endl;;
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);

                }
                else
                {
                    sPRESET1 = " ";
                    _clearConsole();
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
                }
            }
        }

        if (GetAsyncKeyState(PRESET2) & 1)
        {
            if (!bPRESET1 && !bPRESET3)
            {
                bPRESET2 = !bPRESET2;
                if (bPRESET2)
                {
                    sPRESET2 = "X";
                    _clearConsole();
                    cout << "\007" << endl;;
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
                }
                else
                {
                    sPRESET2 = " ";
                    _clearConsole();
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
                }
            }
        }

        if (GetAsyncKeyState(PRESET3) & 1)
        {
            if (!bPRESET1 && !bPRESET2)
            {
                bPRESET3 = !bPRESET3;
                if (bPRESET3)
                {
                    sPRESET3 = "X";
                    _clearConsole();
                    cout << "\007" << endl;;
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
                }
                else
                {
                    sPRESET3 = " ";
                    _clearConsole();
                    _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
                }
            }
        }

        //Rapid Fire
        if (GetAsyncKeyState(RAPIDFIRE) & 1)
        {
            bRAPID = !bRAPID;
            if (bRAPID)
            {
                sRAPID = "X";
                _clearConsole();
                _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
            }
            else
            {
                sRAPID = " ";
                _clearConsole();
                _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
            }
        }

        //Customize
        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            _clearConsole();
            bPRESET1, bPRESET2, bPRESET3, bADSFLAG = false;
            sPRESET1, sPRESET2, sPRESET3, sFLAG = "";
            bMENU = false;
            custom();
        }

        //ADS Flag & Panic Key
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            bADSFLAG = !bADSFLAG;

            if (bADSFLAG)
            {
                sFLAG = " ";
                _clearConsole();
                _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
            }
            else
            {
                sFLAG = "X";
                _clearConsole();
                _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
            }
        }

        // QUIT
        if (GetKeyState(VK_END))
        {
            break;
        }

        //Recoil Loops
        if (bPRESET1)
        {
            if (!bADSFLAG)
            {
                _flaggedCOIL(recoilStrength1, recoilDelay1);
            }
            else
            {
                _UniCoil(recoilStrength1, recoilDelay1);
            }
        }

        if (bPRESET2)
        {
            if (!bADSFLAG)
            {
                _flaggedCOIL(recoilStrength2, recoilDelay2);
            }
            else
            {
                _UniCoil(recoilStrength2, recoilDelay2);
            }
        }

        if (bPRESET3)
        {
            if (!bADSFLAG)
            {
                _flaggedCOIL(recoilStrength3, recoilDelay3);
            }
            else
            {
                _UniCoil(recoilStrength3, recoilDelay3);
            }
        }

        //Rapid Fire
        if (bRAPID)
        {
            _rapidFire(rapidFireDelay);
        }

        //Timer
        Sleep(1);
    }
}

int custom()
{
    //Original Custom Input Method by "Cubb"
    //Original Source Code: https://www.unknowncheats.me/forum/2871653-post1.html
    ////::ShowWindow(::GetConsoleWindow(), SW_SHOW);
    ////int  speed = 194;
    ////int delay = 0;
    ////cout << "enter speed " << endl;
    ////cin >> speed;
    ////cout << "speed is " << speed << endl;
    ////cout << "enter delay " << endl;
    ////cin >> delay;
    ////cout << "delay is " << delay << endl;
    ////while (1)
    ////{
    ////    if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
    ////    {
    ////        mouse_event(MOUSEEVENTF_MOVE, 0, speed, NULL, NULL);
    ////        Sleep(delay);
    ////    }
    ////}


    //UPDATE 10-16-2021
    //New plan is to include a configuration file. This will eliminate the need for a separate menu entirely.
    //User will be able to define Keys and Preset Values
    
    //UPDATE , Its now 1am and i have finally got the config setup completed for users. However , I have decided to keep the custom menu.
    //1, I would like to maintain this small connection to the original authors work
    //2, I believe users will find it helpful when creating their own configuration to have access to customizing settings while in the process
    // to expand on this , i have made it so that the configuration will be reloaded when user exits the custom menu. This way user will not have to exit the app to trigger the config load event.
    // may also include a button to reload the config ... but i dont see a need for it

    //Prepare console for user input
    _setWindow(40, 10);
    int speed = 9;
    int delay = 9;

    //Introduce ADS Flag
    string adsFLAG;
    
    //Rapid Fire
    string rapidFLAG;
    bool bRAPID = false;

    //Declare so we can later load in case user makes changes
    Config config;
    
    cout << "Enter Recoil Amount: (between 0 - 9)" << endl;
    cin >> speed;
    _clearConsole();

    cout << "Enter Desired Delay: (between 0 - 9)" << endl;
    cin >> delay;
    _clearConsole();

    //Begin Branch
    cout << "Require ADS? (Y/N)" << endl;
    cin >> adsFLAG;
    if (adsFLAG == "Y" || adsFLAG == "y")
    {
        _clearConsole();
        cout << "Rapid Fire? (Y/N)" << endl;
        cin >> rapidFLAG;
        if (rapidFLAG == "Y" || rapidFLAG == "y")
        {
            bCUSTOM = true;
            bRAPID = true;
        }
        else if (rapidFLAG == "N" || rapidFLAG == "n")
        {
            bCUSTOM = true;
        }
        else
        {
            //Return to main
            _clearConsole();
            std::cout << "Please enter a valid response of Y or N\n";
            std::cout << "returning to Main Menu" << std::endl;
            Sleep(3000);

            //Restore Custom Menu Defaults
            speed = 0;
            delay = 0;
            adsFLAG = "";
            bCUSTOM = false;
            bRAPID = false;
            cMENU = false;
            bMENU = true;
            _clearConsole();

            //Display Main Menu
            bADSFLAG = false;
            sFLAG = "X";
            _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
        }
    }
    else if (adsFLAG == "N" || adsFLAG == "n")
    {
        _clearConsole();        
        cout << "Rapid Fire? (Y/N)" << endl;
        cin >> rapidFLAG;
        if (rapidFLAG == "Y" || rapidFLAG == "y")
        {
            bCUSTOM = true;
            bRAPID = true;
        }
        else if (rapidFLAG == "N" || rapidFLAG == "n")
        {
            bCUSTOM = true;
        }
        else
        {
            //Return to main
            _clearConsole();
            std::cout << "Please enter a valid response of Y or N\n";
            std::cout << "returning to Main Menu" << std::endl;
            Sleep(3000);

            //Restore Custom Menu Defaults
            speed = 0;
            delay = 0;
            adsFLAG = "";
            bCUSTOM = false;
            bRAPID = false;
            cMENU = false;
            bMENU = true;
            _clearConsole();

            //Display Main Menu
            bADSFLAG = false;
            sFLAG = "X";
            recoilSELECTION(sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
        }
    }
    else
    {
        //Return to main
        _clearConsole();
        std::cout << "Please enter a valid response of Y or N\n";
        std::cout << "returning to Main Menu" << std::endl;
        Sleep(3000);

        //Restore Custom Menu Defaults
        speed = 0;
        delay = 0;
        adsFLAG = "";
        bCUSTOM = false;
        bRAPID = false;
        cMENU = false;
        bMENU = true;
        _clearConsole();

        //Display Main Menu
        bADSFLAG = false;
        sFLAG = "X";
        _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
    }

    // NightFyre Console framework
    while (bCUSTOM)
    {
        //Display user settings and other options
        if (!cMENU)
        {
            //Create menu
            _setWindow(30, 12);
            recoilCUSTOM(speed, delay, adsFLAG, bRAPID);
            cMENU = true;
            cRUN = true;
        }

        if (cRUN)
        {
            _uniCustom(adsFLAG, speed, delay);
        }

        if (bRAPID)
        {
            _rapidFire(50);
        }

        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            //Return to main
            _clearConsole();
            std::cout << "Returning to Main Menu" << std::endl;
            Sleep(3000);

            //Restore Custom Menu Defaults
            speed = 0;
            delay = 0;
            adsFLAG = "";
            bCUSTOM = false;
            bRAPID = false;
            cMENU = false;
            bMENU = true;
            _clearConsole();

            //Display Main Menu
            bADSFLAG = false;
            sFLAG = "X";
            _loadConfig(config, userSELECT);
            _userMENU(userSELECT, sPRESET1, sPRESET2, sPRESET3, sRAPID, sFLAG);
        }

        if (GetKeyState(VK_END))
        {
            break;
        }

        Sleep(1);
    }

    return 0;
}