#include "KeyboardManager.hpp"
#include "Controller.hpp"

#include <map>

// this is a map between the controller buttons and the keyboard buttons.
std::map<WORD, int> button_mapping = {
    {XINPUT_GAMEPAD_DPAD_UP, 'W'},
    {XINPUT_GAMEPAD_DPAD_DOWN, 'S'},
    {XINPUT_GAMEPAD_DPAD_LEFT, 'A'},
    {XINPUT_GAMEPAD_DPAD_RIGHT, 'D'},
    //{XINPUT_GAMEPAD_START, -1},
    //{XINPUT_GAMEPAD_BACK, -1},
    //{XINPUT_GAMEPAD_LEFT_THUMB, 1},
    //{XINPUT_GAMEPAD_RIGHT_THUMB, 1},
    //{XINPUT_GAMEPAD_LEFT_SHOULDER, 1},
    //{XINPUT_GAMEPAD_RIGHT_SHOULDER, 1},
    {XINPUT_GAMEPAD_A, VK_DOWN},
    //{XINPUT_GAMEPAD_B, 1},
    //{XINPUT_GAMEPAD_X, 1},
    //{XINPUT_GAMEPAD_Y, 1}
};

std::map<int, int> left_stick_x_mapping = {
    {1, VK_RIGHT},
    {-1, VK_LEFT}};

std::map<int, int> left_stick_y_mapping = {
    {1, -1},
    {-1, -1}};

std::map<int, int> right_stick_x_mapping = {
    {1, -1},
    {-1, -1}};

std::map<int, int> right_stick_y_mapping = {
    {1, -1},
    {-1, -1}};