#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>
#include <thread>
#include <chrono>

#define WIN32_LEAN_AND_MEAN
#include <winternl.h>



#pragma comment(lib, "ntdll.lib")



extern "C" NTSTATUS ZwReadVirtualMemory(
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    void* lpBuffer,
    SIZE_T nSize,
    SIZE_T* lpNumberOfBytesRead
);


extern "C" NTSTATUS ZwWriteVirtualMemory(
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    void* lpBuffer,
    SIZE_T nSize,
    SIZE_T* lpNumberOfBytesWritten
);


extern "C" NTSTATUS ZwProtectVirtualMemory(
    HANDLE hProcess,
    LPVOID BaseAddress,
    SIZE_T NumberOfBytesToProtect,
    ULONG NewAccessProtection,
    PULONG OldAccessProtection
);

class Memoryh
{
public:
    DWORD  ProcessId = 0;
    HANDLE ProcessHandle = nullptr;

    struct MEMORY_REGION
    {
        DWORD_PTR dwBaseAddr;
        DWORD_PTR dwMemorySize;
    };

    

    int GetPid(const char* procname)
    {
        if (!procname)
            return 0;

        DWORD pid = 0;
        DWORD maxThreads = 0;

        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe{};
        pe.dwSize = sizeof(pe);

        if (Process32First(snap, &pe))
        {
            do
            {
                if (_tcsicmp(pe.szExeFile, procname) == 0)
                {
                    if (pe.cntThreads > maxThreads)
                    {
                        maxThreads = pe.cntThreads;
                        pid = pe.th32ProcessID;
                    }
                }
            } while (Process32Next(snap, &pe));
        }

        CloseHandle(snap);
        return pid;
    }

    const char* GetEmulatorRunning()
    {
        if (GetPid("HD-Player.exe"))        return "HD-Player.exe";
        if (GetPid("LdVBoxHeadless.exe"))   return "LdVBoxHeadless.exe";
        if (GetPid("MEmuHeadless.exe"))     return "MEmuHeadless.exe";
        if (GetPid("AndroidProcess.exe"))  return "AndroidProcess.exe";
        if (GetPid("aow_exe.exe"))          return "aow_exe.exe";
        if (GetPid("NoxVMHandle.exe"))      return "NoxVMHandle.exe";
        return nullptr;
    }

    BOOL AttackProcess(const char* procname)
    {
        if (!procname)
            return FALSE;

        ProcessId = GetPid(procname);
        if (!ProcessId)
            return FALSE;

        ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
        return ProcessHandle != nullptr;
    }

   

    std::vector<DWORD_PTR> Newspeed;

    bool SaveScope()
    {
        SYSTEM_INFO si;
        GetSystemInfo(&si);

        DWORD_PTR start = (DWORD_PTR)si.lpMinimumApplicationAddress;
        DWORD_PTR end = (DWORD_PTR)si.lpMaximumApplicationAddress;

        std::vector<BYTE> pattern =
        {
            0xCC,0x3D,0x06,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x80,0x3F,0x33,0x33,0x13,0x40,
            0x00,0x00,0xB0,0x3F,
            0x00,0x00,0x80,0x3F
        };


        const char* emu = GetEmulatorRunning();
        if (!emu || !AttackProcess(emu))
        {
            Beep(500, 300);
            return false;
        }

        Newspeed.clear();

        if (!FindPattern(start, end, pattern.data(), Newspeed) || Newspeed.empty())
        {
           
            return false;
        }

        
        Beep(1000, 300);

       
        return true;
    }

    bool EnableScope()
    {
        if (Newspeed.empty())
            return false;

        BYTE enable[2] = { 0xFF, 0xFF };
        BYTE disable[2] = { 0x00, 0x00 };

        for (auto addr : Newspeed)
        {
            ZwWriteVirtualMemory(
                ProcessHandle,
                (LPVOID)(addr + 8), 
                enable,
                sizeof(enable),
                nullptr
            );
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        for (auto addr : Newspeed)
        {
            ZwWriteVirtualMemory(
                ProcessHandle,
                (LPVOID)(addr + 8),
                disable,
                sizeof(disable),
                nullptr
            );
        }

        return true;
    }



    bool FindPattern(
        DWORD_PTR start,
        DWORD_PTR end,
        BYTE* pattern,
        std::vector<DWORD_PTR>& out
    )
    {
        MEMORY_BASIC_INFORMATION mbi{};
        DWORD_PTR address = start;

        SIZE_T patternSize = _msize(pattern);

        while (address < end &&
            VirtualQueryEx(ProcessHandle, (LPCVOID)address, &mbi, sizeof(mbi)))
        {
            if (mbi.State == MEM_COMMIT &&
                !(mbi.Protect & PAGE_GUARD) &&
                mbi.Protect != PAGE_NOACCESS)
            {
                std::vector<BYTE> buffer(mbi.RegionSize);
                SIZE_T bytesRead;

                if (ZwReadVirtualMemory(
                    ProcessHandle,
                    mbi.BaseAddress,
                    buffer.data(),
                    mbi.RegionSize,
                    &bytesRead) == 0)
                {
                    for (SIZE_T i = 0; i + patternSize < bytesRead; i++)
                    {
                        if (!memcmp(buffer.data() + i, pattern, patternSize))
                        {
                            out.push_back((DWORD_PTR)mbi.BaseAddress + i);
                        }
                    }
                }
            }

            address += mbi.RegionSize;
        }

        return !out.empty();
    }
};
