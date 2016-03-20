#ifdef BACKEND_SDL

#include <arpa/inet.h>
#include <stdio.h>

#include "platform/common/config.h"
#include "platform/common/manager.h"
#include "platform/common/menu.h"
#include "platform/audio.h"
#include "platform/input.h"
#include "platform/gfx.h"
#include "platform/system.h"
#include "platform/ui.h"

#include <SDL2/SDL.h>

extern void gfxSetWindowSize(int width, int height);

static bool requestedExit;

bool systemInit(int argc, char* argv[]) {
    requestedExit = false;

    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0 || !gfxInit()) {
        return false;
    }

    audioInit();
    uiInit();
    inputInit();

    return true;
}

void systemExit() {
    inputCleanup();
    uiCleanup();
    audioCleanup();
    gfxCleanup();

    SDL_Quit();
}

void systemRun() {
    mgrRun();
}

bool systemIsRunning() {
    if(requestedExit) {
        return false;
    }

    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            requestedExit = true;
            return false;
        } else if(event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            gfxSetWindowSize(event.window.data1, event.window.data2);
        }
    }

    return true;
}

void systemRequestExit() {
    requestedExit = true;
}

const std::string systemIniPath() {
    return "gameyob.ini";
}

const std::string systemDefaultGbBiosPath() {
    return "gb_bios.bin";
}

const std::string systemDefaultGbcBiosPath() {
    return "gbc_bios.bin";
}

const std::string systemDefaultBorderPath() {
    return "default_border.png";
}

const std::string systemDefaultRomPath() {
    return "gb/";
}

void systemPrintDebug(const char* str, ...) {
    if(showConsoleDebug()) {
        va_list list;
        va_start(list, str);
        uiPrintv(str, list);
        va_end(list);

        uiFlush();
    }
}

bool systemGetIRState() {
    return false;
}

void systemSetIRState(bool state) {
}

const std::string systemGetIP() {
    return "";
}

int systemSocketListen(u16 port) {
    return -1;
}

FILE* systemSocketAccept(int listeningSocket, std::string* acceptedIp) {
    return NULL;
}

FILE* systemSocketConnect(const std::string ipAddress, u16 port) {
    return NULL;
}

void systemSetRumble(bool rumble) {
}

u32* systemGetCameraImage() {
    return NULL;
}

#endif