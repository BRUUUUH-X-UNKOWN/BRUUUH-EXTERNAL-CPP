
#include <Windows.h>
#include <vector>
#include <string> 
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <winternl.h>
#include <mutex>
#include <map>
#include <future>
#include <random>
#include "Memory.h"
#include <C:\Users\USER\Desktop\BRUUUH EXTERNAL\BRUUUH EXTERNAL\C++\examples\example_win32_directx11\SmartyMem.h>
#include <mutex>
#include <future>


#pragma comment(lib, "ntdll.lib")

extern std::string MemoryLogs;
extern bool g_MuteBeeps;

 
#pragma once

 


class ShadowBrutal
{

public:
    DWORD ProcessId = 0;
    HANDLE ProcessHandle;

    typedef struct _MEMORY_REGION
    {
        DWORD_PTR dwBaseAddr;
        DWORD_PTR dwMemorySize;
    }MEMORY_REGION;

    int GetPid(const char* procname)
    {
        if (procname == NULL)
            return 0;

        DWORD pid = 0;
        DWORD threadCount = 0;

        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap == INVALID_HANDLE_VALUE)
            return 0;

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(PROCESSENTRY32);

        if (Process32First(hSnap, &pe))
        {
            do
            {

#ifdef UNICODE
                char exeFile[MAX_PATH];
                size_t convertedChars = 0;
                wcstombs_s(&convertedChars, exeFile, pe.szExeFile, _TRUNCATE);
                if (_stricmp(exeFile, procname) == 0)

#else

                if (_stricmp(pe.szExeFile, procname) == 0)

#endif

                {
                    if ((int)pe.cntThreads > threadCount)
                    {
                        threadCount = pe.cntThreads;
                        pid = pe.th32ProcessID;
                    }
                }
            } while (Process32Next(hSnap, &pe));
        }

        CloseHandle(hSnap);

        return pid;
    }

    const char* GetEmulatorRunning()
    {
        if (GetPid("HD-Player.exe") != 0)
            return "HD-Player.exe";

        else if (GetPid("LdVBoxHeadless.exe") != 0)
            return "LdVBoxHeadless.exe";

        else if (GetPid("MEmuHeadless.exe") != 0)
            return "MEmuHeadless.exe";

        else if (GetPid("LdVBoxHeadless.exe") != 0)
            return "LdVBoxHeadless.exe";

        else if (GetPid("AndroidProcess.exe") != 0)
            return "AndroidProcess.exe";

        else if (GetPid("aow_exe.exe") != 0)
            return "aow_exe.exe";

        else if (GetPid("NoxVMHandle.exe") != 0)
            return "NoxVMHandle.exe";
        
        return nullptr;

    }

    struct EntitySpeedHere
    {
        DWORD_PTR addressSpeed;
        std::vector<BYTE> patternSpeed;
    };

    std::vector<EntitySpeedHere> OldSpeed;
    std::vector<DWORD_PTR> NewSpeed;

    struct EntityHere
    {
        std::vector<EntityHere> SpeedoriginalBytesMap;
        DWORD_PTR addressSpeed;

    };



    std::unordered_map<uintptr_t, std::vector<BYTE>> SpeedoriginalBytesMap;

 

    bool SaveSpeedAoB()
    {

        if (!AttackProcess("HD-Player.exe"))
        {
            MemoryLogs = "Emulator Not Found !";
          // //"Notification", "Emulator Not Found !", main_color);
            return false;
        }

        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR startAddress = reinterpret_cast<DWORD_PTR>(si.lpMinimumApplicationAddress);
        DWORD_PTR endAddress = reinterpret_cast<DWORD_PTR>(si.lpMaximumApplicationAddress);


        std::vector<BYTE> SearchSpeed = { 0x01, 0x00, 0x00, 0x00, 0x02, 0x2b, 0x07, 0x3d };




        // //"Notification", "Speed Hack : Loading", main_color);
        MemoryLogs = "Speed Hack : Loading !";

        NewSpeed.clear();
        OldSpeed.clear();


        if (!FindPattern(startAddress, endAddress, SearchSpeed.data(), NewSpeed))
        {
            // //"Notification", "Speed Hack Failed.", main_color);
           //"Notification", "Speed Hack : Load", main_color);
            MemoryLogs = "Speed Hack : Load !";
            return false;
        }


        if (NewSpeed.empty())
        {
           //"Notification", "Address Not Found!", main_color);

            return false;
        }


        return true;
    }

    bool ActivateSpeed()
    {
        std::vector<BYTE> replace = { 0x01, 0x00, 0x00, 0x00, 0x92, 0xe4, 0x6f, 0x3d };


        if (NewSpeed.empty())
        {
            return false;
        }


        for (const auto& address : NewSpeed)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

            //"Notification", "Speed Hack : Activated !", main_color);
            MemoryLogs = "Speed Hack : Activated !";
        }

        return true;
    }



    bool ActivateMax()
    {
        std::vector<BYTE> replace = { 0x01, 0x00, 0x00, 0x00, 0x92, 0xe4, 0x6f, 0x3d };


        if (NewSpeed.empty())
        {
            return false;
        }


        for (const auto& address : NewSpeed)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

        }
        return true;
    }

    bool SpeedOFF()
    {
        std::vector<BYTE> replace = { 0x01, 0x00, 0x00, 0x00, 0x02, 0x2b, 0x07, 0x3d };


        if (NewSpeed.empty())
        {
            return false;
        }


        for (const auto& address : NewSpeed)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                continue;
            }

           //"Notification", "Speed Hack : Deactivated !", main_color);
            MemoryLogs = "Speed Hack : Deactivated !";
        }
        return true;
    }


    struct EntityWallHackHere
    {
        DWORD_PTR addressWallHack;
        std::vector<BYTE> patternWallHack;
    };

    std::vector<EntityWallHackHere> OldWallHack;
    std::vector<DWORD_PTR> NewWallHack;





    std::unordered_map<uintptr_t, std::vector<BYTE>> WallHackoriginalBytesMap;

    bool cameraright()
    {
        std::vector<BYTE> replace = { 0x01, 0x00, 0x00, 0x00, 0x92, 0xe4, 0x6f, 0x3d };


        if (NewSpeed.empty())
        {
            return false;
        }


        for (const auto& address : NewSpeed)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

            //"Notification", "Speed Hack : Activated !", main_color);
            MemoryLogs = "Speed Hack : Activated !";
        }

        return true;
    }









    bool tryingmethod()
    {
        // Checking if the emulator is running
        if (!AttackProcess("HD-Player.exe"))
        {
           //"Notification", "Emulator Not Found !", main_color);
            return false;
        }

        // Getting system information
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR startAddress = reinterpret_cast<DWORD_PTR>(si.lpMinimumApplicationAddress);
        DWORD_PTR endAddress = reinterpret_cast<DWORD_PTR>(si.lpMaximumApplicationAddress);

        // Define patterns for Speed and Camera Hack
        std::vector<BYTE> SearchSpeed = { 0x3f, 0xae, 0x47, 0x81, 0x3f, 0x00, 0x1a, 0xb7, 0xee, 0xdc, 0x3a, 0x9f, 0xed, 0x30, 0x00, 0x4f, 0xe2, 0x43, 0x2a, 0xb0, 0xee, 0xef, 0x0a, 0x60, 0xf4, 0x43, 0x6a, 0xf0, 0xee, 0x1c, 0x00, 0x8a, 0xe2, 0x43, 0x5a, 0xf0, 0xee, 0x8f };
        std::vector<BYTE> SearchCameraHack = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };

        // Notification for Speed Hack
       //"Notification", "Camra & Wall Hack : Loading", main_color);

        // Clear previous results
        NewWallHack.clear();
        OldWallHack.clear();
        NewcamraHack.clear();
        OldcamraHack.clear();

        // Search for Speed Hack pattern
        if (!FindPattern(startAddress, endAddress, SearchSpeed.data(), NewWallHack))
        {
           //"Notification", "Wall Hack : Load Failed", main_color);
        }

        // Search for Camera Hack pattern
        if (!FindPattern(startAddress, endAddress, SearchCameraHack.data(), NewcamraHack))
        {
           //"Notification", "Camera Hack : Load Failed", main_color);
        }

        // Check if patterns were found
        if (NewWallHack.empty() && NewcamraHack.empty())
        {
           //"Notification", "No Addresses Found!", main_color);
            return false;
        }

        // If found, show success notification
        if (!NewWallHack.empty())
        {
           //"Notification", "Wall Hack : Loaded", main_color);
        }

        if (!NewcamraHack.empty())
        {
           //"Notification", "Camra & Wall Hack : Loaded", main_color);
        }

        return true;
    }

    //scop methed
    struct Entityscope2Here
    {
        DWORD_PTR addressscope2;
        std::vector<BYTE> patternscope2;
    };

    std::vector<Entityscope2Here> Oldscope2;
    std::vector<DWORD_PTR> Newscope2;


    std::unordered_map<uintptr_t, std::vector<BYTE>> scope2originalBytesMap;

    // glich method

    struct EntityglichHere
    {
        DWORD_PTR addressglich;
        std::vector<BYTE> patternglich;
    };

    std::vector<EntityglichHere> Oldglich;
    std::vector<DWORD_PTR> Newglich;



    std::unordered_map<uintptr_t, std::vector<BYTE>> glichoriginalBytesMap;

    //sniper scope
    struct EntitysniperscopeHere
    {
        DWORD_PTR addresssniperscope;
        std::vector<BYTE> patternsniperscope;
    };

    std::vector<EntitysniperscopeHere> Oldsniperscope;
    std::vector<DWORD_PTR> Newsniperscope;


    std::unordered_map<uintptr_t, std::vector<BYTE>> sniperscopeoriginalBytesMap;

    //snipertracking
    struct EntityscopetrackingHere
    {
        DWORD_PTR addressscopetracking;
        std::vector<BYTE> patternscopetracking;
    };

    std::vector<EntityscopetrackingHere> Oldscopetracking;
    std::vector<DWORD_PTR> Newscopetracking;


    std::unordered_map<uintptr_t, std::vector<BYTE>> scopetrackingoriginalBytesMap;

    //sniper swich

    struct EntitysniperswitchHere
    {
        DWORD_PTR addresssniperswitch;
        std::vector<BYTE> patternsniperswitch;
    };

    std::vector<EntitysniperswitchHere> Oldsniperswitch;
    std::vector<DWORD_PTR> Newsniperswitch;


    std::unordered_map<uintptr_t, std::vector<BYTE>> sniperswitchoriginalBytesMap;


    bool allmethod()
    {
        // Checking if the emulator is running
        if (!AttackProcess("HD-Player.exe"))
        {
           //"Notification", "Emulator Not Found !", main_color);
            return false;
        }

        // Getting system information
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR startAddress = reinterpret_cast<DWORD_PTR>(si.lpMinimumApplicationAddress);
        DWORD_PTR endAddress = reinterpret_cast<DWORD_PTR>(si.lpMaximumApplicationAddress);

        // Define patterns for Speed, Camera Hack, and the new ones
        std::vector<BYTE> SearchSpeed = { 0x3f, 0xae, 0x47, 0x81, 0x3f, 0x00, 0x1a, 0xb7, 0xee, 0xdc, 0x3a, 0x9f, 0xed, 0x30, 0x00, 0x4f, 0xe2, 0x43, 0x2a, 0xb0, 0xee, 0xef, 0x0a, 0x60, 0xf4, 0x43, 0x6a, 0xf0, 0xee, 0x1c, 0x00, 0x8a, 0xe2, 0x43, 0x5a, 0xf0, 0xee, 0x8f };
        std::vector<BYTE> SearchCameraHack = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };

        // New patterns
        std::vector<BYTE> SearchScope2x = { 0xc0,0x3f,0x33,0x33,0x13,0x40,0x00,0x00,0xf0,0x3f,0x00,0x00,0x80,0x3f };
        std::vector<BYTE> SearchGlichFire = { 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x40 };
        std::vector<BYTE> SearchSniperScope = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01 };
        //std::vector<BYTE> SearchSniperTracking = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x4F, 0x01 };
        std::vector<BYTE> SearchSniperSwitch = { 0x42, 0x00, 0x00, 0xB4, 0x42, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01 };

        // Notification for hacks loading
       //"Notification", "Please Wait Reading This Memory !", main_color);
        MemoryLogs = "Please Wait Reading This Memory !";

        // Clear previous results
        NewWallHack.clear();
        OldWallHack.clear();
        NewcamraHack.clear();
        OldcamraHack.clear();
        Newscope2.clear();
        Oldscope2.clear();
        Newglich.clear();
        Oldglich.clear();
        Newsniperscope.clear();
        Oldsniperscope.clear();
        //Newscopetracking.clear();
       // Oldscopetracking.clear();
        Newsniperswitch.clear();
        Oldsniperswitch.clear();

        // Search for patterns
        if (!FindPattern(startAddress, endAddress, SearchSpeed.data(), NewWallHack))
        {
           //"Notification", "Wall Hack: Load Failed", main_color);
        }

        if (!FindPattern(startAddress, endAddress, SearchCameraHack.data(), NewcamraHack))
        {
           //"Notification", "Camera Hack: Load Failed", main_color);
        }

        if (!FindPattern(startAddress, endAddress, SearchScope2x.data(), Newscope2))
        {
           //"Notification", "Scope 2x Hack: Load Failed", main_color);
        }

        if (!FindPattern(startAddress, endAddress, SearchGlichFire.data(), Newglich))
        {
           //"Notification", "GlichFire Hack: Load Failed", main_color);
        }

        if (!FindPattern(startAddress, endAddress, SearchSniperScope.data(), Newsniperscope))
        {
           //"Notification", "SniperScope Hack: Load Failed", main_color);
        }

        //if (!FindPattern(startAddress, endAddress, SearchSniperTracking.data(), Newscopetracking))
       // {
        //   //"Notification", "SniperTracking Hack: Load Failed", main_color);
       // }

        if (!FindPattern(startAddress, endAddress, SearchSniperSwitch.data(), Newsniperswitch))
        {
           //"Notification", "SniperSwitch Hack: Load Failed", main_color);
        }

        // Check if patterns were found
        if (NewWallHack.empty() && NewcamraHack.empty() && Newscope2.empty() && Newglich.empty() &&
            Newsniperscope.empty() && Newsniperswitch.empty())
        {
           //"Notification", "No Addresses Found!", main_color);
            return false;
        }

        // If found, show success notifications
        if (!NewWallHack.empty())
        {
           //"Notification", "Wall Hack: Loaded", main_color);
        }

        if (!NewcamraHack.empty())
        {
           //"Notification", "Camera Hack: Loaded", main_color);
        }

        if (!Newscope2.empty())
        {
           //"Notification", "Scope 2x Hack: Loaded", main_color);
        }

        if (!Newglich.empty())
        {
           //"Notification", "GlichFire Hack: Loaded", main_color);
        }

        if (!Newsniperscope.empty())
        {
           //"Notification", "SniperScope Hack: Loaded", main_color);
        }

      

        if (!Newsniperswitch.empty())
        {
           //"Notification", "All Steps Are Done Paly Now !", main_color);
            MemoryLogs = "All Steps Are Done Paly Now !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    //2xscop

    bool scop2()
    {
        std::vector<BYTE> replace = { 0xc0,0x3f,0x33,0x33,0x13,0x40,0x00,0x00,0xf0,0x3f,0x00,0x00,0x80,0x4c };

        if (Newscope2.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }

        

        for (const auto& address : Newscope2)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Scope 2xit : Activated !", main_color);
            MemoryLogs = "Scope 2xit : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFWscop2()
    {
        std::vector<BYTE> replace = { 0xc0,0x3f,0x33,0x33,0x13,0x40,0x00,0x00,0xf0,0x3f,0x00,0x00,0x80,0x3f };


        if (Newscope2.empty())
        {
            return false;
        }


        for (const auto& address : Newscope2)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Scope 2xit : Deactivated !", main_color);
            MemoryLogs = "Scope 2xit : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    //glich fire

    bool glichfire()
    {
        std::vector<BYTE> replace = { 0x00, 0xC0, 0x30, 0x00, 0x00, 0x00, 0x3F };

        if (Newglich.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }


        for (const auto& address : Newglich)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Glich Fire : Activated !", main_color);
            MemoryLogs = "Glich Fire : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFglichfire()
    {
        std::vector<BYTE> replace = { 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x40 };


        if (Newglich.empty())
        {
            return false;
        }


        for (const auto& address : Newglich)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Glich Fire : Deactivated !", main_color);
            MemoryLogs = "Glich Fire : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    //sniper scope

    bool sniperscop()
    {
        std::vector<BYTE> replace = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01 };

        if (Newsniperscope.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }


        for (const auto& address : Newsniperscope)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Scope : Activated !", main_color);
            MemoryLogs = "Sniper Scope : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFsniperscop()
    {
        std::vector<BYTE> replace = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01 };


        if (Newsniperscope.empty())
        {
            return false;
        }


        for (const auto& address : Newsniperscope)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Scope : Deactivated !", main_color);
            MemoryLogs = "Sniper Scope : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    // scope tracking

    bool scoptracking()
    {
        std::vector<BYTE> replace = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01 };

        if (Newscopetracking.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }


        for (const auto& address : Newscopetracking)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Scope Tracking : Activated !", main_color);
            MemoryLogs = "Sniper Scope Tracking : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFscoptracking()
    {
        std::vector<BYTE> replace = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8E, 0x03, 0x00, 0xEE, 0x90, 0x03, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xB0, 0x3F, 0x00, 0x00, 0x80, 0x4F, 0x01 };


        if (Newscopetracking.empty())
        {
            return false;
        }


        for (const auto& address : Newscopetracking)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Scope Tracking : Deactivated !", main_color);
            MemoryLogs = "Sniper ScopeTracking : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    //sniperswitch
    bool scosniperswitchp()
    {
        std::vector<BYTE> replace = { 0x42, 0x00, 0x00, 0x3F, 0x42, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3B, 0x00, 0x00, 0x29, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01 };

        if (Newsniperswitch.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }


        for (const auto& address : Newsniperswitch)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Switch : Activated !", main_color);
            MemoryLogs = "Sniper Switch : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFscosniperswitchp()
    {
        std::vector<BYTE> replace = { 0x42, 0x00, 0x00, 0xB4, 0x42, 0x96, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01 };


        if (Newsniperswitch.empty())
        {
            return false;
        }


        for (const auto& address : Newsniperswitch)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Sniper Switch : Deactivated !", main_color);
            MemoryLogs = "Sniper Switch : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }

    

    bool ActivateWallHack()
    {
        std::vector<BYTE> replace = { 0xbf, 0xae, 0x47, 0x81, 0x3f, 0x00, 0x1a, 0xb7, 0xee, 0xdc, 0x3a, 0x9f, 0xed, 0x30, 0x00, 0x4f, 0xe2, 0x43, 0x2a, 0xb0, 0xee, 0xef, 0x0a, 0x60, 0xf4, 0x43, 0x6a, 0xf0, 0xee, 0x1c, 0x00, 0x8a, 0xe2, 0x43, 0x5a, 0xf0, 0xee, 0x8f };

        if (NewWallHack.empty())
        {
            MemoryLogs = "No addresses found!";
            return false;
        }


        for (const auto& address : NewWallHack)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Wall Hack : Activated !", main_color);
            MemoryLogs = "Wall Hack : Activated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    bool OFFWallHack()
    {
        std::vector<BYTE> replace = { 0x3f, 0xae, 0x47, 0x81, 0x3f, 0x00, 0x1a, 0xb7, 0xee, 0xdc, 0x3a, 0x9f, 0xed, 0x30, 0x00, 0x4f, 0xe2, 0x43, 0x2a, 0xb0, 0xee, 0xef, 0x0a, 0x60, 0xf4, 0x43, 0x6a, 0xf0, 0xee, 0x1c, 0x00, 0x8a, 0xe2, 0x43, 0x5a, 0xf0, 0xee, 0x8f };


        if (NewWallHack.empty())
        {
            return false;
        }


        for (const auto& address : NewWallHack)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "Wall Hack : Deactivated !", main_color);
            MemoryLogs = "Wall Hack : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }


    // camrea 


    struct EntitycamraHackHere
    {
        DWORD_PTR addresscamraHack;
        std::vector<BYTE> patterncamraHack;
    };

    std::vector<EntitycamraHackHere> OldcamraHack;
    std::vector<DWORD_PTR> NewcamraHack;





    std::unordered_map<uintptr_t, std::vector<BYTE>> camraHackoriginalBytesMap;

    

     


    bool OFFcamraHack()
    {
        std::vector<BYTE> replace = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };


        if (NewcamraHack.empty())
        {
            return false;
        }


        for (const auto& address : NewcamraHack)
        {
            if (!WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), replace.data(), replace.size(), nullptr))
            {
                MemoryLogs += "Failed to write memory at address";
                continue;
            }

           //"Notification", "camra Hack : Deactivated !", main_color);
            MemoryLogs = "camra Hack : Deactivated !";
            if (!g_MuteBeeps) Beep(500, 500);
        }

        return true;
    }



 
 






    bool SpeedOriginalBytes(uintptr_t address)
    {
        std::vector<BYTE> bytes(256);

        // Read original bytes and store them in the map
        if (ReadProcessMemory(ProcessHandle, reinterpret_cast<LPCVOID>(address), bytes.data(), bytes.size(), nullptr))
        {
            SpeedoriginalBytesMap[address] = bytes;
            return true;
        }

        MemoryLogs += "Failed to read memory at address: " + std::to_string(address) + "\n";
        return false;
    }

    bool RevertSpeed()
    {

        if (SpeedoriginalBytesMap.empty())
        {
            MemoryLogs = "No changes to revert";
            return false;
        }

        for (const auto& entry : SpeedoriginalBytesMap)
        {
            uintptr_t address = entry.first;
            const std::vector<BYTE>& bytes = entry.second;

            if (WriteProcessMemory(ProcessHandle, reinterpret_cast<LPVOID>(address), bytes.data(), bytes.size(), nullptr))
            {
                MemoryLogs += "Successfully reverted changes at address: " + std::to_string(address) + "\n";
            }
            else
            {
                MemoryLogs += "Failed to revert changes at address: " + std::to_string(address) + "\n";
                return false;
            }
        }
        SpeedoriginalBytesMap.clear();
        return true;
    }

    std::vector<BYTE> IntToByteArray(int value)
    {
        std::vector<BYTE> byteArray(sizeof(value));
        BYTE* pValue = reinterpret_cast<BYTE*>(&value);

        for (size_t i = 0; i < sizeof(value); ++i)
        {
            byteArray[i] = pValue[i];
        }

        return byteArray;
    }


    void ReWrite(std::string type, DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* Search, BYTE* Replace)
    {
        if (!AttackProcess(GetEmulatorRunning()))
            MemoryLogs = type + ": An unexpected error occurred";

        MemoryLogs = "Applying - " + type;
        bool Status = ReplacePattern(dwStartRange, dwEndRange, Search, Replace);
        if (Status)
            MemoryLogs = type + " - Disable !";
        else
            MemoryLogs = type + " : Failed to Enable!";

        CloseHandle(ProcessHandle);
    }

    void deWrite(std::string type, DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* Search, BYTE* Replace)
    {
        if (!AttackProcess(GetEmulatorRunning()))
            MemoryLogs = type + ": An unexpected error occurred";;

        bool Status = ReplacePattern(dwStartRange, dwEndRange, Search, Replace);
        if (Status)
            MemoryLogs = type + " - Disabled!";
        else
            MemoryLogs = type + " : Failed to Disable!";

        CloseHandle(ProcessHandle);
    }

    BOOL AttackProcess(const char* procname)
    {
        const char* emulator = GetEmulatorRunning();
        if (emulator == nullptr) 
            return false;

        DWORD ProcId = GetPid(emulator);
        if (ProcId == 0)
            return false;

        ProcessId = ProcId;
        ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessId);
        return ProcessHandle != nullptr;
    }

    bool ReplacePattern(DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* SearchAob, BYTE* ReplaceAob)
    {
        int RepByteSize = _msize(ReplaceAob);
        if (RepByteSize <= 0) return false;
        std::vector<DWORD_PTR> foundedAddress;
        FindPattern(dwStartRange, dwEndRange, SearchAob, foundedAddress);
        if (foundedAddress.empty())
            return false;

        DWORD OldProtect;
        for (int i = 0; i < foundedAddress.size(); i++)
        {
            ZwProtectVirtualMemory(ProcessHandle, (LPVOID)foundedAddress[i], RepByteSize, PAGE_EXECUTE_READWRITE, &OldProtect);
            ZwWriteVirtualMemory(ProcessHandle, (LPVOID)foundedAddress[i], ReplaceAob, RepByteSize, 0);
            ZwProtectVirtualMemory(ProcessHandle, (LPVOID)foundedAddress[i], RepByteSize, PAGE_EXECUTE_READ, &OldProtect);
        }

        return true;
    }


    bool ChangePattern(DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* Search, BYTE* Replace)
    {
        if (!AttackProcess(GetEmulatorRunning())) return false;

        bool Status = ReplacePattern(dwStartRange, dwEndRange, Search, Replace);
        if (Status) return true;
        else return false;

        CloseHandle(ProcessHandle);
    }

    bool HookPattern(DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* SearchAob, BYTE* ReplaceAob, std::vector<DWORD_PTR>& AddressRet)
    {
        if (!AttackProcess(GetEmulatorRunning())) return false;
        int RepByteSize = _msize(ReplaceAob);
        if (RepByteSize <= 0) return false;

        if (AddressRet.empty())
        {
            FindPattern(dwStartRange, dwEndRange, SearchAob, AddressRet);
            if (AddressRet.empty()) return false;

            DWORD OldProtect;
            for (int i = 0; i < AddressRet.size(); i++)
            {
                WriteProcessMemory(ProcessHandle, (LPVOID)AddressRet[i], ReplaceAob, RepByteSize, 0);
            }

            return true;
        }
        else {
            DWORD OldProtect;
            for (int i = 0; i < AddressRet.size(); i++)
            {
                WriteProcessMemory(ProcessHandle, (LPVOID)AddressRet[i], ReplaceAob, RepByteSize, 0);
            }
            return true;
        }
        CloseHandle(ProcessHandle);
    }

    bool FindPattern(DWORD_PTR StartRange, DWORD_PTR EndRange, BYTE* SearchBytes, std::vector<DWORD_PTR>& AddressRet) {
        MEMORY_BASIC_INFORMATION mbi;
        mbi.RegionSize = 0x1000;
        DWORD_PTR dwAddress = StartRange;
        DWORD_PTR nSearchSize = _msize(SearchBytes);

        std::vector<MEMORY_REGION> m_vMemoryRegion;

        // Collect all memory regions
        while (VirtualQueryEx(ProcessHandle, (LPCVOID)dwAddress, &mbi, sizeof(mbi)) && (dwAddress < EndRange) && ((dwAddress + mbi.RegionSize) > dwAddress)) {
            if ((mbi.State == MEM_COMMIT) && ((mbi.Protect & PAGE_GUARD) == 0) && (mbi.Protect != PAGE_NOACCESS) && ((mbi.AllocationProtect & PAGE_NOCACHE) != PAGE_NOCACHE)) {
                MEMORY_REGION mData = { (DWORD_PTR)mbi.BaseAddress, mbi.RegionSize };
                m_vMemoryRegion.push_back(mData);
            }
            dwAddress = (DWORD_PTR)mbi.BaseAddress + mbi.RegionSize;
        }

        std::mutex mtx;

        auto processRegion = [&](MEMORY_REGION mData) {
            BYTE* pCurrMemoryData = new BYTE[mData.dwMemorySize];
            ZeroMemory(pCurrMemoryData, mData.dwMemorySize);
            DWORD_PTR dwNumberOfBytesRead = 0;

            // Read process memory
            ReadProcessMemory(ProcessHandle, (LPCVOID)mData.dwBaseAddr, pCurrMemoryData, mData.dwMemorySize, &dwNumberOfBytesRead);
            if ((int)dwNumberOfBytesRead > 0) {
                DWORD_PTR dwOffset = 0;
                int iOffset = Memfind(pCurrMemoryData, dwNumberOfBytesRead, SearchBytes, nSearchSize);
                while (iOffset != -1) {
                    dwOffset += iOffset;
                    DWORD_PTR firstByteAddress = dwOffset + mData.dwBaseAddr;

                    std::lock_guard<std::mutex> lock(mtx);
                    AddressRet.push_back(firstByteAddress);

                    dwOffset += nSearchSize;
                    iOffset = Memfind(pCurrMemoryData + dwOffset, dwNumberOfBytesRead - dwOffset - nSearchSize, SearchBytes, nSearchSize);
                }
            }

            delete[] pCurrMemoryData;
            };

        // Launch threads to process memory regions concurrently
        std::vector<std::future<void>> futures;
        for (const auto& region : m_vMemoryRegion) {
            futures.push_back(std::async(std::launch::async, processRegion, region));
        }


        for (auto& fut : futures)
        {
            fut.get();
        }

        return true;
    }
    int Memfind(BYTE* buffer, DWORD_PTR dwBufferSize, BYTE* bstr, DWORD_PTR dwStrLen) {
        if (dwBufferSize < 0) {
            return -1;
        }
        DWORD_PTR  i, j;
        for (i = 0; i < dwBufferSize; i++) {
            for (j = 0; j < dwStrLen; j++) {
                if (buffer[i + j] != bstr[j] && bstr[j] != '?')
                    break;

            }
            if (j == dwStrLen)
                return i;
        }
        return -1;
    }
};
