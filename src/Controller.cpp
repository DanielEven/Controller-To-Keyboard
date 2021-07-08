#include "Controller.hpp"

bool Controller::updateState()
{
    XINPUT_STATE new_state;

    // Clear the new state memory.
    ZeroMemory(&new_state, sizeof(XINPUT_STATE));

    // Getting the new state.
    XInputGetState(0, &new_state);

    return (this->state.dwPacketNumber != new_state.dwPacketNumber);
}

Controller::Controller()
{
    DWORD dwResult;

    // Clear the state memory.
    ZeroMemory(&this->state, sizeof(XINPUT_STATE));

    // Trying to connect.
    dwResult = XInputGetState(0, &state);

    if (dwResult == ERROR_SUCCESS)
    {
        // The controller is connected.
        this->connected = true;
    }
    else
    {
        // The controller is not connected.
        this->connected = false;
    }
}

bool Controller::isConnected()
{
    return this->connected;
}

bool Controller::isButtonPressed(WORD button)
{
    WORD pressed = this->state.Gamepad.wButtons;

    WORD res = pressed & button;
    if (res != 0)
    {
        return true;
    }
    return false;
}