#include "Includes.h"

using namespace ConsoleColor;
#define ColorText(color, text) (ConsoleColor::ColorText((color), (text)))

std::vector<HWND> owWindows;
std::atomic<bool> spamW(false);

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    char className[256];
    GetClassNameA(hwnd, className, sizeof(className));
    if (strcmp(className, "TankWindowClass") == 0 && IsWindowVisible(hwnd)) {
        owWindows.push_back(hwnd);
    }
    return TRUE;
}

static void PressAndHoldW(HWND hwnd) {
    SetForegroundWindow(hwnd);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    INPUT input{};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 'W';

    SendInput(1, &input, sizeof(INPUT));

    std::this_thread::sleep_for(std::chrono::seconds(5));

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

static void DoSpamLoop() {
    while (spamW) {
        for (size_t i = 0; i < owWindows.size(); ++i) {
            if (!spamW) break;

            HWND hwnd = owWindows[i];

            std::cout << ColorText(BLUE, _("    [!] "))
                << ColorText(WHITE, _("Holding W on Tab "))
                << ColorText(LIGHTBLUE, std::to_string(i + 1))
                << ColorText(WHITE, _("."))
                << std::endl;

            PressAndHoldW(hwnd);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        // another simple example
        /*
        for (HWND hwnd : owWindows) {
            if (!spamW) break;
            PressAndHoldW(hwnd);
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
        */
    }
}

static void ToggleSpam() {
    if (spamW) {
        spamW = false;
        system(_("cls"));
        std::cout << ColorText(RED, _("\n\n    [OFF] ")) << ColorText(WHITE, _("OW2 idleHelper Stopped.")) << std::endl;
    }
    else {
        system(_("cls"));
        std::cout << ColorText(GREEN, _("\n\n    [ON] ")) << ColorText(WHITE, _("Spam W in all OW2 windows.")) << std::endl;
        owWindows.clear();
        EnumWindows(EnumWindowsProc, 0);

        if (!owWindows.empty()) {
            spamW = true;
            std::thread(DoSpamLoop).detach(); // Background spam loop
        }
        else {
            std::cout << ColorText(YELLOW, _("\n\n    [??] ")) << ColorText(WHITE, _("No OW2 windows found.")) << std::endl;
        }
    }
}

static void MainGameLoop() {
    bool insertHeld = false;

    while (true) {
        if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
            if (!insertHeld) {
                insertHeld = true;
                ToggleSpam();
            }
        }
        else {
            insertHeld = false;
        }

        if (GetAsyncKeyState(VK_END) & 0x8000) {
            spamW = false;
            ExitProcess(0);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
	HWND console = GetConsoleWindow();
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	Console::Size(console, 600, 150);
	Console::Alpha(console);
	std::string consoleTitle = std::string(_("OW2 idleHelper | ")).append(Console::Decrypt(Console::RandomStr(10).c_str()).append(_(" | By Fer3on")).c_str()).c_str();
	SetConsoleTitleA(consoleTitle.c_str());

    system(_("cls"));
	std::cout << ColorText(CYAN, _("\n\n    [?] ")) << ColorText(WHITE, _("Waiting for Overwatch 2!")) << std::endl;

	while (!FindWindowA(_("TankWindowClass"), nullptr)) { Sleep(500); } // Waiting to overwatch if not launched yet
    system(_("cls"));

    std::cout << ColorText(GREEN, _("\n\n    [!] ")) << ColorText(WHITE, _("Press ")) << ColorText(LIGHTGREEN, _("INSERT ")) << ColorText(WHITE, _("to start idleHelper.")) << std::endl;
    std::cout << ColorText(MAGENTA, _("    [x] ")) << ColorText(WHITE, _("Press ")) << ColorText(LIGHTMAGENTA, _("END ")) << ColorText(WHITE, _("to close the application.")) << std::endl;
    MainGameLoop();

    return 0; // Useless but we need it to debug
}