#include "Controller.hpp"

#define DEAD_ZONE 10000

static const int controller_number = 0;

Controller::Controller()
{
    DWORD dwResult;

    // Clear the state memory.
    ZeroMemory(&this->state, sizeof(XINPUT_STATE));

    // Trying to connect.
    dwResult = XInputGetState(controller_number, &state);

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

bool Controller::updateState()
{
    XINPUT_STATE new_state;

    // Clear the new state memory.
    ZeroMemory(&new_state, sizeof(XINPUT_STATE));

    // Getting the new state.
    XInputGetState(controller_number, &new_state);

    bool change = (this->state.dwPacketNumber != new_state.dwPacketNumber);
    if (change)
    {
        this->state = new_state;
    }
    return change;
}

bool Controller::isConnected()
{
    return this->connected;
}

bool Controller::isButtonPressed(WORD button)
{
    this->updateState();

    WORD pressed = this->state.Gamepad.wButtons;

    WORD res = pressed & button;
    if (res != 0)
    {
        return true;
    }
    return false;
}

Point *Controller::getLeftStickState()
{
    this->updateState();

    float lx = this->state.Gamepad.sThumbLX;
    float ly = this->state.Gamepad.sThumbLY;

    return new Point(lx, ly);
}

Point *Controller::getRightStickState()
{
    this->updateState();

    float rx = this->state.Gamepad.sThumbRX;
    float ry = this->state.Gamepad.sThumbRY;

    return new Point(rx, ry);
}

int Controller::getLeftTriggerState()
{
    return (int)this->state.Gamepad.bLeftTrigger;
}

int Controller::getRightTriggerState()
{
    return (int)this->state.Gamepad.bRightTrigger;
}

Direction *Controller::getLeftStickDirection()
{
    Point *curr = this->getLeftStickState();

    int dx = curr->x;
    int dy = curr->y;

    Direction *to = new Direction();

    if (dx > DEAD_ZONE)
        to->x = 1;

    if (dx < -DEAD_ZONE)
        to->x = -1;

    if (dy > DEAD_ZONE)
        to->y = 1;

    if (dy < -DEAD_ZONE)
        to->y = -1;

    return to;
}

Direction *Controller::getRightStickDirection()
{
    Point *curr = this->getRightStickState();

    int dx = curr->x;
    int dy = curr->y;

    Direction *to = new Direction();

    if (dx > DEAD_ZONE)
        to->x = 1;

    if (dx < -DEAD_ZONE)
        to->x = -1;

    if (dy > DEAD_ZONE)
        to->y = 1;

    if (dy < -DEAD_ZONE)
        to->y = -1;

    return to;
}