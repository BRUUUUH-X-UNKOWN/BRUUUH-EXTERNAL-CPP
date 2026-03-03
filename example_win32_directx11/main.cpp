#define IMGUI_DEFINE_MATH_OPERATORS

//MAIN
#include "main.h"
#include "image.h"

//Auth
#include "auth/AuthlyX.h"

#include "ShadowxCheats.h"
//#include "../../AOBCheatSystem.h"

#include <fstream>
#include "Sniper Macro C++.h"



//Key Binds
static int aim_head;
static int aim_neck;
static int aim_drag;

static int wall_hack;
static int speed_hack;
static int camera_hack;

static int fakelag_key;
static int streamer_mode;

//Checkboxes
static bool aimbot_h = false;
static bool aimbot_d = false;
static bool aimbot_n = false;
static bool noRecoil = false;
static bool aimbot_b = false;

static bool aimbot_2x = false;
static bool aimbot_4x = false;

static bool unlimitedAmmo = false;
static bool fastReload = false;
static bool femaleFix = false;
static bool resetGuest = false;
static bool glitchFire = false;


static bool loadWallHack = false;
static bool wallHack = false;
static bool loadSpeedHack = false;
static bool speedHack = false;
static bool loadCameraLeft = false;
static bool CameraLeft = false;
static bool blueCrosshair = false;

static bool fastfire = false;
static bool fastRevive = false;
static bool fastLanding = false;
static bool sniperScope = false;
static bool sniperSwitch = false;
static bool sniperAim = false;
static bool sniperDelay = false;
static bool sniperLocation = false;
static bool awmLocation = false;
static bool awmyLocation = false;
static bool vsk94Location = false;
static bool M82BLocation = false;
static std::vector<DWORD_PTR> wallhackAddress;
static std::vector<DWORD_PTR> speedhackAddress;
static std::vector<DWORD_PTR> cameraleftAddress;

ShadowBrutal mem;
ArivMem ariv;
Memoryh sniper_macro;


AuthlyX AuthlyXApp(
    "469e4d9235d1",
    "EXTERNAL",
    "8.6",
    "BcO8UJa9Vb94IJM9FiAF1eAPaZ552HXzwG47RHZ6"
);



namespace texture
{
    ID3D11ShaderResourceView* JINO = nullptr;
    ID3D11ShaderResourceView* logo = nullptr;
    ID3D11ShaderResourceView* logo12 = nullptr;

}

static float fakelag2 = 2.0f;

namespace esp
{
    bool money = true;
    bool nickname = true;
    bool weapon = true;
    bool zoom = true;

    bool c4 = true;
    bool HP_line = true;
    bool hit = true;
    bool box = true;
    bool bomb = true;

    static float box_color[4] = { 37 / 255.f, 37 / 255.f, 47 / 255.f, 1.f };
    static float nick_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float money_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float zoom_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float c4_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float bomb_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float hp_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float hp_line_color[4] = { 112 / 255.f, 109 / 255.f, 214 / 255.f, 1.f };
    static float weapon_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };
    static float hit_color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };

    int hp = 85;
}

int page = 0;

static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

std::string btn_txt = "Login";

DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

bool done = false;
bool fake_lag;
bool show_menu = true;
static bool streammode = false;
static bool autosave = false;
static bool sound = false;
static bool discordrpc= true;
bool disableAllAnimations = false;
static bool disableParticles = false;
static bool disableCheckboxEffects = false;


static std::string bodyType = "None";
static std::string LocationType = "None";
static std::string LocationMode = "Off";
static std::string chamsMenuType = "None";
static std::string sniperSwitchType = "V1";

static const char* emulatorDisplayNames[] = {
    "Automatic", "BlueStacks", "MSI", "MEmu", "LD Player",
    "GameLoop", "NoxPlayer", "Genymotion", "Andy",
    "Droid4X", "KoPlayer", "SmartGaGa"
};
static const char* emulatorProcessNames[] = {
    "Automatic",         // 0 - Automatic
    "HD-Player",         // 1 - BlueStacks
    "HD-Player",         // 2 - MSI
    "MEmuHeadless",      // 3 - MEmu
    "LdBoxHeadless",     // 4 - LD Player
    "AndroidEmulatorEn", // 5 - GameLoop
    "NoxVMHandle",       // 6 - NoxPlayer
    "VBoxHeadless",      // 7 - Genymotion
    "VBoxHeadless",      // 8 - Andy
    "Droid4X",           // 9 - Droid4X
    "KoPlayer",          // 10 - KoPlayer
    "ProjectTitan"       // 11 - SmartGaGa
};
static int emulatorSelected = 0;
static std::string g_targetProcess = "";

static std::string GetAutoProcessName() {
    static const char* candidates[] = {
        "HD-Player", "MEmuHeadless", "LdBoxHeadless",
        "AndroidEmulatorEn", "NoxVMHandle", "VBoxHeadless",
        "Droid4X", "KoPlayer", "ProjectTitan"
    };
    for (auto& name : candidates) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) continue;
        PROCESSENTRY32 pe = { sizeof(pe) };
        if (Process32First(snap, &pe)) {
            do {
                std::string pname = pe.szExeFile;
                if (pname.size() > 4 && pname.substr(pname.size()-4) == ".exe")
                    pname = pname.substr(0, pname.size()-4);
                if (pname == name) { CloseHandle(snap); return name; }
            } while (Process32Next(snap, &pe));
        }
        CloseHandle(snap);
    }
    return "HD-Player";
}

static std::string GetTargetProcess() {
    if (emulatorSelected == 0) {
        // Automatic
        return GetAutoProcessName() + ".exe";
    }
    return std::string(emulatorProcessNames[emulatorSelected]) + ".exe";
}

static float color[4] = { 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.f };

struct AppConfig {
    std::string licenseKey = "";
    std::string aimbotBodyType = "None";
    std::string chamsMenuType = "None";
    std::string sniperSwitchType = "V1";
    std::string fakeLagMode = "Automatic";
    std::string sniperLocationType = "None";
    std::string sniperLocationMode = "Off";
    std::string emulatorMode = "Automatic";
    bool Sound = false;
    bool discordRPC = true;
    bool disableAllAnimations = false;
    bool streamerMode = false;
    bool autoSave = true;

    float colorR = 255.0f / 255.0f;
    float colorG = 255.0f / 255.0f;
    float colorB = 255.0f / 255.0f;
    float colorA = 1.0f;
};

AppConfig currentConfig;

bool initialized = false;
bool initialized2 = false;
bool authed = false;

#pragma region Menu
void EnableAimbotHead()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Head", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x43 };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Head", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xAA), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xAA), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xA6), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xA6), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Head", "Enabled", ImGui::GetColorU32(c::accent));
    }
    else {
        notificationSystem.AddNotification("Aimbot Head", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableAimbotHead()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Head", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x43 };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Head", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xA6), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xA6), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xAA), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0xAA), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Head", "Disabled", ImGui::GetColorU32(c::accent));
    }
    else {
        notificationSystem.AddNotification("Aimbot Head", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void EnableAimbotDrag()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Drag", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x43 };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Drag", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x80), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x80), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x7C), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x7C), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();

        notificationSystem.AddNotification("Aimbot Drag", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Aimbot Drag", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableAimbotDrag()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Drag", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA5, 0x43 };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Drag", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x7C), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x7C), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x80), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x80), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();

        notificationSystem.AddNotification("Aimbot Drag", "Disabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Aimbot Drag", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void EnableAimbotNeck()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Neck", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xA5, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Neck", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x2A), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x2A), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x26), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x26), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();

        notificationSystem.AddNotification("Aimbot Neck", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Aimbot Neck", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableAimbotNeck()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;
    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Aimbot Neck", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<DWORD_PTR> aimbot_new;
        std::vector<BYTE> SearchAimbot = { 0xA5, 0x43, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F };
        mem.FindPattern(startAddress, endAddress, SearchAimbot.data(), aimbot_new);
        if (aimbot_new.empty()) {
            notificationSystem.AddNotification("Aimbot Neck", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            return;
        }
        for (auto result : aimbot_new) {
            int value1, value2;
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x26), &value1, sizeof(value1), NULL);
            ReadProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x26), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x2A), &value2, sizeof(value2), NULL);
            WriteProcessMemory(mem.ProcessHandle, (LPVOID)(result + 0x2A), &value1, sizeof(value1), NULL);
        }
        aimbot_new.clear();

        notificationSystem.AddNotification("Aimbot Neck", "Disabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Aimbot Neck", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void EnableNoRecoil()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("No Recoil", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
        0x7A, 0x44, 0xF0, 0x48, 0x2D, 0xE9, 0x10, 0xB0, 0x8D, 0xE2, 0x02, 0x8B, 0x2D, 0xED, 0x08, 0xD0
        };
        std::vector<BYTE> replace = {
            0x7A, 0xFF, 0xF0, 0x48, 0x2D, 0xE9, 0x10, 0xB0, 0x8D, 0xE2, 0x02, 0x8B, 0x2D, 0xED, 0x08, 0xD0
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) {


            }
            notificationSystem.AddNotification("No Recoil", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("No Recoil", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("No Recoil", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    
}
void DisableNoRecoil()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("No Recoil", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
        0x7A, 0xFF, 0xF0, 0x48, 0x2D, 0xE9, 0x10, 0xB0, 0x8D, 0xE2, 0x02, 0x8B, 0x2D, 0xED, 0x08, 0xD0
        };
        std::vector<BYTE> search = {
            0x7A, 0x44, 0xF0, 0x48, 0x2D, 0xE9, 0x10, 0xB0, 0x8D, 0xE2, 0x02, 0x8B, 0x2D, 0xED, 0x08, 0xD0
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) {


            }
            notificationSystem.AddNotification("No Recoil", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("No Recoil", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("No Recoil", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    
}

void AimbotBody()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (!mem.AttackProcess(GetTargetProcess().c_str()))
    {
        notificationSystem.AddNotification("Aimbot Body", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        return;
    }

    notificationSystem.AddNotification("Aimbot Body", "Enabling", ImGui::GetColorU32(c::accent));

    std::vector<std::pair<std::vector<BYTE>, std::vector<BYTE>>> patches = {
        {{0xDC, 0x52, 0x39, 0xBD, 0x27, 0xC1, 0x8B, 0x3C, 0xC0, 0xD0, 0xF8, 0xB9}, {0x00, 0x00, 0x00, 0x3E, 0x0A, 0xD7, 0x23, 0x3D, 0xD2, 0xA5, 0xF9, 0xBC}},
        {{0x63, 0x71, 0xB0, 0xBD, 0x90, 0x98, 0x74, 0xBB, 0x00, 0x00, 0x80, 0xB3}, {0xCD, 0xDC, 0x79, 0x44, 0x90, 0x98, 0x74, 0xBB, 0x00, 0x00, 0x80, 0xB3}},
        {{0x5D, 0xC1, 0xAB, 0x2C, 0x09, 0x04, 0xFF, 0x18, 0xEF, 0xE5, 0x11, 0x59}, {0xCD, 0xDC, 0x79, 0x44, 0x58, 0x34, 0x09, 0xBB, 0xB0, 0x60, 0xBE, 0xBA}},
        {{0x7B, 0xF9, 0x6C, 0xBD, 0x58, 0x34, 0x09, 0xBB, 0xB0, 0x60, 0xBE, 0xBA}, {0xCD, 0xDC, 0x79, 0x44, 0x58, 0x34, 0x09, 0xBB, 0xB0, 0x60, 0xBE, 0xBA}},
        {{0x21, 0x60, 0x29, 0x1C, 0x80, 0xA2, 0xF4, 0x00, 0xC8, 0xD1, 0x85, 0xDE}, {0xCD, 0xDC, 0x79, 0x44, 0x58, 0x34, 0x09, 0xBB, 0xB0, 0x60, 0xBE, 0xBA}},
        {{0x13, 0x66, 0xCF, 0x2C, 0x2C, 0x79, 0xF9, 0x7E, 0x6C, 0xE1, 0xD5, 0x13}, {0xCD, 0xDC, 0x79, 0x44, 0x58, 0x34, 0x09, 0xBB, 0xB0, 0x60, 0xBE, 0xBA}},
        {{0x54, 0x1B, 0x87, 0xBD, 0x90, 0xC6, 0xD7, 0xBA, 0x80, 0x54, 0x99, 0xB9}, {0xCD, 0xDC, 0x79, 0x44, 0x90, 0xC6, 0xD7, 0xBA, 0x80, 0x54, 0x99, 0xB9}},
        {{0x71, 0x02, 0x87, 0xBD, 0x90, 0xFD, 0xD7, 0xBA, 0x40, 0x18, 0x98, 0x39}, {0xCD, 0xDC, 0x79, 0x44, 0x90, 0xFD, 0xD7, 0xBA, 0x40, 0x18, 0x98, 0x39}},
        {{0xCC, 0xF8, 0x6C, 0xBD, 0x40, 0xD2, 0xCE, 0xB9, 0x58, 0x64, 0xBE, 0x3A}, {0xCD, 0xDC, 0x79, 0x44, 0x40, 0xD2, 0xCE, 0xB9, 0x58, 0x64, 0xBE, 0x3A}},
        {{0x00, 0x00, 0x00, 0x00, 0x40, 0xD2, 0xCE, 0xB9, 0x58, 0x64, 0xBE, 0x3A}, {0xCD, 0xDC, 0x79, 0x44, 0x40, 0xD2, 0xCE, 0xB9, 0x58, 0x64, 0xBE, 0x3A}},
        {{0x76, 0xFC, 0xDB, 0xBC, 0x7C, 0x5E, 0x8B, 0x3A, 0x50, 0x8B, 0xBB, 0x3A}, {0xCD, 0xDC, 0x79, 0x44, 0x7C, 0x5E, 0x8B, 0x3A, 0x50, 0x8B, 0xBB, 0x3A}},
        {{0x80, 0x13, 0x95, 0xBC, 0x30, 0xFF, 0x37, 0xBB, 0x00, 0xFD, 0x78, 0x3B}, {0xCD, 0xDC, 0x79, 0x44, 0x30, 0xFF, 0x37, 0xBB, 0x00, 0xFD, 0x78, 0x3B}},
        {{0x1F, 0x93, 0xDB, 0xBC, 0x90, 0xBF, 0x84, 0x3A, 0x20, 0xA6, 0xBB, 0xBA}, {0xCD, 0xDC, 0x79, 0x44, 0x90, 0xBF, 0x84, 0x3A, 0x20, 0xA6, 0xBB, 0xBA}},
        {{0xEF, 0xA3, 0x00, 0xBE, 0x40, 0xB9, 0x92, 0x39, 0x20, 0x4E, 0x07, 0xBA}, {0xCD, 0xDC, 0x79, 0x44, 0x40, 0xB9, 0x92, 0x39, 0x20, 0x4E, 0x07, 0xBA}},
        {{0xBC, 0x19, 0xFD, 0xBD, 0xB0, 0xE3, 0xA9, 0x3A, 0x80, 0x42, 0x23, 0xB9}, {0xCD, 0xDC, 0x79, 0x44, 0xB0, 0xE3, 0xA9, 0x3A, 0x80, 0x42, 0x23, 0xB9}}
    };

    bool anySuccess = false;
    int currentStep = 1;
    int totalSteps = patches.size();

    for (auto& patch : patches)
    {
        std::string progressMsg = "Enabling " + std::to_string(currentStep) + "/" + std::to_string(totalSteps);
        notificationSystem.AddNotification("Aimbot Body", progressMsg.c_str(), ImGui::GetColorU32(c::accent));

        if (mem.ReplacePattern(startAddress, endAddress, patch.first.data(), patch.second.data()))
        {
            anySuccess = true;
        }
        currentStep++;
    }


    if (anySuccess)
    {
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Body", "Enabled", ImGui::GetColorU32(c::accent));
    }
    else
    {
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Body", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
    }
}
void AimbotBodyV2()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str()))
    {
        notificationSystem.AddNotification("Aimbot Body V2", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        return;
    }

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    notificationSystem.AddNotification("Aimbot Body V2", "Enabling", ImGui::GetColorU32(c::accent));

    std::vector<std::pair<std::vector<BYTE>, std::vector<BYTE>>> patchesV2 = {
        {{0xdc, 0x52, 0x39, 0xbd, 0x27, 0xc1, 0x8b, 0x3c, 0xc0, 0xd0, 0xf8, 0xb9}, {0xdb, 0x42, 0x32, 0x3e, 0x33, 0xc1, 0x18, 0x3c, 0xc2, 0xd0, 0xf7, 0xb3}},
        {{0x63, 0x71, 0xb0, 0xbd, 0x90, 0x98, 0x74, 0xbb}, {0xcd, 0xdc, 0x79, 0x44, 0x90, 0x98, 0x74, 0xbb}},
        {{0x7b, 0xf9, 0x6c, 0xbd, 0x58, 0x34, 0x09, 0xbb, 0xb0, 0x60, 0xbe, 0xba}, {0xcd, 0xdc, 0x79, 0x44, 0x58, 0x34, 0x09, 0xbb, 0xb0, 0x60, 0xbe, 0xba}},
        {{0x54, 0x1b, 0x87, 0xbd, 0x90, 0xc6, 0xd7, 0xba, 0x80, 0x54, 0x99, 0xb9}, {0xcd, 0xdc, 0x79, 0x44, 0x90, 0xc6, 0xd7, 0xba, 0x80, 0x54, 0x99, 0xb9}},
        {{0x71, 0x02, 0x87, 0xbd, 0x90, 0xfd, 0xd7, 0xba, 0x40, 0x18, 0x98, 0x39}, {0xcd, 0xdc, 0x79, 0x44, 0x90, 0xfd, 0xd7, 0xba, 0x40, 0x18, 0x98, 0x39}},
        {{0xcc, 0xf8, 0x6c, 0xbd, 0x40, 0xd2, 0xce, 0xb9, 0x58, 0x64, 0xbe, 0x3a}, {0xcd, 0xdc, 0x79, 0x44, 0x40, 0xd2, 0xce, 0xb9, 0x58, 0x64, 0xbe, 0x3a}},
        {{0x76, 0xfc, 0xdb, 0xbc, 0x7c, 0x5e, 0x8b, 0x3a, 0x50, 0x8b, 0xbb, 0x3a}, {0xcd, 0xdc, 0x79, 0x44, 0x7c, 0x5e, 0x8b, 0x3a, 0x50, 0x8b, 0xbb, 0x3a}},
        {{0x80, 0x13, 0x95, 0xbc, 0x30, 0xff, 0x37, 0xbb, 0x00, 0xfd, 0x78, 0x3b}, {0xcd, 0xdc, 0x79, 0x44, 0x30, 0xff, 0x37, 0xbb, 0x00, 0xfd, 0x78, 0x3b}},
        {{0x1f, 0x93, 0xdb, 0xbc, 0x90, 0xbf, 0x84, 0x3a, 0x20, 0xa6, 0xbb, 0xba}, {0xcd, 0xdc, 0x79, 0x44, 0x90, 0xbf, 0x84, 0x3a, 0x20, 0xa6, 0xbb, 0xba}},
        {{0xef, 0xa3, 0x00, 0xbe, 0x40, 0xb9, 0x92, 0x39, 0x20, 0x4e, 0x07, 0xba}, {0xcd, 0xdc, 0x79, 0x44, 0x40, 0xb9, 0x92, 0x39, 0x20, 0x4e, 0x07, 0xba}},
        {{0xbc, 0x19, 0xfd, 0xbd, 0xb0, 0xe3, 0xa9, 0x3a, 0x80, 0x42, 0x23, 0xb9}, {0x42, 0xe0, 0x56, 0x43, 0xb0, 0xe3, 0xa9, 0x3a, 0x80, 0x42, 0x23, 0xb9}},
        {{0x7d, 0x1a, 0x89, 0xbd, 0x50, 0x26, 0x9f, 0x3b}, {0x00, 0x00, 0x70, 0x41, 0x00, 0x00, 0x70, 0x41}},
        {{0x0e, 0xe4, 0xf2, 0xbd, 0xcd, 0x99, 0x04, 0xbc}, {0x00, 0x00, 0x70, 0x41, 0x00, 0x00, 0x70, 0x41}}
    };

    bool anySuccess = false;
    int currentStep = 1;
    int totalSteps = patchesV2.size();

    for (const auto& patch : patchesV2)
    {
        std::string progressMsg = "Enabling " + std::to_string(currentStep) + "/" + std::to_string(totalSteps);
        notificationSystem.AddNotification("Aimbot Body V2", progressMsg.c_str(), ImGui::GetColorU32(c::accent));

        if (mem.ReplacePattern(startAddress, endAddress, const_cast<BYTE*>(patch.first.data()), const_cast<BYTE*>(patch.second.data())))
        {
            anySuccess = true;
        }
        currentStep++;
    }


    if (anySuccess)
    {
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Body V2", "Enabled", ImGui::GetColorU32(c::accent));
    }
    else
    {
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        notificationSystem.AddNotification("Aimbot Body V2", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
    }
}

void EnableScopeTracking2X()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Scope Tracking 2X", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
        0x33, 0x33, 0x93, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x02, 0x00, 0x00, 0x00, 0xEC, 0x51, 0xB8, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x42, 0x00, 0x00, 0xC0, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01, 0x00
        };
        std::vector<BYTE> replace = {
            0x33, 0x33, 0x93, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x02, 0x00, 0x00, 0x00, 0xEC, 0x51, 0xB8, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x42, 0x00, 0x00, 0xC0, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x29, 0x5C, 0x01, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 2X", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 2X", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Scope Tracking 2X", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableScopeTracking2X()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Scope Tracking 2X", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
        0x33, 0x33, 0x93, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x02, 0x00, 0x00, 0x00, 0xEC, 0x51, 0xB8, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x42, 0x00, 0x00, 0xC0, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01, 0x00
        };
        std::vector<BYTE> search = {
            0x33, 0x33, 0x93, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, 0x02, 0x00, 0x00, 0x00, 0xEC, 0x51, 0xB8, 0x3D, 0xCD, 0xCC, 0x4C, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xA0, 0x42, 0x00, 0x00, 0xC0, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xF0, 0x3F, 0x00, 0x00, 0x29, 0x5C, 0x01, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 2X", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 2X", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Scope Tracking 2X", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableScopeTracking4X()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Scope Tracking 4X", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
        0x20, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, '?', 0x00, 0x00, 0x00, 0x29, 0x5C, 0x8F, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xD0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01
        };
        std::vector<BYTE> replace = {
            0x20, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, '?', 0x00, 0x00, 0x00, 0x29, 0x5C, 0x8F, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xD0, 0x3F, 0x00, 0x00, 0x80, 0x5C, 0x01
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 4X", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 4X", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Scope Tracking 4X", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableScopeTracking4X()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Scope Tracking 4X", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
        0x20, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, '?', 0x00, 0x00, 0x00, 0x29, 0x5C, 0x8F, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xD0, 0x3F, 0x00, 0x00, 0x80, 0x3F, 0x01
        };
        std::vector<BYTE> search = {
            0x20, 0x40, 0xCD, 0xCC, 0x8C, 0x3F, 0x8F, 0xC2, 0xF5, 0x3C, 0xCD, 0xCC, 0xCC, 0x3D, '?', 0x00, 0x00, 0x00, 0x29, 0x5C, 0x8F, 0x3D, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xF0, 0x41, 0x00, 0x00, 0x48, 0x42, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x13, 0x40, 0x00, 0x00, 0xD0, 0x3F, 0x00, 0x00, 0x80, 0x5C, 0x01
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 4X", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Scope Tracking 4X", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Scope Tracking 4X", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableFastFire()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Fire", "Enabling", ImGui::GetColorU32(c::accent));
        
        std::vector<BYTE> search = { 0x00, 0x00, 0x80, 0x40, 0x33, 0x33, 0x93, 0x40, 0x3D, 0x0A, 0xF7, 0x3F };
        std::vector<BYTE> replace = { 0x00, 0x00, 0x80, 0x40, 0xCD, 0xCC, 0x2C, 0x40, 0x8F, 0xC2, 0xF5, 0x3D };

        std::vector<BYTE> searchb = { 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D };
        std::vector<BYTE> replaceb = { 0x99, 0xBB, 0x16, 0x3B, 0x99, 0xBB, 0x16, 0x3B, 0x02, 0x2B, 0x07, 0x3D };

        bool st1 = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());
        bool st2 = mem.ReplacePattern(startAddress, endAddress, searchb.data(), replaceb.data());

        if (st1 || st2)
        {
            notificationSystem.AddNotification("Fast Fire", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Fire", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Fire", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableFastFire()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Fire", "Disabling", ImGui::GetColorU32(c::accent));
        
        // Pattern 1 Revert
        std::vector<BYTE> replace1 = { 0x00, 0x00, 0x80, 0x40, 0x33, 0x33, 0x93, 0x40, 0x3D, 0x0A, 0xF7, 0x3F };
        std::vector<BYTE> search1 = { 0x00, 0x00, 0x80, 0x40, 0xCD, 0xCC, 0x2C, 0x40, 0x8F, 0xC2, 0xF5, 0x3D };

        // Pattern 2 Revert
        std::vector<BYTE> replace2 = { 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D };
        std::vector<BYTE> search2 = { 0x99, 0xBB, 0x16, 0x3B, 0x99, 0xBB, 0x16, 0x3B, 0x02, 0x2B, 0x07, 0x3D };

        bool st1 = mem.ReplacePattern(startAddress, endAddress, search1.data(), replace1.data());
        bool st2 = mem.ReplacePattern(startAddress, endAddress, search2.data(), replace2.data());

        if (st1 || st2)
        {
            notificationSystem.AddNotification("Fast Fire", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Fire", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Fire", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void EnableFastReload()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Reload", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0xC0, 0xD8, 0xFF, 0xEB, 0x01, 0x00, 0x50, 0xE3, 0x84, 0x0A, 0x94, 0x0D, 0x00, 0x8A, 0x38, 0x0E, 0x10, 0x0A, 0x18, 0xEE, 0x02, 0x8B, 0xBD, 0xEC, 0x30, 0x88, 0xBD, 0xE8, 0x30, 0x48, 0x2D, 0xE9, 0x08, 0xB0, 0x8D, 0xE2, 0x00, 0x40, 0xA0, 0xE1, 0x25, 0x0A, 0x00, 0xE3, 0x00, 0x10, 0xA0, 0xE3
        };
        std::vector<BYTE> replace = {
            0xC0, 0xD8, 0xFF, 0xEB, 0x01, 0x00, 0x50, 0xE3, 0x84, 0x0A, 0x94, 0x0D, 0x00, 0x8A, 0x38, 0x0E, 0x10, 0x0A, 0x18, 0xEE, 0x02, 0x8B, 0xBD, 0xEC, 0x30, 0x88, 0xBD, 0xE8, 0xFF, 0x00, 0x45, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1, 0x00, 0x40, 0xA0, 0xE1, 0x25, 0x0A, 0x00, 0xE3, 0x00, 0x10, 0xA0, 0xE3
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Reload", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Reload", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Reload", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableFastReload()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Reload", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0xC0, 0xD8, 0xFF, 0xEB, 0x01, 0x00, 0x50, 0xE3, 0x84, 0x0A, 0x94, 0x0D, 0x00, 0x8A, 0x38, 0x0E, 0x10, 0x0A, 0x18, 0xEE, 0x02, 0x8B, 0xBD, 0xEC, 0x30, 0x88, 0xBD, 0xE8, 0x30, 0x48, 0x2D, 0xE9, 0x08, 0xB0, 0x8D, 0xE2, 0x00, 0x40, 0xA0, 0xE1, 0x25, 0x0A, 0x00, 0xE3, 0x00, 0x10, 0xA0, 0xE3
        };
        std::vector<BYTE> search = {
            0xC0, 0xD8, 0xFF, 0xEB, 0x01, 0x00, 0x50, 0xE3, 0x84, 0x0A, 0x94, 0x0D, 0x00, 0x8A, 0x38, 0x0E, 0x10, 0x0A, 0x18, 0xEE, 0x02, 0x8B, 0xBD, 0xEC, 0x30, 0x88, 0xBD, 0xE8, 0xFF, 0x00, 0x45, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1, 0x00, 0x40, 0xA0, 0xE1, 0x25, 0x0A, 0x00, 0xE3, 0x00, 0x10, 0xA0, 0xE3
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Reload", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Reload", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Reload", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableGlitchFire()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Glitch Fire", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x90, 0xC1, 0x00, 0x00, 0x70, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F
        };
        std::vector<BYTE> replace = {
            0x90, 0xC1, 0x00, 0x00, 0x70, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Glitch Fire", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Glitch Fire", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Glitch Fire", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableGlitchFire()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Glitch Fire", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x90, 0xC1, 0x00, 0x00, 0x70, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x3F, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F
        };
        std::vector<BYTE> search = {
            0x90, 0xC1, 0x00, 0x00, 0x70, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x80, 0x3F
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Glitch Fire", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Glitch Fire", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Glitch Fire", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableFastLanding()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Landing", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2
        };
        std::vector<BYTE> replace = {
            0x00, 0x47, 0xEF, 0xC1, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Landing", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Landing", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Landing", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableFastLanding()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Fast Landing", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2
        };
        std::vector<BYTE> search = {
            0x00, 0x47, 0xEF, 0xC1, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Landing", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Fast Landing", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Fast Landing", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void ResetGuest()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Reset Guest", "Resetting Guest Account", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x10, 0x4C, 0x2D, 0xE9, 0x08, 0xB0, 0x8D, 0xE2, 0x0C, 0x01, 0x9F, 0xE5, 0x00, 0x00, 0x8F, 0xE0
        };
        std::vector<BYTE> replace = {
            0x01, 0x00, 0xA0, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1, 0x0C, 0x01, 0x9F, 0xE5, 0x00, 0x00, 0x8F, 0xE0
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Reset Guest", "Success", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Reset Guest", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Reset Guest", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableUnlimitedAmmo()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Unlimited Ammo", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
        0xD0, 0x00, 0xD0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD0, 0x10, 0xC0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD1, 0x00, 0xD0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD1, 0x10, 0xC0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0x30, 0x48, 0x2D, 0xE9, 0x08, 0xB0, 0x8D, 0xE2
        };
        std::vector<BYTE> replace = {
            0x01, 0x00, 0xA0, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Unlimited Ammo", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Unlimited Ammo", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Unlimited Ammo", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableUnlimitedAmmo()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Unlimited Ammo", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
        0xD0, 0x00, 0xD0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD0, 0x10, 0xC0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD1, 0x00, 0xD0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0xD1, 0x10, 0xC0, 0xE5, 0x1E, 0xFF, 0x2F, 0xE1, 0x30, 0x48, 0x2D, 0xE9, 0x08, 0xB0, 0x8D, 0xE2
        };
        std::vector<BYTE> search = {
            0x01, 0x00, 0xA0, 0xE3, 0x1E, 0xFF, 0x2F, 0xE1
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Unlimited Ammo", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Unlimited Ammo", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Unlimited Ammo", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableSniperScope()
{
    if (sniper_macro.SaveScope()) {
        notificationSystem.AddNotification("Sniper Scope", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\WindowsStartup.wav", SND_ASYNC | SND_FILENAME);

        std::thread([]() {
            while (sniperScope) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    sniper_macro.EnableScope();
                    while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            }).detach();
    }
    else {
        notificationSystem.AddNotification("Sniper Scope", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        sniperScope = false;
    }
}
void DisableSniperScope()
{
    notificationSystem.AddNotification("Sniper Scope", "Disabled", ImGui::GetColorU32(c::accent));
    if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
}

void EnableSniperSwitch()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Sniper Switch", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x3F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F
        };
        std::vector<BYTE> replace = {
            0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01, 0x00, 0x00, 0x00, 0x01
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Sniper Switch", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Sniper Switch", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Sniper Switch", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableSniperSwitch()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Sniper Switch", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x3F, 0x00, 0x00, 0x80, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F
        };
        std::vector<BYTE> search = {
           0x01, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x20, 0x41, 0x00, 0x00, 0x34, 0x42, 0x01, 0x00, 0x00, 0x00, 0x01
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if(sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Sniper Switch", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Sniper Switch", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Sniper Switch", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableDelayFix()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Delay Fix", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0xEA, 0x00, 0x60, 0xA0, 0xE3, 0x06, 0x00, 0xA0, 0xE1, 0x18, 0xD0, 0x4B, 0xE2, 0x02, 0x8B, 0xBD, 0xEC, 0x70, 0x8C
        };
        std::vector<BYTE> replace = {
            0x01, 0x00, 0xAF, 0xE3
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Delay Fix", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Delay Fix", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Delay Fix", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableDelayFix()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Delay Fix", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0xEA, 0x00, 0x60, 0xA0, 0xE3, 0x06, 0x00, 0xA0, 0xE1, 0x18, 0xD0, 0x4B, 0xE2, 0x02, 0x8B, 0xBD, 0xEC, 0x70, 0x8C
        };
        std::vector<BYTE> search = {
           0x01, 0x00, 0xAF, 0xE3
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Delay Fix", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("Delay Fix", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("Delay Fix", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableAWMLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("AWM Location", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x18, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x61, 0x00, 0x77, 0x00, 0x6D, '?', '?', '?', '?', '?', '?', '?', '?', '?'
        };
        std::vector<BYTE> replace = {
            0x1C, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM Location", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("AWM Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableAWMLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("AWM Location", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x18, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x61, 0x00, 0x77, 0x00, 0x6D, '?', '?', '?', '?', '?', '?', '?', '?', '?'
        };
        std::vector<BYTE> search = {
           0x1C, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x72, 0x00, 0x65, 0x00, 0x64, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM Location", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("AWM Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableAWMYLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("AWM-Y Location", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x20, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x61, 0x00, 0x77, 0x00, 0x6D, 0x00, 0x5F, 0x00, 0x67, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0x64, 0x00
        };
        std::vector<BYTE> replace = {
            0x1D, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x67, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x73, 0x00, 0x68, 0x00, 0x6F, 0x00, 0x70, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM-Y Location", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM-Y Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("AWM-Y Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableAWMYLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("AWM-Y Location", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x20, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x61, 0x00, 0x77, 0x00, 0x6D, 0x00, 0x5F, 0x00, 0x67, 0x00, 0x6F, 0x00, 0x6C, 0x00, 0x64, 0x00
        };
        std::vector<BYTE> search = {
            0x1D, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x67, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x73, 0x00, 0x68, 0x00, 0x6F, 0x00, 0x70, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM-Y Location", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("AWM-Y Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("AWM-Y Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableVSK94Location()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("VSK94 Location", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x1A, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x76, 0x00, 0x73, 0x00, 0x6B, '?', '?', '?', '?', '?'
        };
        std::vector<BYTE> replace = {
            0x19, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("VSK94 Location", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("VSK94 Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("VSK94 Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableVSK94Location()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("VSK94 Location", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x1A, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2F, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6B, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5F, 0x00, 0x76, 0x00, 0x73, 0x00, 0x6B, '?', '?', '?', '?', '?'
        };
        std::vector<BYTE> search = {
            0x19, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("VSK94 Location", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("VSK94 Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("VSK94 Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void EnableM82BLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("M82B Location", "Enabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> search = {
            0x19, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x2f, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2f, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5f, 0x00, 0x62, 0x00, 0x6d, 0x00, 0x39, 0x00, 0x34, 0x00, 0x00, 0x00
        };
        std::vector<BYTE> replace = {
            0x1D, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x67, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x73, 0x00, 0x68, 0x00, 0x6F, 0x00, 0x70, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("M82B Location", "Enabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("M82B Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("M82B Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}
void DisableM82BLocation()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("M82B Location", "Disabling", ImGui::GetColorU32(c::accent));
        std::vector<BYTE> replace = {
            0x19, 0x00, 0x00, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x67, 0x00, 0x61, 0x00, 0x6d, 0x00, 0x65, 0x00, 0x2f, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x75, 0x00, 0x70, 0x00, 0x2f, 0x00, 0x70, 0x00, 0x69, 0x00, 0x63, 0x00, 0x6b, 0x00, 0x75, 0x00, 0x70, 0x00, 0x5f, 0x00, 0x62, 0x00, 0x6d, 0x00, 0x39, 0x00, 0x34, 0x00, 0x00, 0x00
        };
        std::vector<BYTE> search = {
            0x1D, 0x00, 0x00, 0x00, 0x65, 0x00, 0x66, 0x00, 0x66, 0x00, 0x65, 0x00, 0x63, 0x00, 0x74, 0x00, 0x73, 0x00, 0x2F, 0x00, 0x76, 0x00, 0x66, 0x00, 0x78, 0x00, 0x5F, 0x00, 0x69, 0x00, 0x6E, 0x00, 0x61, 0x00, 0x67, 0x00, 0x6D, 0x00, 0x65, 0x00, 0x5F, 0x00, 0x6C, 0x00, 0x61, 0x00, 0x73, 0x00, 0x65, 0x00, 0x72, 0x00, 0x5F, 0x00, 0x73, 0x00, 0x68, 0x00, 0x6F, 0x00, 0x70, 0x00
        };

        bool st = mem.ReplacePattern(startAddress, endAddress, search.data(), replace.data());

        if (st)
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("M82B Location", "Disabled", ImGui::GetColorU32(c::accent));
        }
        else
        {
            if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
            notificationSystem.AddNotification("M82B Location", "No Matching Pattern Found", ImGui::GetColorU32(c::accent));
        }
    }
    else {
        notificationSystem.AddNotification("M82B Location", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }

}

void LoadWallHack()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Wall Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    notificationSystem.AddNotification("Wall Hack", "Loading Wall Hack", ImGui::GetColorU32(c::accent));
    
    std::vector<BYTE> search = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2, 0x43, 0x2A, 0xB0, 0xEE 
    };
    /*std::vector<BYTE> search = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2, 0x43, 0x2A, 0xB0, 0xEE, 0xEF, 0x0A, 0x60, 0xF4, 0x43, 0x6A, 0xF0, 0xEE, 0x1C, 0x00, 0x8A, 0xE2, 0x43, 0x5A, 0xF0, 0xEE, 0x8F, 0x0A, 0x48, 0xF4, 0x43, 0x2A, 0xF0, 0xEE, 0x43, 0x7A, 0xB0, 0xEE, 0x8F, 0x0A, 0x40, 0xF4, 0x41, 0xAA, 0xB0, 0xEE, 0xFE
    };*/

    wallhackAddress.clear();
    mem.FindPattern(startAddress, endAddress, search.data(), wallhackAddress);

    if (!wallhackAddress.empty()) {
        notificationSystem.AddNotification("Wall Hack", "Loaded", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Wall Hack", "Failed to Load Pattern", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void EnableWallHack()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Wall Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (wallhackAddress.empty()) {
        notificationSystem.AddNotification("Wall Hack", "Failed: Load it first!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> replace = {
        0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0xBF, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2, 0x43, 0x2A, 0xB0, 0xEE 
    };
    /*std::vector<BYTE> replace = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0xBF, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0xBF, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED
    };*/

    bool success = false;
    for (auto addr : wallhackAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, replace.data(), replace.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Wall Hack", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Wall Hack", "Failed to Enable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableWallHack()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Wall Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (wallhackAddress.empty()) {
        notificationSystem.AddNotification("Wall Hack", "Failed: Not Loaded!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> original = {
       0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2, 0x43, 0x2A, 0xB0, 0xEE 
    };
    /*std::vector<BYTE> original = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0xAE, 0x47, 0x81, 0x3F, 0x00, 0x1A, 0xB7, 0xEE, 0xDC, 0x3A, 0x9F, 0xED, 0x30, 0x00, 0x4F, 0xE2, 0x43, 0x2A, 0xB0, 0xEE, 0xEF, 0x0A, 0x60, 0xF4, 0x43, 0x6A, 0xF0, 0xEE, 0x1C, 0x00, 0x8A, 0xE2, 0x43, 0x5A, 0xF0, 0xEE, 0x8F, 0x0A, 0x48, 0xF4, 0x43, 0x2A, 0xF0, 0xEE, 0x43, 0x7A, 0xB0, 0xEE, 0x8F, 0x0A, 0x40, 0xF4, 0x41, 0xAA, 0xB0, 0xEE, 0xFE
    };*/

    bool success = false;
    for (auto addr : wallhackAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, original.data(), original.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Wall Hack", "Disabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Wall Hack", "Failed to Disable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void LoadSpeedHack()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Speed Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    notificationSystem.AddNotification("Speed Hack", "Loading Speed Hack", ImGui::GetColorU32(c::accent));

    std::vector<BYTE> search = {
        0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x6C, 0xF2, 0x41, 0x00, 0x00, 0x00, 0x00
    };
    /*std::vector<BYTE> search = {
        0x01, 0x00, 0x00, 0x00, 0x02, 0x2B, 0x07, 0x3D
    };*/

    speedhackAddress.clear();
    mem.FindPattern(startAddress, endAddress, search.data(), speedhackAddress);

    if (!speedhackAddress.empty()) {
        notificationSystem.AddNotification("Speed Hack", "Loaded", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Speed Hack", "Failed to Load Pattern", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void EnableSpeedHack()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Speed Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (speedhackAddress.empty()) {
        notificationSystem.AddNotification("Speed Hack", "Failed: Load it first!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> replace = {
        0xE3, 0xA5, 0x9B, 0x3C, 0xE3, 0xA5, 0x9B, 0x3C, 0x02, 0x2B, 0x07, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x6C, 0xF2, 0x41, 0x00, 0x00, 0x00, 0x00
    };
    /*std::vector<BYTE> replace = {
        0x01, 0x00, 0x00, 0x00, 0x02, 0x2B, 0x85, 0x3D
    };*/

    bool success = false;
    for (auto addr : speedhackAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, replace.data(), replace.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Speed Hack", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Speed Hack", "Failed to Enable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableSpeedHack()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Speed Hack", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (speedhackAddress.empty()) {
        notificationSystem.AddNotification("Speed Hack", "Failed: Not Loaded!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> original = {
        0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x02, 0x2B, 0x07, 0x3D, 0x00, 0x00, 0x00, 0x00, 0x9B, 0x6C, 0xF2, 0x41, 0x00, 0x00, 0x00, 0x00
    };
    /*std::vector<BYTE> original = {
        0x01, 0x00, 0x00, 0x00, 0x02, 0x2B, 0x07, 0x3D
    };*/

    bool success = false;
    for (auto addr : speedhackAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, original.data(), original.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Speed Hack", "Disabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Speed Hack", "Failed to Disable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}

void LoadCameraLeft()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    DWORD_PTR startAddress = (DWORD_PTR)si.lpMinimumApplicationAddress;
    DWORD_PTR endAddress = (DWORD_PTR)si.lpMaximumApplicationAddress;

    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Camera Left", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    notificationSystem.AddNotification("Camera Left", "Loading Camera Left", ImGui::GetColorU32(c::accent));

    std::vector<BYTE> search = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0xFF 
    };

    cameraleftAddress.clear();
    mem.FindPattern(startAddress, endAddress, search.data(), cameraleftAddress);

    if (!cameraleftAddress.empty()) {
        notificationSystem.AddNotification("Camera Left", "Loaded", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Camera Left", "Failed to Load Pattern", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void EnableCameraLeft()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Camera Left", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (cameraleftAddress.empty()) {
        notificationSystem.AddNotification("Camera Left", "Failed: Load it first!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> replace = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0xFF 
    };

    bool success = false;
    for (auto addr : cameraleftAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, replace.data(), replace.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Camera Left", "Enabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Camera Left", "Failed to Enable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
void DisableCameraLeft()
{
    if (!mem.AttackProcess(GetTargetProcess().c_str())) {
        notificationSystem.AddNotification("Camera Left", "No Emulator is Running", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    if (cameraleftAddress.empty()) {
        notificationSystem.AddNotification("Camera Left", "Failed: Not Loaded!", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
        return;
    }

    std::vector<BYTE> original = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x80, 0xFF 
    };

    bool success = false;
    for (auto addr : cameraleftAddress) {
        if (WriteProcessMemory(mem.ProcessHandle, (LPVOID)addr, original.data(), original.size(), NULL)) {
            success = true;
        }
    }

    if (success) {
        notificationSystem.AddNotification("Camera Left", "Disabled", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
    else {
        notificationSystem.AddNotification("Camera Left", "Failed to Disable", ImGui::GetColorU32(c::accent));
        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
    }
}
#pragma endregion



int StringToIndex(const std::string& value, const char* items[], int count) {
    for (int i = 0; i < count; i++) {
        if (value == items[i]) {
            return i;
        }
    }
    return 0;
}

void SaveConfig(const AppConfig& config) {
    std::ofstream file("config.dat");
    if (file.is_open()) {
        file << "[Settings]\n";
        file << "LicenseKey=" << config.licenseKey << "\n";
        file << "AimbotBodyType=" << config.aimbotBodyType << "\n";
        file << "ChamsMenuType=" << config.chamsMenuType << "\n";
        file << "SniperSwitchType=" << config.sniperSwitchType << "\n";
        file << "FakeLagMode=" << config.fakeLagMode << "\n";
        file << "Sound=" << (config.Sound ? "1" : "0") << "\n";
        file << "DiscordRPC=" << (config.discordRPC ? "1" : "0") << "\n";
        file << "DisableAllAnimations=" << (config.disableAllAnimations ? "1" : "0") << "\n";
        file << "StreamerMode=" << (config.streamerMode ? "1" : "0") << "\n";
        file << "AutoSave=" << (config.autoSave ? "1" : "0") << "\n";
        file << "EmulatorMode=" << config.emulatorMode << "\n";

        file << "ColorR=" << config.colorR << "\n";
        file << "ColorG=" << config.colorG << "\n";
        file << "ColorB=" << config.colorB << "\n";
        file << "ColorA=" << config.colorA << "\n";

        file.close();
    }
}

bool LoadConfig(AppConfig& config) {
    std::ifstream file("config.dat");
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        size_t eqPos = line.find('=');
        if (eqPos != std::string::npos) {
            std::string key = line.substr(0, eqPos);
            std::string value = line.substr(eqPos + 1);

            if (key == "LicenseKey") config.licenseKey = value;
            else if (key == "AimbotBodyType") config.aimbotBodyType = value;
            else if (key == "ChamsMenuType") config.chamsMenuType = value;
            else if (key == "SniperSwitchType") config.sniperSwitchType = value;
            else if (key == "FakeLagMode") config.fakeLagMode = value;
            else if (key == "Sound") config.Sound = (value == "1");
            else if (key == "DiscordRPC") config.discordRPC = (value == "1");
            else if (key == "DisableAllAnimations") config.disableAllAnimations = (value == "1");
            else if (key == "StreamerMode") config.streamerMode = (value == "1");
            else if (key == "AutoSave") config.autoSave = (value == "1");
            else if (key == "EmulatorMode") config.emulatorMode = value;

            else if (key == "ColorR") config.colorR = std::stof(value);
            else if (key == "ColorG") config.colorG = std::stof(value);
            else if (key == "ColorB") config.colorB = std::stof(value);
            else if (key == "ColorA") config.colorA = std::stof(value);
        }
    }

    return true;
}






void DisableDiscordRPC() {
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.details = "";
    discordPresence.state = "";
    discordPresence.largeImageKey = "";
    discordPresence.smallImageKey = "";
    Discord_UpdatePresence(&discordPresence);

    Discord_Shutdown();
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    //AuthlyXApp.Init();
    if (!AuthlyXApp.Init()) {
        std::cout << "Connection Failed: " << AuthlyXApp.response.message << std::endl;
        std::cout << "Change your DNS to Google DNS or Cloudfare and try again if that didnt work try using a VPN or Contact Support";
        std::cout << "Press any key to exit...";
        std::cin.get();
        return 1;
    }
    LoadConfig(currentConfig);
    DownloadAudio();
    sound = currentConfig.Sound;
    discordrpc = currentConfig.discordRPC;
    disableAllAnimations = currentConfig.disableAllAnimations;
    streammode = currentConfig.streamerMode;
    autosave = currentConfig.autoSave;

    strncpy(license, currentConfig.licenseKey.c_str(), sizeof(license) - 1);
    license[sizeof(license) - 1] = '\0';

    bodyType = currentConfig.aimbotBodyType;
    chamsMenuType = currentConfig.chamsMenuType;
    sniperSwitchType = currentConfig.sniperSwitchType;

    // Restore emulator selection from config
    {
        int numEmulators = IM_ARRAYSIZE(emulatorDisplayNames);
        emulatorSelected = 0; // default: Automatic
        for (int i = 0; i < numEmulators; i++) {
            if (currentConfig.emulatorMode == emulatorDisplayNames[i]) {
                emulatorSelected = i;
                break;
            }
        }
    }

    color[0] = currentConfig.colorR;
    color[1] = currentConfig.colorG;
    color[2] = currentConfig.colorB;
    color[3] = currentConfig.colorA;

    WNDCLASSEXW wc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = NULL;   
    wc.hInstance = nullptr;
    wc.hIcon = nullptr;
    wc.hCursor = LoadCursor(0, IDC_ARROW);
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = L"BRUUUH CHEATS";
    wc.lpszClassName = L"BRUUUH CHEATS";
    wc.hIconSm = nullptr;

    RegisterClassExW(&wc);
    hwnd = CreateWindowExW(NULL, wc.lpszClassName, L"BRUUUH CHEATS", WS_POPUP, (GetSystemMetrics(SM_CXSCREEN) / 2) - (c::background::size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (c::background::size.y / 2), c::background::size.x, c::background::size.y, 0, 0, 0, 0);

    SetWindowLongA(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);

    MARGINS margins = { -1 };
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    POINT mouse;
    rc = { 0 };
    GetWindowRect(hwnd, &rc);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd)) {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }
     
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);
    bool isClickable = true;
    ToggleClickability(isClickable);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 

    ImFontConfig cfg;
    cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;

    io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::primary_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof PoppinsRegular, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());
    
    font::second_font = io.Fonts->AddFontFromMemoryTTF(&PoppinsRegular, sizeof(PoppinsRegular), 18, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::icon_font = io.Fonts->AddFontFromMemoryTTF(&ico_moon, sizeof(ico_moon), 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

    font::lexend_general_bold = io.Fonts->AddFontFromMemoryTTF(lexend_bold, sizeof(lexend_bold), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_general_bold2 = io.Fonts->AddFontFromMemoryTTF(lexend_bold2, sizeof(lexend_bold2), 30.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_bold = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::lexend_regular = io.Fonts->AddFontFromMemoryTTF(lexend_regular, sizeof(lexend_regular), 14.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::picomoon = io.Fonts->AddFontFromMemoryTTF(picomoon, sizeof(picomoon), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::Nevan = io.Fonts->AddFontFromMemoryTTF(Nevan, sizeof(Nevan), 20.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::ContiB = io.Fonts->AddFontFromMemoryTTF(continuum_bold, sizeof(continuum_bold), 32.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::ContiM = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 45.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    ImFont* ContiM2 = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 32.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::tab_font = io.Fonts->AddFontFromMemoryTTF(continuum_medium, sizeof(continuum_medium), 18.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());

    font::icomoon_widget = io.Fonts->AddFontFromMemoryTTF(icomoon_widget, sizeof(icomoon_widget), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icomoon_widget2 = io.Fonts->AddFontFromMemoryTTF(icomoon, sizeof(icomoon), 16.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icon_font2 = io.Fonts->AddFontFromMemoryTTF(&icomoon2, sizeof icomoon2, 35, NULL, io.Fonts->GetGlyphRangesCyrillic());

    D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
    if (texture::logo == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo, sizeof(logo), &info, pump, &texture::logo, 0);
    if (texture::logo12 == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, logo12, sizeof(particulas_xd), &info, pump, &texture::logo12, 0);
    if (texture::JINO == nullptr) D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, LOGOJINO, sizeof(LOGOJINO), &info, pump, &texture::JINO, 0);
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);
    


    while (!done)
    {

        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        if (done) break;

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        static int opacity = 255;
        static bool hide = true;

        if (GetAsyncKeyState(VK_INSERT) & 1) 
        {
            isClickable = !isClickable;
            hide = !hide;
            ToggleClickability(isClickable);
        }

        if (GetAsyncKeyState(aim_head) & 1)
        {
            if (!aimbot_h) {
                aimbot_h = true;
            }
            std::thread([]() { EnableAimbotHead(); }).detach();
        }

        if (GetAsyncKeyState(aim_drag) & 1)
        {
            if (!aimbot_d) {
                aimbot_d = true;
            }
            std::thread([]() { EnableAimbotDrag(); }).detach();
        }
        if (GetAsyncKeyState(aim_neck) & 1)
        {
            if (!aimbot_n) {
                aimbot_n = true;
            }
            std::thread([]() { EnableAimbotNeck(); }).detach();
        }
        
        if (GetAsyncKeyState(wall_hack) & 1)
        {
            if (!wallHack) {
                std::thread([]() { EnableWallHack(); }).detach();
                wallHack = true;
            }
            else {
                std::thread([]() { DisableWallHack(); }).detach();
                wallHack = false;
            }
        }

        if (GetAsyncKeyState(speed_hack) & 1)
        {
            if (!speedHack) {
                std::thread([]() { EnableSpeedHack(); }).detach();
                speedHack = true;
            }
            else {
                std::thread([]() { DisableSpeedHack(); }).detach();
                speedHack = false;
            }
        }
        if (GetAsyncKeyState(camera_hack) & 1)
        {
            if (!CameraLeft) {
                std::thread([]() { EnableCameraLeft(); }).detach();
                CameraLeft = true;
            }
            else {
                std::thread([]() { DisableCameraLeft(); }).detach();
                CameraLeft = false;
            }
        }
        if (GetAsyncKeyState(streamer_mode) & 1)
        {
            streammode = !streammode;

            HWND hwnd = GetActiveWindow();

            if (streammode)
            {
                notificationSystem.AddNotification("Done", "Stream Mode Enabled!", ImGui::GetColorU32(c::accent));

                SetWindowDisplayAffinity(hwnd, WDA_EXCLUDEFROMCAPTURE);

                ITaskbarList* pTaskList = nullptr;
                CoInitialize(nullptr);
                if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                {
                    pTaskList->DeleteTab(hwnd);
                    pTaskList->Release();
                }
                CoUninitialize();
                sound = false;
            }
            else
            {
                notificationSystem.AddNotification("Done", "Stream Mode Disabled!", ImGui::GetColorU32(c::accent));

                SetWindowDisplayAffinity(hwnd, WDA_NONE);

                ITaskbarList* pTaskList = nullptr;
                CoInitialize(nullptr);
                if (SUCCEEDED(CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER, IID_ITaskbarList, (LPVOID*)&pTaskList)))
                {
                    pTaskList->AddTab(hwnd);
                    pTaskList->Release();
                }
                CoUninitialize();
                sound = true;
            }
        }

        if (!disableAllAnimations) {
            opacity = ImLerp(opacity, opacity <= 255 && hide ? 300 : 0, ImGui::GetIO().DeltaTime * 8.f);
        }
        else {
            opacity = opacity <= 255 && hide ? 300 : 0;
        }

        if (opacity > 255) opacity = 255;
        SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), opacity, LWA_ALPHA);

        if (GetAsyncKeyState(VK_DELETE) & 1)
        {
            exit(0);
        }

        static bool isKeyPressed = false;

        if ((GetAsyncKeyState(fakelag_key) & 0x8000) && fakelag2 > 0)
        {
            if (!isKeyPressed && fake_lag)
            {
                isKeyPressed = true;
                std::thread([]
                    {
                      if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
                        auto start = std::chrono::steady_clock::now();

                        PauseNetwork();

                        auto elapsed = std::chrono::steady_clock::now() - start;
                        auto delay = ToMilliseconds(fakelag2); 

                        auto remaining = delay - std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

                        if (remaining.count() > 0)
                            std::this_thread::sleep_for(remaining); 

                        ResumeNetwork();
                        if (sound) sndPlaySound("C:\\Windows\\System32\\Windows.wav", SND_ASYNC | SND_FILENAME);
                    }).detach();
            }
        }
        else isKeyPressed = false;



        ImGui::NewFrame();
        {


            ImGuiStyle* style = &ImGui::GetStyle();

            style->WindowPadding = ImVec2(0, 0);
            style->ItemSpacing = ImVec2(10, 10);
            style->WindowBorderSize = 0;
            style->ScrollbarSize = 8.f;

            //static float color[4] = { 230 / 255.f, 25 / 255.f, 25 / 255.f, 1.f };//Red
            //static float color[4] = { 25 / 255.f, 100 / 255.f, 230 / 255.f, 1.f };// Light blue
            //static float color[4] = { 79 / 255.f, 7 / 255.f, 168 / 255.f, 1.f };
            c::accent = { color[0], color[1], color[2], 1.f };


            if (authed == false)
            {
                //Resize window to prevent RenderBlur Glitches
                if (!initialized)
                {
                    SetWindowPos(hwnd, nullptr, (GetSystemMetrics(SM_CXSCREEN) / 2) - (c::background::size2.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (c::background::size2.y / 2), (int)c::background::size2.x, (int)c::background::size2.y, SWP_NOZORDER | SWP_SHOWWINDOW);
                    initialized = true;
                }

                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 screenSize = ImGui::GetIO().DisplaySize;

                ImVec2 centerPosition = ImVec2((screenSize.x - windowSize.x) * 0.5f, (screenSize.y - windowSize.y) * 0.5f);
                ImGui::SetNextWindowPos(ImVec2(0, 0));

                ImGui::SetNextWindowSize(c::background::size2);

                ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus);
                {
                    LoadCredentials();
                    if (!disableAllAnimations && !disableParticles) {
                        ParticlesV();
                    }

                    static std::vector<std::string> captions = {
                        "WELCOME TO BRUUUH CHEATS",
                        "YOUR UNFAIR ADVANTAGE",
                        "THE WIN CONDITION",
                        //"BRUUUH CHEATS "
                        
                    };

                    const ImVec2& pos = ImGui::GetWindowPos();
                    const ImVec2& region = ImGui::GetContentRegionMax();
                    const ImVec2& spacing = style->ItemSpacing;

                  
                    auto draw = ImGui::GetWindowDrawList();
                    const auto& p = ImGui::GetWindowPos();

                    static bool login_page = true;
                    static float login_page_offset = 0.f;
                    static float animation_speed = 0.1f;

                    if (!disableAllAnimations) {
                        login_page_offset = ImLerp(login_page_offset, login_page ? 40.f : -100.f, animation_speed);
                    }
                    else {
                        login_page_offset = login_page ? 40.f : -100.f; 
                    }

                    //Background
                    ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + c::background::size2, ImGui::GetColorU32(c::tab::border, 0.8f), c::background::rounding);
                    ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + c::background::size2, ImGui::GetColorU32(c::accent, 0.04f), c::background::rounding);


                    //Title
                    ImGui::PushFont(font::ContiB);
                    draw->AddText(ImVec2(c::background::size2.x / 2 - ImGui::CalcTextSize("BRUUUH CHEATS").x / 2, 50), ImGui::ColorConvertFloat4ToU32(c::white), "BRUUUH");
                    draw->AddText(
                        ImVec2(
                            c::background::size2.x / 2 - ImGui::CalcTextSize("BRUUUH CHEATS").x / 2 + ImGui::CalcTextSize("BRUUUH ").x,
                            50
                        ),
                        ImColor(color[0], color[1], color[2], 1.f),
                        "CHEATS"
                    );
                    ImGui::PopFont();

                    //Caption
                    AnimatedCaption(captions, ImVec2(c::background::size2.x / 2 , 80));

                    ImGui::SetCursorPos(ImVec2(login_page_offset, 130));

                    ImGui::BeginChild("Inputs", ImVec2(255, 150), 0);

                    ImGui::InputTextExNew("v", "License Key", license, 64, ImVec2(c::background::size2.x - 80, 40), 0,0,0);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
                    /*ImGui::InputTextExNew("v", "Username", username, 64, ImVec2(c::background::size2.x - 80, 40), 0,0,0);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
                    ImGui::InputTextExNew("x", "Password", password, 64, ImVec2(c::background::size2.x - 80, 40), 0, 0, 0);
                    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);*/

                    if (ImGui::Button(btn_txt.c_str(), ImVec2(255, 40)))
                    {
                        btn_txt = "Logging in...";
                        std::thread([]() 
                            {
                                AuthlyXApp.LicenseLogin(license);
                                if (AuthlyXApp.response.success) {

                                    currentConfig.licenseKey = license;
                                    SaveConfig(currentConfig);

                                    authed = true;
                                    btn_txt = "Login";

                                    if (discordrpc) {
                                        std::time_t CurrentTime = std::time(0);
                                        std::string username = "Sub: " + AuthlyXApp.userData.subscription;
                                        std::string expiry = AuthlyXApp.userData.expiryDate;
                                        std::time_t expiryTime = std::atoi(expiry.c_str());
                                        std::string expdate = "Expiry: " + AuthlyXApp.userData.expiryDate;
                                        DiscordEventHandlers Handle;
                                        memset(&Handle, 0, sizeof(Handle));
                                        Discord_Initialize("1350087937236406292", &Handle, 1, NULL);
                                        DiscordRichPresence discordPresence;
                                        memset(&discordPresence, 0, sizeof(discordPresence));
                                        char formattedExpiry[17];
                                        std::tm* tmPtr = std::localtime(&expiryTime);
                                        std::strftime(formattedExpiry, sizeof(formattedExpiry), "Days: %m/%d/%y", tmPtr);
                                        discordPresence.state = expdate.c_str();;
                                        discordPresence.details = username.c_str();
                                        discordPresence.startTimestamp = CurrentTime;
                                        discordPresence.details = username.c_str();
                                        discordPresence.largeImageKey = "https://i.ibb.co/Pv2K78rK/bruuuh-no-bg-blue.png";
                                        discordPresence.largeImageText = "BRUUUH EXTERNAL C++";
                                        discordPresence.smallImageKey = "https://i.gifer.com/3OWpa.gif";
                                        discordPresence.smallImageText = "Your Unfair Advantage";
                                        discordPresence.button1_label = "Discord";
                                        discordPresence.button1_url = "https://discord.gg/fF9RCMVaGT";
                                        discordPresence.button2_label = "Website";
                                        discordPresence.button2_url = "https://bruuuhcheats.xyz";
                                        Discord_UpdatePresence(&discordPresence);
                                   }
                                    authed = true;
                                    notificationSystem.AddNotification("Success", "Logged In!", ImGui::GetColorU32(c::accent));
                                    if(sound) sndPlaySoundA("C:\\Windows\\System32\\WindowsStartup.wav", SND_ASYNC | SND_FILENAME);
                                }
                                else 
                                {
                                    notificationSystem.AddNotification("Error", "Invalid Credentials", ImGui::GetColorU32(c::accent));
                                    authed = false;
                                    btn_txt = "Login";
                                }
                            }).detach();
                    }


                    ImGui::EndChild();



                    ImGui::SetCursorPos(ImVec2(c::background::size2.x / 2 - 27, c::background::size2.y - 50));

                    if (ImGui::TextButton("C", ImVec2(35, 35), 0));
                    if (ImGui::IsItemClicked()) ShellExecute(NULL, "open", "https://discord.gg/fF9RCMVaGT", NULL, NULL, SW_SHOW);

                    notificationSystem.DrawNotifications();
                    move_window2();

                    ImGui::End();
                    
                    RenderBlur(hwnd);
                    
                }
            }


            if (authed == true)
            {
                //AuthlyXApp.ValidateSession();
                if (!initialized2)
                {
                    SetWindowPos(hwnd, nullptr, (GetSystemMetrics(SM_CXSCREEN) / 2) - (c::background::size.x / 2), (GetSystemMetrics(SM_CYSCREEN) / 2) - (c::background::size.y / 2), (int)c::background::size.x, (int)c::background::size.y, SWP_NOZORDER | SWP_SHOWWINDOW);
                    initialized2 = true;
                }

                ImGui::SetNextWindowSize(c::background::size);

                ImGui::SetNextWindowPos(ImVec2(0, 0));

                ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoScrollWithMouse);
                {
                    if (!disableAllAnimations && !disableParticles) {
                        ParticlesV();
                    }
                    // Quelque part dans ton code
                    if (ImGui::IsMouseDragging(0) && ImGui::IsWindowHovered())
                    {
                        ImVec2 delta = ImGui::GetMouseDragDelta(0);
                        // Move window
                    }
                    const ImVec2& pos = ImGui::GetWindowPos();
                    const ImVec2& region = ImGui::GetContentRegionMax();
                    const ImVec2& spacing = style->ItemSpacing;
                    
                    
                    auto draw = ImGui::GetWindowDrawList();
                    const auto& p = ImGui::GetWindowPos();

                    ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + c::background::size, ImGui::GetColorU32(c::background::filling, 0.9f), c::background::rounding);

                    ImGui::GetBackgroundDrawList()->AddRect(pos, pos + c::background::size, ImGui::GetColorU32(c::background::stroke), c::background::rounding);

                    ImGui::GetForegroundDrawList()->AddShadowCircle(ImVec2(30, -120), 180.f, ImColor(c::accent.x, c::accent.y, c::accent.z, 0.8f), 400.f, ImVec2(0, 0), 0, 30);

                    ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(190, c::background::size.y), ImGui::GetColorU32(c::background::filling, 0.7f), c::background::rounding, ImDrawFlags_RoundCornersLeft);
                   
                    ImGui::PushFont(font::lexend_bold);

                   
                    ImGui::PopFont();

                    //Title Stuff
                    ImGui::PushFont(font::ContiM);

                    const char* title = "   B R U U U H";
                    ImVec2 titlesz = ImGui::CalcTextSize(title);

                    draw->AddText(pos + ImVec2(190 / 2 - titlesz.x / 2, 5),
                        ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 0.5f)), title, 0);

                    
                   


                    ImGui::PopFont();

                  


                   


                    ImGui::SetCursorPos(ImVec2(310, 15));

                    ImGui::BeginGroup();

                    //Tabs
                    if (edited::Tab(page == 0, "c", "Aimbot", ImVec2(40, 40))) {
                        page = 0;
                    }
                    ImGui::SameLine(0, 27);

                    if (edited::Tab(page == 1, "b", "Miscs & Chams", ImVec2(40, 40))) {
                        page = 1;
                    }
                    ImGui::SameLine(0, 27);

                    if (edited::Tab(page == 2, "f", "Fake Lag", ImVec2(40, 40))) {
                        page = 2;
                    }
                    ImGui::SameLine(0, 27);

                    if (edited::Tab(page == 3, "d", "Key Binds", ImVec2(40, 40))) {
                        page = 3;
                    }
                    ImGui::SameLine(0, 27);

                    if (edited::Tab(page == 4, "e", "Settings", ImVec2(40, 40))) {
                        page = 4;
                    }

                    ImGui::EndGroup();

                    if (!disableAllAnimations) {
                        tab_alpha = ImLerp(tab_alpha, (page == active_tab) ? 1.f : 0.f, 15.f * ImGui::GetIO().DeltaTime);
                    }
                    else {
                        tab_alpha = (page == active_tab) ? 1.f : 0.f;
                        if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = page;
                    }

                    if (tab_alpha < 0.01f && tab_add < 0.01f) active_tab = page;
                    ImGui::SetCursorPos(ImVec2(20, 70));
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);
                    {
                        if (active_tab == 0)
                        {
                            edited::BeginChild("a", "Aim Functions", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {

                                
                                if (edited::Checkbox("Aimbot In-Game [ Head ]", "Works In-Game", &aimbot_h)) {

                                    if (aimbot_h) std::thread([]() { EnableAimbotHead(); }).detach();
                                    else std::thread([]() { DisableAimbotHead(); }).detach();
                                }

                                bool isEssentialOrUltra = (AuthlyXApp.userData.subscription == "Essential" || AuthlyXApp.userData.subscription == "Ultra");
                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");

                                if (!isEssentialOrUltra) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Aimbot In-Game [ Drag ]", "Works In-Game", &aimbot_d)) {
                                    if (aimbot_d) std::thread([]() { EnableAimbotDrag(); }).detach();
                                    else std::thread([]() { DisableAimbotDrag(); }).detach();
                                }
                                if (edited::Checkbox("Aimbot In-Game [ Neck ]", "Works In-Game", &aimbot_n)) {
                                    if (aimbot_n) std::thread([]() { EnableAimbotNeck(); }).detach();
                                    else std::thread([]() { DisableAimbotNeck(); }).detach();
                                }
                                if (edited::Checkbox("No Recoil", "Works In-Game & Lobby", &noRecoil)) {
                                    if (noRecoil) std::thread([]() { EnableNoRecoil(); }).detach();
                                    else std::thread([]() { DisableNoRecoil(); }).detach();
                                }
                                if (!isEssentialOrUltra) ImGui::EndDisabled();

                                if (!isUltra) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Aimbot In-Game [ Body ]", "Works In-Game & Lobby", &aimbot_b)) {
                                    if (bodyType == "None") notificationSystem.AddNotification("Error", "Invalid Selection", ImGui::GetColorU32(c::accent));
                                    else if (bodyType == "Body") std::thread([]() { AimbotBody(); }).detach();
                                    else if (bodyType == "Body V2") std::thread([]() { AimbotBodyV2(); }).detach();
                                }
                                const char* aimbotItems[3]{ "None", "Body", "Body V2" };
                                static int aimbotBodySelected = StringToIndex(currentConfig.aimbotBodyType, aimbotItems, IM_ARRAYSIZE(aimbotItems));
                                static int aimbotBodyPreviousSelect = aimbotBodySelected;
                                ImGui::Combo("Aimbot Body Type", &aimbotBodySelected, aimbotItems, IM_ARRAYSIZE(aimbotItems), 3);
                                if (aimbotBodySelected != aimbotBodyPreviousSelect) {
                                    if (aimbotBodySelected == 0) bodyType = "None";
                                    else if (aimbotBodySelected == 1) bodyType = "Body";
                                    else if (aimbotBodySelected == 2) bodyType = "Body V2";
                                    currentConfig.aimbotBodyType = bodyType;
                                    aimbotBodyPreviousSelect = aimbotBodySelected;
                                    if (autosave) SaveConfig(currentConfig);
                                }
                                if (!isUltra) ImGui::EndDisabled();

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 60), c::elements::rounding);
                                }
                                /*
                                static int smooth = 165;
                                if (ImGui::SliderInt("Smoothness", &smooth, 0, 400)) {
                                    std::string message = "Smoothness:" + std::to_string(smooth) + "\n";

                                }

                                static int speed = 75;
                                if (ImGui::SliderInt("Speed", &speed, 0, 100, "%d%%")) {
                                    std::string message = "Speed:" + std::to_string(speed) + "\n";

                                }*/

                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);

                            edited::BeginChild("f", "Scope Functions", ImVec2((c::background::size.x - 60) / 2, 135), ImGuiChildFlags_None);
                            {
                                bool isEssentialOrUltra33 = (AuthlyXApp.userData.subscription == "Essential" || AuthlyXApp.userData.subscription == "Ultra");
                                if (!isEssentialOrUltra33) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Scope Tracking [ 2X ]", "Works In-Game & Lobby", &aimbot_2x)) {
                                    if (aimbot_2x) std::thread([]() { EnableScopeTracking2X(); }).detach();
                                    else std::thread([]() { DisableScopeTracking2X(); }).detach();
                                }
                                if (edited::Checkbox("Scope Tracking [ 4X ]", "Works In-Game & Lobby", &aimbot_4x)) {
                                    if (aimbot_4x) std::thread([]() { EnableScopeTracking4X(); }).detach();
                                    else std::thread([]() { DisableScopeTracking4X(); }).detach();
                                }
                                if (!isEssentialOrUltra33) ImGui::EndDisabled();

                                if (!isEssentialOrUltra33) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 130), c::elements::rounding);
                                }
                            }
                            edited::EndChild();

                            ImGui::SetCursorPos(ImVec2(325, 250));

                            edited::BeginChild("m", "Advanced Aim Functions", ImVec2((c::background::size.x - 60) / 2, 250), ImGuiChildFlags_None);
                            {
                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");

                                if (!isUltra) ImGui::BeginDisabled(true);
                                /*if (edited::Checkbox("Unlimited Ammo", "Works In-Game & Lobby", &unlimitedAmmo)) {
                                    if (unlimitedAmmo) EnableUnlimitedAmmo();
                                    else DisableUnlimitedAmmo();
                                }*/
                                if (edited::Checkbox("Fast Reload", "Works In-Game & Lobby", &fastReload)) {
                                    if (fastReload) std::thread([]() { EnableFastReload(); }).detach();
                                    else std::thread([]() { DisableFastReload(); }).detach();
                                }
                                if (edited::Checkbox("Fast Fire", "Works In-Game & Lobby", &fastfire)) {
                                    if (fastfire) std::thread([]() { EnableFastFire(); }).detach();
                                    else std::thread([]() { DisableFastFire(); }).detach();
                                }
                                if (edited::Checkbox("Female Fix", "Works In-Lobby", &femaleFix)) {
                                    if (femaleFix) notificationSystem.AddNotification("Success", "Female Fix Enabled", ImGui::GetColorU32(c::accent));
                                    else notificationSystem.AddNotification("Success", "Female Fix Disabled", ImGui::GetColorU32(c::accent));
                                }
                                if (edited::Checkbox("Glitch Fire", "Works In-Lobby", &glitchFire)) {
                                    if (glitchFire) std::thread([]() { EnableGlitchFire(); }).detach();
                                    else std::thread([]() { DisableGlitchFire(); }).detach();
                                }
                                if (!isUltra) ImGui::EndDisabled();

                                if (edited::Checkbox("Reset Guest", "Works In-Login", &resetGuest)) {
                                    if (resetGuest) std::thread([]() { ResetGuest(); }).detach();
                                }

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 100), c::elements::rounding);
                                }
                            }
                            edited::EndChild();

                        }
                        else if (active_tab == 1)
                        {
                            edited::BeginChild("b", "Misc Functions", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {

                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");

                                if (!isUltra) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Load Wall Hack", "Works In-Game & Lobby", &loadWallHack)) {
                                    if (loadWallHack) std::thread([]() { LoadWallHack(); }).detach();
                                }
                                if (edited::Checkbox("Wall Hack", "Works In-Game & Lobby", &wallHack)) {
                                    if (wallHack) std::thread([]() { EnableWallHack(); }).detach();
                                    else std::thread([]() { DisableWallHack(); }).detach();
                                }
                                if (edited::Checkbox("Load Speed Hack", "Works In-Game & Lobby", &loadSpeedHack)) {
                                    std::thread([]() { LoadSpeedHack(); }).detach();
                                }
                                if (edited::Checkbox("Speed Hack", "Works In-Game & Lobby", &speedHack)) {
                                    if (speedHack) std::thread([]() { EnableSpeedHack(); }).detach();
                                    else std::thread([]() { DisableSpeedHack(); }).detach();
                                }
                                if (edited::Checkbox("Load Camera Left", "Works In-Game & Lobby", &loadCameraLeft)) {
                                    std::thread([]() { LoadCameraLeft(); }).detach();
                                }
                                if (edited::Checkbox("Camera Left", "Works In-Game & Lobby", &CameraLeft)) {
                                    if (CameraLeft) std::thread([]() { EnableCameraLeft(); }).detach();
                                    else std::thread([]() { DisableCameraLeft(); }).detach();
                                }
                                if (edited::Checkbox("Fast Landing", "Works In-Game & Lobby", &fastLanding)) {
                                    if (fastLanding) std::thread([]() { EnableFastLanding(); }).detach();
                                    else std::thread([]() { DisableFastLanding(); }).detach();
                                }
                                if (!isUltra) ImGui::EndDisabled();

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 130), c::elements::rounding);
                                }

                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);

                            edited::BeginChild("g", "Chams Functions", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {
                                static bool chams3D = false;
                                if (edited::Checkbox("Chams 3D", "Works In-Game & Lobby", &chams3D)) {
                                    notificationSystem.AddNotification("Success", "Chams 3D Enabled", ImGui::GetColorU32(c::accent));
                                }
                                
                                bool isExtendedOrUltra2 = (AuthlyXApp.userData.subscription == "Essential" || AuthlyXApp.userData.subscription == "Ultra");

                                if (!isExtendedOrUltra2) ImGui::BeginDisabled(true);
                                static bool chamsGlow = false;
                                if (edited::Checkbox("Chams Glow", "Works In-Game & Lobby", &chamsGlow)) {
                                    notificationSystem.AddNotification("Success", "Chams Glow Enabled", ImGui::GetColorU32(c::accent));
                                }
                                static bool chamsHDR = false;
                                if (edited::Checkbox("Chams HDR", "Works In-Game & Lobby", &chamsHDR)) {
                                    notificationSystem.AddNotification("Success", "Chams HDR Enabled", ImGui::GetColorU32(c::accent));
                                }
                                static bool chamaMenu = false;
                                if (edited::Checkbox("Chams Menu", "Works In-Game & Lobby", &chamaMenu)) {
                                    if (chamsMenuType == "None") notificationSystem.AddNotification("Error", "Invalid Selection", ImGui::GetColorU32(c::accent));
                                    else if (chamsMenuType == "Old") notificationSystem.AddNotification("Success", "Chams Menu Old Enabled", ImGui::GetColorU32(c::accent));
                                    else if (chamsMenuType == "New") notificationSystem.AddNotification("Success", "Chams Menu New Enabled", ImGui::GetColorU32(c::accent));
                                    else if (chamsMenuType == "Overlay") notificationSystem.AddNotification("Success", "Chams Menu Overlay Enabled", ImGui::GetColorU32(c::accent));
                                    else if (chamsMenuType == "OverlayV2") notificationSystem.AddNotification("Success", "Chams Menu OverlayV2 Enabled", ImGui::GetColorU32(c::accent));
                                }
                                const char* chamsItems[5]{ "None", "Old", "New", "Overlay", "OverlayV2" };
                                static int chamsSelected = StringToIndex(currentConfig.chamsMenuType, chamsItems, IM_ARRAYSIZE(chamsItems));
                                static int chamsPreviousSelect = chamsSelected;
                                ImGui::Combo("Chams Menu Type", &chamsSelected, chamsItems, IM_ARRAYSIZE(chamsItems), 5);
                                if (chamsSelected != chamsPreviousSelect) {
                                    if (chamsSelected == 0) chamsMenuType = "None";
                                    else if (chamsSelected == 1) chamsMenuType = "Old";
                                    else if (chamsSelected == 2) chamsMenuType = "New";
                                    else if (chamsSelected == 3) chamsMenuType = "Overlay";
                                    else if (chamsSelected == 4) chamsMenuType = "OverlayV2";
                                    currentConfig.chamsMenuType = chamsMenuType;
                                    chamsPreviousSelect = chamsSelected;
                                    if (autosave) SaveConfig(currentConfig);
                                }
                                if (!isExtendedOrUltra2) ImGui::EndDisabled();

                                if (!isExtendedOrUltra2) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 80), c::elements::rounding);
                                }

                                /*static int espdst = 150;
                                if (ImGui::SliderInt("ESP Distance", &espdst, 0, 200, "%dM%"))
                                {
                                    std::string message = "EspDistance:" + std::to_string(espdst) + "\n";

                                }

                                static int select1 = 0;
                                static int previousSelect5 = -1;
                                const char* items1[3]{ "Top", "Centre", "Bottom" };
                                ImGui::Combo("ESP Anchor Point", &select1, items1, IM_ARRAYSIZE(items1), 3);
                                if (select1 != previousSelect5) {

                                    if (select1 == 0) {


                                    }
                                    else if (select1 == 1) {


                                    }
                                    else if (select1 == 2) {


                                    }
                                    previousSelect5 = select1;
                                }*/

                            }
                            edited::EndChild();

                        }
                        else if (active_tab == 2)
                        {
                            edited::BeginChild("c", "Sniper Functions", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {
                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");
                                bool isExtendedOrUltra3 = (AuthlyXApp.userData.subscription == "Essential" || AuthlyXApp.userData.subscription == "Ultra");



                                if (!isExtendedOrUltra3) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Sniper Scope", "Works In-Game & Lobby", &sniperScope)) {
                                    if (sniperScope) std::thread([]() { EnableSniperScope(); }).detach();
                                    else std::thread([]() { DisableSniperScope(); }).detach();
                                }
                                if (!isExtendedOrUltra3) ImGui::EndDisabled();

                                if (!isUltra) ImGui::BeginDisabled(true);
                                static std::string sniperSwitchType = "V1";
                                if (edited::Checkbox("Sniper Switch", "Works In-Game & Lobby", &sniperSwitch)) {
                                    if(sniperSwitch) std::thread([]() { EnableSniperSwitch(); }).detach();
                                    else std::thread([]() { DisableSniperSwitch(); }).detach();
                                }
                                const char* sniperItems[2]{ "V1", "V2" };
                                static int sniperSelected = StringToIndex(currentConfig.sniperSwitchType, sniperItems, IM_ARRAYSIZE(sniperItems));
                                ImGui::Combo("Sniper Switch Type", &sniperSelected, sniperItems, IM_ARRAYSIZE(sniperItems), 2);
                                if (edited::Checkbox("Sniper Aim", "Works In-Game & Lobby", &sniperAim)) {
                                    notificationSystem.AddNotification("Info", "Sniper Aim Toggled", ImGui::GetColorU32(c::accent));
                                }
                                if (edited::Checkbox("Sniper Delay Fix", "Works In-Game & Lobby", &sniperDelay)) {
                                    if(sniperDelay) std::thread([]() { EnableDelayFix(); }).detach();
                                    else std::thread([]() { DisableDelayFix(); }).detach();
                                }
                                if (edited::Checkbox("Sniper Location", "Works In-Game & Lobby", &sniperLocation)) {
                                    if (LocationType == "None") notificationSystem.AddNotification("Error", "Invalid Selection", ImGui::GetColorU32(c::accent));
                                    else if (LocationType == "AWM" && LocationMode == "On") {
                                        std::thread([]() { EnableAWMLocation(); }).detach();
                                    }
                                    else if (LocationType == "AWM" && LocationMode == "Off") {
                                        std::thread([]() { DisableAWMLocation(); }).detach();
                                    }
                                    else if (LocationType == "AWM-Y" && LocationMode == "On") {
                                        std::thread([]() { EnableAWMYLocation(); }).detach();
                                    }
                                    else if (LocationType == "AWM-Y" && LocationMode == "Off") {
                                        std::thread([]() { DisableAWMYLocation(); }).detach();
                                    }
                                    else if (LocationType == "VSK94" && LocationMode == "On") {
                                        std::thread([]() { EnableVSK94Location(); }).detach();
                                    }
                                    else if (LocationType == "VSK94" && LocationMode == "Off") {
                                        std::thread([]() { DisableVSK94Location(); }).detach();
                                    }
                                    else if (LocationType == "M82B" && LocationMode == "On") {
                                        std::thread([]() { EnableM82BLocation(); }).detach();
                                    }
                                    else if (LocationType == "M82B" && LocationMode == "Off") {
                                        std::thread([]() { DisableM82BLocation(); }).detach();
                                    }
                                }
                                //Mode
                                const char* sniperLocationModeItems[2]{ "Off", "On"};
                                static int sniperLocModeSelected = StringToIndex(currentConfig.sniperLocationMode, sniperLocationModeItems, IM_ARRAYSIZE(sniperLocationModeItems));
                                static int sniperLocModePrev = sniperLocModeSelected;
                                ImGui::Combo("Location Mode", &sniperLocModeSelected, sniperLocationModeItems, IM_ARRAYSIZE(sniperLocationModeItems), 3);
                                if (sniperLocModeSelected != sniperLocModePrev) {
                                    if (sniperLocModeSelected == 0) LocationMode = "Off";
                                    else if (sniperLocModeSelected == 1) LocationMode = "On";
                                    currentConfig.sniperLocationMode = LocationMode;
                                    sniperLocModePrev = sniperLocModeSelected;
                                    if (autosave) SaveConfig(currentConfig);
                                }
                                // Type
                                const char* sniperLocationItems[5]{ "None", "AWM", "AWM-Y", "VSK94", "M82B"};
                                static int sniperLocTypeSelected = StringToIndex(currentConfig.sniperLocationType, sniperLocationItems, IM_ARRAYSIZE(sniperLocationItems));
                                static int sniperLocTypePrev = sniperLocTypeSelected;
                                ImGui::Combo("Location Type", &sniperLocTypeSelected, sniperLocationItems, IM_ARRAYSIZE(sniperLocationItems), 3);
                                if (sniperLocTypeSelected != sniperLocTypePrev) {
                                    if (sniperLocTypeSelected == 0) LocationType = "None";
                                    else if (sniperLocTypeSelected == 1) LocationType = "AWM";
                                    else if (sniperLocTypeSelected == 2) LocationType = "AWM-Y";
                                    else if (sniperLocTypeSelected == 3) LocationType = "VSK94";
                                    else if (sniperLocTypeSelected == 4) LocationType = "M82B";
                                    currentConfig.sniperLocationType = LocationType;
                                    sniperLocTypePrev = sniperLocTypeSelected;
                                    if (autosave) SaveConfig(currentConfig);
                                }
                                if (!isUltra) ImGui::EndDisabled();

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos(); ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 130), c::elements::rounding);
                                }
                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);

                            edited::BeginChild("d", "Fake Lag", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {
                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");
                                if (!isUltra) ImGui::BeginDisabled(true);
                                if (edited::Checkbox("Fake Lag - Enable", "Active Anywhere", &fake_lag)) {
                                    notificationSystem.AddNotification("Notification", "Fake Lag Toggled", ImGui::GetColorU32(c::accent));
                                }
                                ImGui::SliderFloat("Delay", &fakelag2, 0.0f, 10.0f, "%0.01fS");
                                edited::Keybind("Fake Lag - Key", "Assign Key For Fake Lag", &fakelag_key);
                                if (!isUltra) ImGui::EndDisabled();

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos(); ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 130), c::elements::rounding);
                                }
                            }
                            edited::EndChild();
                        }
                        else if (active_tab == 3)
                        {
                            
                            edited::BeginChild("d", "Aimbot Key Binds", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {

                                edited::Keybind("Aimbot Head - Key", "Assign Key For Aimbot Head", &aim_head);

                                bool isExt = (AuthlyXApp.userData.subscription == "Essential" || AuthlyXApp.userData.subscription == "Ultra");
                                bool isUltra = (AuthlyXApp.userData.subscription == "Ultra");

                                if (!isExt) ImGui::BeginDisabled(true);
                                edited::Keybind("Aimbot Drag - Key", "Assign Key For Aimbot Drag", &aim_drag);
                                edited::Keybind("Aimbot Neck - Key", "Assign Key For Aimbot Neck", &aim_neck);
                                if (!isExt) ImGui::EndDisabled();

                                ImGui::Spacing();

                                if (!isUltra) ImGui::BeginDisabled(true);
                                edited::Keybind("Wall Hack - Key", "Assign Key For Wall Hack", &wall_hack);
                                edited::Keybind("Speed Hack - Key", "Assign Key For Speed Hack", &speed_hack);
                                edited::Keybind("Camera Left - Key", "Assign Key For Camera Left", &camera_hack);
                                if (!isUltra) ImGui::EndDisabled();

                                if (!isUltra) {
                                    ImVec2 p_min = ImGui::GetWindowPos();
                                    ImVec2 p_max = p_min + ImGui::GetWindowSize();
                                    ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(0, 0, 0, 80), c::elements::rounding);
                                }

                            }
                            edited::EndChild();


                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);

                            edited::BeginChild("i", "Streamer Key Binds", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {

                                edited::Keybind("Streamer Mode - Key", "Assign Key For Streamer Mode", &streamer_mode);

                                ImGui::SetCursorPos(ImVec2(63.5, ImGui::GetCursorPosY() + 25 - ImGui::CalcTextSize("P").y / 2));
                                ImGui::PushFont(font::tab_font);
                                ImGui::TextColored(c::accent, "Press ");
                                ImGui::PopFont();

                                draw->AddRectFilled(ImVec2(637.5, 197), ImVec2(637.5 + ImGui::CalcTextSize("INS").x + 10, 215), ImGui::GetColorU32(c::accent, 0.4f), 3.f);

                                ImGui::SetCursorPos(ImVec2(151.5, 85));
                                ImGui::PushFont(font::tab_font);
                                ImGui::TextColored(c::accent, "to Hide the Menu");
                                ImGui::PopFont();

                                ImGui::SetCursorPos(ImVec2(113, 85));
                                ImGui::TextColored(ImVec4(1.f, 1.f, 1.f, 0.5f), "INS");

                            }
                            edited::EndChild();



                        }
                        else if (active_tab == 4)
                        {
                            edited::BeginChild("g", "Settings", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {
                                edited::ColorEdit4("Main Color", "Setting the main color of the menu.", color, picker_flags);

                                static float previousColor[4] = { color[0], color[1], color[2], color[3] };
                                if (color[0] != previousColor[0] || color[1] != previousColor[1] ||
                                    color[2] != previousColor[2] || color[3] != previousColor[3]) {

                                    currentConfig.colorR = color[0];
                                    currentConfig.colorG = color[1];
                                    currentConfig.colorB = color[2];
                                    currentConfig.colorA = color[3];

                                    c::accent = { color[0], color[1], color[2], 1.f };

                                    if (autosave) SaveConfig(currentConfig);

                                    previousColor[0] = color[0];
                                    previousColor[1] = color[1];
                                    previousColor[2] = color[2];
                                    previousColor[3] = color[3];
                                }


                                if (edited::Checkbox("Streamer Mode", "Hides panel and cheats in stream", &streammode))
                                {
                                    currentConfig.streamerMode = streammode;

                                    if (autosave) SaveConfig(currentConfig);

                                    if (streammode) { 
                                        notificationSystem.AddNotification("Done", "Stream Mode Enabled!", ImGui::GetColorU32(c::accent));

                                        SetWindowDisplayAffinity(GetActiveWindow(), WDA_EXCLUDEFROMCAPTURE);
                                        ITaskbarList* pTaskList = NULL;
                                        HRESULT initRet = CoInitialize(NULL);
                                        HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
                                            NULL,
                                            CLSCTX_INPROC_SERVER,
                                            IID_ITaskbarList,
                                            (LPVOID*)&pTaskList);

                                        if (createRet == S_OK)
                                        {
                                            pTaskList->DeleteTab(GetActiveWindow());
                                            pTaskList->Release();
                                        }
                                        CoUninitialize();
                                    }
                                    else {
                                        notificationSystem.AddNotification("Done", "Stream Mode Disabled!", ImGui::GetColorU32(c::accent));

                                        SetWindowDisplayAffinity(GetActiveWindow(), WDA_NONE);
                                        ITaskbarList* pTaskList = NULL;
                                        HRESULT initRet = CoInitialize(NULL);
                                        HRESULT createRet = CoCreateInstance(CLSID_TaskbarList,
                                            NULL,
                                            CLSCTX_INPROC_SERVER,
                                            IID_ITaskbarList,
                                            (LPVOID*)&pTaskList);

                                        if (createRet == S_OK)
                                        {
                                            pTaskList->AddTab(GetActiveWindow());
                                            pTaskList->Release();
                                        }
                                    }
                                }
                                
                                if (edited::Checkbox("Auto Save Settings", "Auto Save & Load on Next Launch", &autosave))
                                {
                                    currentConfig.autoSave = autosave;

                                    SaveConfig(currentConfig);

                                    if (autosave) {
                                        notificationSystem.AddNotification("Info", "Auto Save Enabled", ImGui::GetColorU32(c::accent));
                                    }
                                    else {
                                        notificationSystem.AddNotification("Info", "Auto Save Disabled", ImGui::GetColorU32(c::accent));
                                    }
                                }
                                
                                if (edited::Checkbox("Discord RPC", "Display Application status on Discord", &discordrpc))
                                {
                                    currentConfig.discordRPC = discordrpc;

                                    if (autosave) {
                                        SaveConfig(currentConfig);
                                    }

                                    if (discordrpc) {
                                        if (authed) {
                                            std::time_t CurrentTime = std::time(0);
                                            std::string username = "User: " + AuthlyXApp.userData.username;
                                            std::string expiry = AuthlyXApp.userData.expiryDate;
                                            std::time_t expiryTime = std::atoi(expiry.c_str());
                                            std::string expdate = "Expiry: " + AuthlyXApp.userData.expiryDate;
                                            DiscordEventHandlers Handle;
                                            memset(&Handle, 0, sizeof(Handle));
                                            Discord_Initialize("1350087937236406292", &Handle, 1, NULL);
                                            DiscordRichPresence discordPresence;
                                            memset(&discordPresence, 0, sizeof(discordPresence));
                                            char formattedExpiry[17];
                                            std::tm* tmPtr = std::localtime(&expiryTime);
                                            std::strftime(formattedExpiry, sizeof(formattedExpiry), "Days: %m/%d/%y", tmPtr);
                                            discordPresence.state = expdate.c_str();
                                            discordPresence.details = username.c_str();
                                            discordPresence.startTimestamp = CurrentTime;
                                            discordPresence.largeImageKey = "https://i.ibb.co/Pv2K78rK/bruuuh-no-bg-blue.png";
                                            discordPresence.largeImageText = "BRUUUH EXTERNAL C++";
                                            discordPresence.smallImageKey = "https://i.gifer.com/3OWpa.gif";
                                            discordPresence.smallImageText = "Your Unfair Advantage";
                                            discordPresence.button1_label = "Discord";
                                            discordPresence.button1_url = "https://discord.gg/fF9RCMVaGT";
                                            discordPresence.button2_label = "Website";
                                            discordPresence.button2_url = "https://bruuuhcheats.xyz";
                                            Discord_UpdatePresence(&discordPresence);
                                        }
                                        notificationSystem.AddNotification("Info", "Discord RPC Enabled", ImGui::GetColorU32(c::accent));
                                    }
                                    else {
                                        DisableDiscordRPC();
                                        notificationSystem.AddNotification("Info", "Discord RPC Disabled", ImGui::GetColorU32(c::accent));
                                    }
                                }

                                const char* beepItems[2]{ "Yes", "No" };
                                static int beepSelected = currentConfig.Sound ? 0 : 1;
                                static int beepPreviousSelect = beepSelected;

                                ImGui::Combo("Sound", &beepSelected, beepItems, IM_ARRAYSIZE(beepItems), 2);
                                if (beepSelected != beepPreviousSelect) {
                                    sound = (beepSelected == 0);
                                    currentConfig.Sound = sound;
                                    beepPreviousSelect = beepSelected;

                                    if (autosave) SaveConfig(currentConfig);
                                }

                                if (edited::Checkbox("Disable All Animations", "Turn off all UI animations", &disableAllAnimations))
                                {
                                    currentConfig.disableAllAnimations = disableAllAnimations;
                                    if (autosave) SaveConfig(currentConfig);

                                    if (disableAllAnimations) {
                                        notificationSystem.AddNotification("Info", "All Animations Disabled", ImGui::GetColorU32(c::accent));
                                    }
                                    else {
                                        notificationSystem.AddNotification("Info", "Animations Enabled", ImGui::GetColorU32(c::accent));
                                    }
                                }

                                // Emulator selector
                                static int emulatorPrev = emulatorSelected;
                                ImGui::Combo("Emulator", &emulatorSelected, emulatorDisplayNames, IM_ARRAYSIZE(emulatorDisplayNames), 6);
                                if (emulatorSelected != emulatorPrev) {
                                    emulatorPrev = emulatorSelected;
                                    currentConfig.emulatorMode = emulatorDisplayNames[emulatorSelected];
                                    notificationSystem.AddNotification("Info",
                                        (std::string("Emulator: ") + emulatorDisplayNames[emulatorSelected]).c_str(),
                                        ImGui::GetColorU32(c::accent));
                                    if (autosave) SaveConfig(currentConfig);
                                }

                                ImGui::Spacing();
                            }
                            edited::EndChild();

                            ImGui::SameLine(0, 10);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 40);

                            edited::BeginChild("g", "Info", ImVec2((c::background::size.x - 60) / 2, 430), ImGuiChildFlags_None);
                            {
                                //// Title with icon
                                //ImGui::PushFont(font::icomoon_widget2);
                                //ImGui::TextColored(c::accent, "e ");
                                //ImGui::PopFont();
                                //ImGui::SameLine();
                                //ImGui::Text("Information & Links");
                                //ImGui::Separator();

                                //ImGui::Spacing();

                                // Buttons with icons
                                if (edited::IconButton("b", "Discord Server", ImVec2(ImGui::GetContentRegionAvail().x, 40)))
                                {
                                    ShellExecute(NULL, "open", "https://discord.gg/fF9RCMVaGT", NULL, NULL, SW_SHOW);
                                    notificationSystem.AddNotification("Info", "Opening Discord...", ImGui::GetColorU32(c::accent));
                                }

                                //if (CustomIconButton("C", "Discord Server"))
                                //{
                                //    ShellExecute(NULL, "open", "https://discord.gg/fF9RCMVaGT", NULL, NULL, SW_SHOW);
                                //    notificationSystem.AddNotification("Info", "Opening Discord...", ImGui::GetColorU32(c::accent));
                                //}
                                ImGui::Spacing();

                                if (edited::IconButton("d", "Official Website", ImVec2(ImGui::GetContentRegionAvail().x, 40)))
                                {
                                    ShellExecute(NULL, "open", "https://bruuuhcheats.xyz", NULL, NULL, SW_SHOW);
                                    notificationSystem.AddNotification("Info", "Opening Website...", ImGui::GetColorU32(c::accent));
                                }

                                ImGui::Spacing();

                                if (edited::IconButton("f", "User Guide", ImVec2(ImGui::GetContentRegionAvail().x, 40)))
                                {
                                    //ShellExecute(NULL, "open", "https://docs.bruuuhcheats.xyz", NULL, NULL, SW_SHOW);
                                    notificationSystem.AddNotification("Info", "Coming Soon", ImGui::GetColorU32(c::accent));
                                }

                                ImGui::Spacing();
                                ImGui::Separator();

                                edited::IconLabel("c", "Version: 8.6 External", ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

                                std::string userText = "User: " + AuthlyXApp.userData.username;
                                edited::IconLabel("a", userText.c_str(), ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
                                
                                std::string keyText = "License: " + AuthlyXApp.userData.licenseKey;
                                edited::IconLabel("a", keyText.c_str(), ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

                                std::string subText = "Subscription: " + AuthlyXApp.userData.subscription;
                                edited::IconLabel("h", subText.c_str(), ImVec4(0.0f, 1.0f, 0.0f, 1.0f));

                                std::string expiryText = "Expires: " + AuthlyXApp.userData.expiryDate;
                                edited::IconLabel("g", expiryText.c_str(), ImVec4(0.8f, 0.8f, 0.8f, 1.0f));

                                ImGui::Spacing();
                                ImGui::Separator();
                            }
                            edited::EndChild();
                        }
                        

                        ImGui::PopStyleVar();

                    }
                    
                  
                    notificationSystem.DrawNotifications();
                    move_window();
                    ImGui::End();
                    RenderBlur(hwnd);

                }

            }
            
        }

        ImGui:: Render();

        const float clear_color_with_alpha[4] = { 0.f };

        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

   
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

