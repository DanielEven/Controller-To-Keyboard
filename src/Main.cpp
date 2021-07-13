#include "Controller.hpp"
#include "Mapping.hpp"
#include "KeyboardManager.hpp"
#include "ConfigurationReader.hpp"

#include <set>
#include <time.h>

void updateButtons(Controller *c);
void updateSticks(Controller *c);
void updateTriggers(Controller *c);
void sleep(double mili);
void printMessage();

# define DELAY_BETWEEN_PRESSING 200

int main()
{
    printMessage();

    // Reading and setting the configurations.
    if (!setConfigurations())
        return -1;

    Controller *c = new Controller();

    while (!c->isButtonPressed(XINPUT_GAMEPAD_BACK))
    {
        updateButtons(c);
        updateSticks(c);
        updateTriggers(c);

        sleep(DELAY_BETWEEN_PRESSING);
    }

    return 0;
}

// A map of the pressed buttons.
std::map<WORD, bool> pressed_mapping = {
    {XINPUT_GAMEPAD_DPAD_UP, false},
    {XINPUT_GAMEPAD_DPAD_DOWN, false},
    {XINPUT_GAMEPAD_DPAD_LEFT, false},
    {XINPUT_GAMEPAD_DPAD_RIGHT, false},
    {XINPUT_GAMEPAD_START, false},
    {XINPUT_GAMEPAD_BACK, false},
    {XINPUT_GAMEPAD_LEFT_THUMB, false},
    {XINPUT_GAMEPAD_RIGHT_THUMB, false},
    {XINPUT_GAMEPAD_LEFT_SHOULDER, false},
    {XINPUT_GAMEPAD_RIGHT_SHOULDER, false},
    {XINPUT_GAMEPAD_A, false},
    {XINPUT_GAMEPAD_B, false},
    {XINPUT_GAMEPAD_X, false},
    {XINPUT_GAMEPAD_Y, false}};

/*************************
    This function updates the keyboard according to the controller's buttons.

    Steps:
    1. Create the current button set.
    2. Checking if there are released buttons, and releasing the keys.
    3. Pressing the new keys.
*************************/
void updateButtons(Controller *c)
{

    // 1
    std::set<WORD, greater<WORD>> current;

    for (auto iter = button_mapping.begin(); iter != button_mapping.end(); iter++)
    {
        WORD button = iter->first;
        if (c->isButtonPressed(button))
        {
            current.insert(button);
        }
    }

    // 2
    for (auto iter = pressed_mapping.begin(); iter != pressed_mapping.end(); iter++)
    {
        WORD button = iter->first;
        if (pressed_mapping[button] == true) // This is a pressed button.
        {
            if (current.count(button) == 0)
            {
                // We stopped pressing the button.
                releaseKey(button_mapping[button]);
                pressed_mapping[button] = false;
            }
        }
    }

    // 3
    for (auto iter = current.begin(); iter != current.end(); iter++)
    {
        WORD button = (*iter);
        holdKey(button_mapping[button]);
        pressed_mapping[button] = true;
    }
}

// A map of the moving sticks.
/*
L - Left
R - Right
*/
std::map<char, bool> moving_sticks_mapping = {
    {'L', false},
    {'R', false},
};

/*************************
    This function updates the keyboard according to the controller's sticks.

    Steps:
    1. Create the current moving sticks set.
    2. Checking if there are released sticks, and releasing the keys.
    3. Pressing the new keys.
*************************/
void updateSticks(Controller *c)
{
    const Direction *origin = new Direction(0, 0);

    // 1
    std::set<char, greater<char>> current;

    for (auto iter = moving_sticks_mapping.begin(); iter != moving_sticks_mapping.end(); iter++)
    {
        char stick = iter->first;
        Direction *dir;
        switch (stick)
        {
        case 'R':
            dir = c->getRightStickDirection();
            break;
        case 'L':
            dir = c->getLeftStickDirection();
            break;
        }
        if (!(*dir == *origin))
        {
            current.insert(stick);
        }
    }

    // 2
    for (auto iter = moving_sticks_mapping.begin(); iter != moving_sticks_mapping.end(); iter++)
    {
        char stick = iter->first;
        if (moving_sticks_mapping[stick] == true) // This is a moving stick.
        {
            if (current.count(stick) == 0)
            {
                // We stopped moving the stick.

                Direction *dir;
                switch (stick)
                {
                case 'R':
                    dir = c->getRightStickDirection();
                    if (dir->x != 0)
                        releaseKey(right_stick_x_mapping[dir->x]);
                    if (dir->y != 0)
                        releaseKey(right_stick_y_mapping[dir->y]);
                    break;
                case 'L':
                    dir = c->getLeftStickDirection();
                    if (dir->x != 0)
                        releaseKey(left_stick_x_mapping[dir->x]);
                    if (dir->y != 0)
                        releaseKey(left_stick_y_mapping[dir->y]);
                    break;
                }

                moving_sticks_mapping[stick] = false;
            }
        }
    }

    // 3
    for (auto iter = current.begin(); iter != current.end(); iter++)
    {
        char stick = (*iter);

        Direction *dir;
        switch (stick)
        {
        case 'R':
            dir = c->getRightStickDirection();
            if (dir->x != 0)
                holdKey(right_stick_x_mapping[dir->x]);
            if (dir->y != 0)
                holdKey(right_stick_y_mapping[dir->y]);
            break;
        case 'L':
            dir = c->getLeftStickDirection();
            if (dir->x != 0)
                holdKey(left_stick_x_mapping[dir->x]);
            if (dir->y != 0)
                holdKey(left_stick_y_mapping[dir->y]);
            break;
        }

        moving_sticks_mapping[stick] = true;
    }
}

// A map of the moving triggers.
/*
L - Left
R - Right
*/
std::map<char, bool> moving_triggers_mapping = {
    {'L', false},
    {'R', false},
};

#define TRIGGER_DEAD_ZONE 100

/*************************
    This function updates the keyboard according to the controller's triggers.
*************************/
void updateTriggers(Controller *c)
{

    // Left trigger releasing.
    if (moving_triggers_mapping['L'] == true) // The left trigger is moving.
    {
        if (c->getLeftTriggerState() < TRIGGER_DEAD_ZONE)
        {
            // We stopped moving the trigger.
            releaseKey(left_trigger_mapping);
            moving_triggers_mapping['L'] = false;
        }
    }

    // Left trigger holding.
    if (c->getLeftTriggerState() > TRIGGER_DEAD_ZONE)
    {
        pressKey(left_trigger_mapping);
        moving_triggers_mapping['L'] = true;
    }

    // Right trigger releasing.
    if (moving_triggers_mapping['R'] == true) // The right trigger is moving.
    {
        if (c->getRightTriggerState() < TRIGGER_DEAD_ZONE)
        {
            // We stopped moving the trigger.
            releaseKey(right_trigger_mapping);
            moving_triggers_mapping['R'] = false;
        }
    }

    // Right trigger holding.
    if (c->getRightTriggerState() > TRIGGER_DEAD_ZONE)
    {
        pressKey(right_trigger_mapping);
        moving_triggers_mapping['R'] = true;
    }
}

void sleep(double mili)
{
    time_t now = clock();

    while (clock() < now + mili)
        ;
}

void printMessage()
{
    cout << "*********************************************************" << endl
         << "*************                               *************" << endl
         << "************* Controller To Keyboard Mapper *************" << endl
         << "*************                               *************" << endl
         << "*************    Created by Daniel Even     *************" << endl
         << "*************                               *************" << endl
         << "*********************************************************" << endl;
}