#include "Controller.hpp"

#define STICK_DEAD_ZONE 10000

static std::map<int, bool> connected_controllers = {
    {0, false},
    {1, false},
    {2, false},
    {3, false}};

Controller::Controller()
{
    DWORD dwResult;

    // Clear the state memory.
    ZeroMemory(&this->state, sizeof(XINPUT_STATE));

    // Trying to connect to one of the controllers.
    for (auto iter = connected_controllers.begin(); iter != connected_controllers.end(); iter++)
    {
        int num = iter->first;
        if (connected_controllers[num] == false)
        {
            dwResult = XInputGetState(num, &state);

            if (dwResult == ERROR_SUCCESS)
            {
                // The controller is now connected.
                this->connected = true;
                this->number = num;
                connected_controllers[num] = true;

                return;
            }
        }
    }

    // The controller is not connected.
    this->connected = false;
}

bool Controller::updateState()
{
    XINPUT_STATE new_state;

    // Clear the new state memory.
    ZeroMemory(&new_state, sizeof(XINPUT_STATE));

    // Getting the new state.
    XInputGetState(this->getNumber(), &new_state);

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

int Controller::getNumber()
{
    return this->number;
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

    if (dx > STICK_DEAD_ZONE)
        to->x = 1;

    if (dx < -STICK_DEAD_ZONE)
        to->x = -1;

    if (dy > STICK_DEAD_ZONE)
        to->y = 1;

    if (dy < -STICK_DEAD_ZONE)
        to->y = -1;

    return to;
}

Direction *Controller::getRightStickDirection()
{
    Point *curr = this->getRightStickState();

    int dx = curr->x;
    int dy = curr->y;

    Direction *to = new Direction();

    if (dx > STICK_DEAD_ZONE)
        to->x = 1;

    if (dx < -STICK_DEAD_ZONE)
        to->x = -1;

    if (dy > STICK_DEAD_ZONE)
        to->y = 1;

    if (dy < -STICK_DEAD_ZONE)
        to->y = -1;

    return to;
}

bool Controller::applyVibration(int speed, double time_mili)
{
    DWORD did_on, did_off;
    XINPUT_VIBRATION on, off;
    ZeroMemory(&on, sizeof(XINPUT_VIBRATION));
    ZeroMemory(&off, sizeof(XINPUT_VIBRATION));

    // The speed is too high.
    if (speed > 30000)
    {
        return false;
    }

    // Setting up the vibration.
    on.wLeftMotorSpeed = speed;
    on.wRightMotorSpeed = speed;
    off.wLeftMotorSpeed = 0;
    off.wRightMotorSpeed = 0;

    // Turnning the vibration on.
    did_on = XInputSetState(this->getNumber(), &on);

    // waiting.
    Sleep(time_mili);

    // Turnning the vibration off.
    did_off = XInputSetState(this->getNumber(), &off);

    return ERROR_SUCCESS == did_on && ERROR_SUCCESS == did_off;
}