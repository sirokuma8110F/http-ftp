#include <3ds.h>
#include <citro2d.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "http_server.h"
#include "ftp_server.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

enum ServerMode {
    MODE_NONE,
    MODE_HTTP,
    MODE_FTP
};

void init_services() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    gfxSet3D(false); // Disable 3D for simplicity
}

void exit_services() {
    gfxExit();
}

void switch_server_mode(enum ServerMode *current_mode) {
    if (*current_mode == MODE_HTTP) {
        stop_http_server();
        start_ftp_server();
        *current_mode = MODE_FTP;
    } else if (*current_mode == MODE_FTP) {
        stop_ftp_server();
        start_http_server();
        *current_mode = MODE_HTTP;
    }
}

int main(int argc, char **argv) {
    init_services();

    printf("3DS Server starting...\n");

    enum ServerMode current_mode = MODE_NONE;

    // Start with HTTP server
    start_http_server();
    current_mode = MODE_HTTP;

    // Main loop
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        if (kDown & KEY_START) break;
        if (kDown & KEY_X) {
            switch_server_mode(&current_mode);
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    // Stop current server
    if (current_mode == MODE_HTTP) {
        stop_http_server();
    } else if (current_mode == MODE_FTP) {
        stop_ftp_server();
    }

    exit_services();
    return 0;
}
