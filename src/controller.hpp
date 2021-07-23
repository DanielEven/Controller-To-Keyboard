#include <windows.h>
#include <Xinput.h>
#include "Point.hpp"
#include "Direction.hpp"
#include <map>

#pragma comment(lib, "Xinput.lib")
#pragma once

class Controller
{
private:
    XINPUT_STATE state;
    bool connected;
    int number;

    // Updating the controller's state.
    // The function returns true if there is a change.
    bool updateState();

public:
    Controller();

    /* Getting information about the controller. */

    // Checking if the controller is connected.
    bool isConnected();

    // Getting the controller's number
    int getNumber();

    // Checking if a specific button is pressed.
    bool isButtonPressed(WORD button);

    // Gettting the State of the left stick.
    Point *getLeftStickState();
    // Gettting the State of the right stick.
    Point *getRightStickState();

    // Getting the state of the left trigger control.
    int getLeftTriggerState();
    // Getting the state of the right trigger control.
    int getRightTriggerState();

    // A function that calculates what is the left stick's direction.
    Direction *getLeftStickDirection();
    // A function that calculates what is the right stick's direction.
    Direction *getRightStickDirection();

    // A function that makes a vibration in the controller.
    // speed: the vibration speed, a number between 0 - 30000.
    // time_mili: the time of vibration in mili seconds.
    bool applyVibration(int speed, double time_mili);
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