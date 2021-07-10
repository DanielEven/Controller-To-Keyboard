#include "Controller.hpp"
#include "Mapping.hpp"
#include "KeyboardManager.hpp"
#include <set>

void updateButtons(Controller *c);

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

int main()
{
    Controller *c = new Controller();

    updateButtons(c);

    return 0;
}

/*************************
    This function updates the keyboard according to the controller's buttons.

    Steps:
    1. Create the current button set.
    2. Checking if there are released buttons.
    3. Pressing the new buttons.
*************************/
void updateButtons(Controller *c)
{
    while (!c->isButtonPressed(XINPUT_GAMEPAD_BACK))
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

        //2
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
            if (pressed_mapping[button] == false) // if the button isn't already pressed.
            {
                holdKey(button_mapping[button]);
                pressed_mapping[button] = true;
            }
        }
    }
}