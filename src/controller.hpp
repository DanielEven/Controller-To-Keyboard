#include <windows.h>
#include <Xinput.h>
#include "Point.hpp"

#pragma comment(lib, "Xinput.lib")

class Controller
{
private:
    XINPUT_STATE state;
    bool connected;

    bool updateState();

public:
    Controller();

    // Getting information about the controller.

    // Checking if the controller is connected.
    bool isConnected();

    // Checking if a specific button is pressed
    bool isButtonPressed(WORD button);
};

/*
#define XINPUT_GAMEPAD_DPAD_UP          0x0001
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008
#define XINPUT_GAMEPAD_START            0x0010
#define XINPUT_GAMEPAD_BACK             0x0020
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
#define XINPUT_GAMEPAD_A                0x1000
#define XINPUT_GAMEPAD_B                0x2000
#define XINPUT_GAMEPAD_X                0x4000
#define XINPUT_GAMEPAD_Y                0x8000
*/