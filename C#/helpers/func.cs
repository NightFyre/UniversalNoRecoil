using System;
using System.Threading;
using System.Runtime.InteropServices;

namespace helpers.UniversalNoRecoil2
{
    class func
    {
        [DllImport("user32.dll")]
        public static extern void mouse_event(uint dwFlags, int dx, int dy, uint dwData, int dwExtraInfo);
        public const uint MOUSEEVENTF_MOVE = 0x0001;
        public const int MOUSEEVENTF_LEFTDOWN = 0x02;
        public const int MOUSEEVENTF_LEFTUP = 0x04;

        [DllImport("user32.dll")]
        public static extern short GetAsyncKeyState(Int32 vKey);
        public static int VK_LBUTTON = 0x01;
        public static int VK_RBUTTON = 0x02;
        public static int VK_XBUTTON1 = 0x05;
        public static int VK_XBUTTON2 = 0x06;
        public static int VK_MENU = 0x12;
        public static int VK_END = 0x23;
        public static int VK_HOME = 0x24;
        public static int VK_INSERT = 0x2D;
        public static int VK_NUMPAD1 = 0x61;
        public static int VK_NUMPAD2 = 0x62;
        public static int VK_NUMPAD3 = 0x63;
        public static int VK_NUMPAD4 = 0x64;
        public static int VK_NUMPAD9 = 0x69;
        public static int VK_LSHIFT = 0xA0;

        /// <summary>
        /// Console UI
        /// </summary>
        /// <param name="PRESET1">String 1</param>
        /// <param name="PRESET2">String 2</param>
        /// <param name="PRESET3">String 3</param>
        /// <param name="RAPIDFIRE">String 4</param>
        /// <param name="FLAG">String 5</param>
        public static void _consoleMENU(string PRESET1, string PRESET2, string PRESET3, string RAPIDFIRE, string FLAG)
        {
            Console.Clear();
            Console.WriteLine(" _______________________ \n" +
            "|-------NO RECOIL-------|\n" +
            $"| [1] PRESET 1:  => [{PRESET1}] |\n" +
            $"| [2] PRESET 2:  => [{PRESET2}] |\n" +
            $"| [3] PRESET 3:  => [{PRESET3}] |\n" +
            $"| [4] RAPID FIRE => [{RAPIDFIRE}] |\n" +
            $"| [INS] REQ ADS: => [{FLAG}] |\n" +
            "| [HOME] CUSTOMIZE      |\n" +
            "| [END] QUIT            |\n" +
            "|v1.1-------NightFyre---|");
        }

        /// <summary>
        /// Flagged No Recoil
        /// </summary>
        /// <param name="aim_key">ADS Flag</param>
        /// <param name="shoot_key">Shoot Flag</param>
        /// <param name="speed">How far to move mouse down</param>
        /// <param name="delay">Time between automated mouse movements</param>
        public static void _uniCoil(short aim_key, short shoot_key, int speed, int delay)
        {
            if ((aim_key) != 0)
            {
                if ((shoot_key) != 0)
                {
                    mouse_event(MOUSEEVENTF_MOVE, 0, speed, 0, 0);
                    Thread.Sleep(delay);
                }
            }
        }

        /// <summary>
        /// No Recoil
        /// </summary>
        /// <param name="shoot_key">Shoot Flag</param>
        /// <param name="speed">How far to move mouse down</param>
        /// <param name="delay">Time between automated mouse movements</param>
        public static void _uniCoilF(short shoot_key, int speed, int delay)
        {
            if ((shoot_key) != 0)
            {
                mouse_event(MOUSEEVENTF_MOVE, 0, speed, 0, 0);
                Thread.Sleep(delay);
            }
        }

        /// <summary>
        /// Rapid Fire
        /// </summary>
        /// <param name="delay">Delay between mouse clicks</param>
        public static void _rFIRE(int delay)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Thread.Sleep(1);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Thread.Sleep(delay);
        }

        /// <summary>
        /// customSELECTIONS
        /// </summary>
        /// <param name="aim_key"></param>
        /// <param name="shoot_key"></param>
        /// <param name="SPEED"></param>
        /// <param name="DELAY"></param>
        /// <param name="FLAG"></param>
        public static void _uniCustom(short aim_key, short shoot_key, short rapid_key, int SPEED, int DELAY, string FLAG)
        {
            if (FLAG == "Y" || FLAG == "y")
            {
                if ((aim_key) != 0)
                {
                    if ((shoot_key) != 0)
                    {
                        mouse_event(MOUSEEVENTF_MOVE, 0, SPEED, 0, 0);
                        Thread.Sleep(DELAY);
                    }
                }
            }
            else if (FLAG == "N" || FLAG == "n")
            {
                if ((shoot_key) != 0)
                {
                    mouse_event(MOUSEEVENTF_MOVE, 0, SPEED, 0, 0);
                    Thread.Sleep(DELAY);
                }
            }
        }
    }
}
