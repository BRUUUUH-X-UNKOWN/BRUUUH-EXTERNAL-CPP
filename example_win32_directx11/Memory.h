#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <TlHelp32.h>
#include <unordered_map>

class ArivMem {
public:
    DWORD ProcessId = 0;
    HANDLE ProcessHandle = nullptr;

    struct MEMORY_REGION {
        DWORD_PTR dwBaseAddr;
        DWORD_PTR dwMemorySize;
    };

    int GetPid(const char* procname) {
        if (!procname) return 0;
        DWORD pid = 0, threadCount = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 pe = { sizeof(pe) };
        if (Process32First(hSnap, &pe)) {
            do {
                if (_stricmp(pe.szExeFile, procname) == 0 && (int)pe.cntThreads > threadCount) {
                    threadCount = pe.cntThreads;
                    pid = pe.th32ProcessID;
                }
            } while (Process32Next(hSnap, &pe));
        }
        CloseHandle(hSnap);
        return pid;
    }

    const char* GetEmulatorRunning() {
        return GetPid("HD-Player.exe") ? "HD-Player.exe" : nullptr;
    }

    std::unordered_map<DWORD_PTR, int> originalValues;
    std::unordered_map<DWORD_PTR, int> modifiedValues;
    std::vector<DWORD_PTR> AddressScan;

    std::vector<BYTE> ScanAimbot = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x43 };

    void EnableAimHead() {
        notificationSystem.AddNotification("Aimbot Head", "Enabling", ImGui::GetColorU32(c::accent));
        // Clear previous scan results to ensure fresh AoB scan
        originalValues.clear();
        modifiedValues.clear();
        AddressScan.clear();

        if (!AttackProcess(GetEmulatorRunning())) {
            notificationSystem.AddNotification("Aimbot Head", "Emulator isn't running", ImGui::GetColorU32(c::accent));
            return;
        }

        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
        DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

        FindPattern(startAddress, endAddress, ScanAimbot.data(), AddressScan);

        if (AddressScan.empty()) {
            CloseHandle(ProcessHandle);
            notificationSystem.AddNotification("Aimbot Head", "No Players Found", ImGui::GetColorU32(c::accent));
            return;
        }

        for (auto currentAddress : AddressScan) {
            DWORD_PTR Nestax = 0xAA;  // Offset de escritura
            DWORD_PTR xNesta = 0xA6;  // Offset de lectura

            DWORD_PTR addressToSave = currentAddress + Nestax;
            DWORD_PTR addressToSave9 = currentAddress + xNesta;

            int buffer = 0;
            int buffer9 = 0;

            // Leer memoria y guardar valores originales
            SIZE_T bytesRead = 0;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressToSave, &buffer, sizeof(buffer), &bytesRead) && bytesRead == sizeof(buffer))
                originalValues[addressToSave] = buffer;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressToSave9, &buffer9, sizeof(buffer9), &bytesRead) && bytesRead == sizeof(buffer9))
                originalValues[addressToSave9] = buffer9;

            DWORD_PTR headBytes = currentAddress + xNesta;
            DWORD_PTR chestBytes = currentAddress + Nestax;

            int ValorCabeza = 0;
            int ChestValor = 0;

            DWORD oldProtect;
            SIZE_T bytesWritten = 0;

            // Leer valores actuales
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)headBytes, &ValorCabeza, sizeof(ValorCabeza), &bytesRead) && bytesRead == sizeof(ValorCabeza))
                originalValues[headBytes] = ValorCabeza;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)chestBytes, &ChestValor, sizeof(ChestValor), &bytesRead) && bytesRead == sizeof(ChestValor))
                originalValues[chestBytes] = ChestValor;

            // Cambiar permisos y escribir en memoria
            VirtualProtectEx(ProcessHandle, (LPVOID)chestBytes, sizeof(ValorCabeza), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)chestBytes, &ValorCabeza, sizeof(ValorCabeza), &bytesWritten) && bytesWritten == sizeof(ValorCabeza))
                modifiedValues[chestBytes] = ValorCabeza;
            VirtualProtectEx(ProcessHandle, (LPVOID)chestBytes, sizeof(ValorCabeza), oldProtect, &oldProtect);

            VirtualProtectEx(ProcessHandle, (LPVOID)headBytes, sizeof(ChestValor), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)headBytes, &ChestValor, sizeof(ChestValor), &bytesWritten) && bytesWritten == sizeof(ChestValor))
                modifiedValues[headBytes] = ChestValor;
            VirtualProtectEx(ProcessHandle, (LPVOID)headBytes, sizeof(ChestValor), oldProtect, &oldProtect);

            // Guardar valores modificados
            int buffer1 = 0;
            int buffer19 = 0;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressToSave, &buffer1, sizeof(buffer1), &bytesRead) && bytesRead == sizeof(buffer1))
                modifiedValues[addressToSave] = buffer1;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressToSave9, &buffer19, sizeof(buffer19), &bytesRead) && bytesRead == sizeof(buffer19))
                modifiedValues[addressToSave9] = buffer19;
        }
        notificationSystem.AddNotification("Aimbot Head", "Enabled", ImGui::GetColorU32(c::accent));
        CloseHandle(ProcessHandle);
    }

    void EnableAimDrag() {
        // Clear previous scan results to ensure fresh AoB scan
        originalValues.clear();
        modifiedValues.clear();
        AddressScan.clear();

        if (!AttackProcess(GetEmulatorRunning())) {
            return;
        }

        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR SAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
        DWORD_PTR EAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

        FindPattern(SAddress, EAddress, ScanAimbot.data(), AddressScan);

        if (AddressScan.empty()) {
            CloseHandle(ProcessHandle);
            return;
        }

        for (size_t i = 0; i < AddressScan.size(); i++) {
            DWORD_PTR addressscan = AddressScan[i] + 0xDA;
            DWORD_PTR addressrep = AddressScan[i] + 0xA6;
            int bufferRead, bufferWrite;
            SIZE_T bytesRead = 0, bytesWritten = 0;
            DWORD oldProtect;

            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressscan, &bufferRead, sizeof(bufferRead), &bytesRead) && bytesRead == sizeof(bufferRead))
                originalValues[addressscan] = bufferRead;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressrep, &bufferWrite, sizeof(bufferWrite), &bytesRead) && bytesRead == sizeof(bufferWrite))
                originalValues[addressrep] = bufferWrite;

            VirtualProtectEx(ProcessHandle, (LPVOID)addressscan, sizeof(bufferRead), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)addressscan, &bufferWrite, sizeof(bufferWrite), &bytesWritten) && bytesWritten == sizeof(bufferWrite))
                modifiedValues[addressscan] = bufferWrite;
            VirtualProtectEx(ProcessHandle, (LPVOID)addressscan, sizeof(bufferRead), oldProtect, &oldProtect);

            VirtualProtectEx(ProcessHandle, (LPVOID)addressrep, sizeof(bufferRead), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)addressrep, &bufferRead, sizeof(bufferRead), &bytesWritten) && bytesWritten == sizeof(bufferRead))
                modifiedValues[addressrep] = bufferRead;
            VirtualProtectEx(ProcessHandle, (LPVOID)addressrep, sizeof(bufferRead), oldProtect, &oldProtect);
        }
        CloseHandle(ProcessHandle);
    }

    void EnableAimDragPro() {
        // Clear previous scan results to ensure fresh AoB scan
        originalValues.clear();
        modifiedValues.clear();
        AddressScan.clear();

        if (!AttackProcess(GetEmulatorRunning())) {
            return;
        }

        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD_PTR SAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
        DWORD_PTR EAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

        FindPattern(SAddress, EAddress, ScanAimbot.data(), AddressScan);

        if (AddressScan.empty()) {
            CloseHandle(ProcessHandle);
            return;
        }

        for (size_t i = 0; i < AddressScan.size(); i++) {
            DWORD_PTR addressscan = AddressScan[i] + 0xE6;
            DWORD_PTR addressrep = AddressScan[i] + 0xA6;
            int bufferRead, bufferWrite;
            SIZE_T bytesRead = 0, bytesWritten = 0;
            DWORD oldProtect;

            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressscan, &bufferRead, sizeof(bufferRead), &bytesRead) && bytesRead == sizeof(bufferRead))
                originalValues[addressscan] = bufferRead;
            if (ReadProcessMemory(ProcessHandle, (LPCVOID)addressrep, &bufferWrite, sizeof(bufferWrite), &bytesRead) && bytesRead == sizeof(bufferWrite))
                originalValues[addressrep] = bufferWrite;

            VirtualProtectEx(ProcessHandle, (LPVOID)addressscan, sizeof(bufferRead), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)addressscan, &bufferWrite, sizeof(bufferWrite), &bytesWritten) && bytesWritten == sizeof(bufferWrite))
                modifiedValues[addressscan] = bufferWrite;
            VirtualProtectEx(ProcessHandle, (LPVOID)addressscan, sizeof(bufferRead), oldProtect, &oldProtect);

            VirtualProtectEx(ProcessHandle, (LPVOID)addressrep, sizeof(bufferRead), PAGE_EXECUTE_READWRITE, &oldProtect);
            if (WriteProcessMemory(ProcessHandle, (LPVOID)addressrep, &bufferRead, sizeof(bufferRead), &bytesWritten) && bytesWritten == sizeof(bufferRead))
                modifiedValues[addressrep] = bufferRead;
            VirtualProtectEx(ProcessHandle, (LPVOID)addressrep, sizeof(bufferRead), oldProtect, &oldProtect);
        }
        CloseHandle(ProcessHandle);
    }

    void Restore() {
        if (!AttackProcess(GetEmulatorRunning())) {
            return;
        }
        for (const auto& entry : originalValues) {
            DWORD_PTR address = entry.first;
            int originalValue = entry.second;
            SIZE_T bytesWritten = 0;
            DWORD oldProtect;
            VirtualProtectEx(ProcessHandle, (LPVOID)address, sizeof(originalValue), PAGE_EXECUTE_READWRITE, &oldProtect);
            WriteProcessMemory(ProcessHandle, (LPVOID)address, &originalValue, sizeof(originalValue), &bytesWritten);
            VirtualProtectEx(ProcessHandle, (LPVOID)address, sizeof(originalValue), oldProtect, &oldProtect);
        }
        CloseHandle(ProcessHandle);
    }

    void Reapply() {
        if (!AttackProcess(GetEmulatorRunning())) {
            return;
        }
        for (const auto& entry : modifiedValues) {
            DWORD_PTR address = entry.first;
            int valueToReapply = entry.second;
            SIZE_T bytesWritten = 0;
            DWORD oldProtect;
            VirtualProtectEx(ProcessHandle, (LPVOID)address, sizeof(valueToReapply), PAGE_EXECUTE_READWRITE, &oldProtect);
            WriteProcessMemory(ProcessHandle, (LPVOID)address, &valueToReapply, sizeof(valueToReapply), &bytesWritten);
            VirtualProtectEx(ProcessHandle, (LPVOID)address, sizeof(valueToReapply), oldProtect, &oldProtect);
        }
        CloseHandle(ProcessHandle);
    }

    bool ModifyMemory(DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* Search, BYTE* Replace) {
        if (!AttackProcess(GetEmulatorRunning())) return false;
        bool Status = ReplacePattern(dwStartRange, dwEndRange, Search, Replace);
        if (Status)
            CloseHandle(ProcessHandle);
        return Status;
    }

    bool AttackProcess(const char* procname) {
        DWORD ProcId = GetPid(procname);
        if (!ProcId) return false;
        ProcessId = ProcId;
        ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
        return ProcessHandle != nullptr;
    }

    bool ReplacePattern(DWORD_PTR dwStartRange, DWORD_PTR dwEndRange, BYTE* SearchAob, BYTE* ReplaceAob) {
        SIZE_T RepByteSize = _msize(ReplaceAob);
        if (RepByteSize <= 0) return false;
        std::vector<DWORD_PTR> foundedAddress;
        FindPattern(dwStartRange, dwEndRange, SearchAob, foundedAddress);
        if (foundedAddress.empty()) return false;
        for (auto address : foundedAddress) {
            DWORD oldProtect;
            VirtualProtectEx(ProcessHandle, (LPVOID)address, RepByteSize, PAGE_EXECUTE_READWRITE, &oldProtect);
            WriteProcessMemory(ProcessHandle, (LPVOID)address, ReplaceAob, RepByteSize, nullptr);
            VirtualProtectEx(ProcessHandle, (LPVOID)address, RepByteSize, oldProtect, &oldProtect);
        }
        return true;
    }

    bool FindPattern(DWORD_PTR StartRange, DWORD_PTR EndRange, BYTE* SearchBytes, std::vector<DWORD_PTR>& AddressRet) {
        BYTE* pCurrMemoryData = nullptr;
        MEMORY_BASIC_INFORMATION mbi = { 0 };
        std::vector<MEMORY_REGION> m_vMemoryRegion;
        mbi.RegionSize = 0x1000;
        DWORD_PTR dwAddress = StartRange;
        SIZE_T nSearchSize = _msize(SearchBytes);

        while (VirtualQueryEx(ProcessHandle, (LPCVOID)dwAddress, &mbi, sizeof(mbi)) && dwAddress < EndRange) {
            if (mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_GUARD) && mbi.Protect != PAGE_NOACCESS)
                m_vMemoryRegion.push_back({ (DWORD_PTR)mbi.BaseAddress, mbi.RegionSize });
            dwAddress = (DWORD_PTR)mbi.BaseAddress + mbi.RegionSize;
        }

        for (const auto& mData : m_vMemoryRegion) {
            pCurrMemoryData = new BYTE[mData.dwMemorySize];
            ZeroMemory(pCurrMemoryData, mData.dwMemorySize);
            SIZE_T dwNumberOfBytesRead = 0;
            ReadProcessMemory(ProcessHandle, (LPCVOID)mData.dwBaseAddr, pCurrMemoryData, mData.dwMemorySize, &dwNumberOfBytesRead);
            if (dwNumberOfBytesRead > 0) {
                DWORD_PTR dwOffset = 0;
                int iOffset = Memfind(pCurrMemoryData, dwNumberOfBytesRead, SearchBytes, nSearchSize);
                while (iOffset != -1) {
                    dwOffset += iOffset;
                    AddressRet.push_back(dwOffset + mData.dwBaseAddr);
                    dwOffset += nSearchSize;
                    iOffset = Memfind(pCurrMemoryData + dwOffset, dwNumberOfBytesRead - dwOffset - nSearchSize, SearchBytes, nSearchSize);
                }
            }
            delete[] pCurrMemoryData;
        }
        return !AddressRet.empty();
    }

    int Memfind(BYTE* buffer, SIZE_T dwBufferSize, BYTE* bstr, SIZE_T dwStrLen) {
        for (SIZE_T i = 0; i < dwBufferSize; i++) {
            for (SIZE_T j = 0; j < dwStrLen; j++) {
                if (buffer[i + j] != bstr[j] && bstr[j] != '?') break;
                if (j == dwStrLen - 1) return i;
            }
        }
        return -1;
    }
};