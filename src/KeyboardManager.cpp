#include "KeyboardManager.hpp"

bool pressKey(int key)
{
    INPUT inputs[2] = {};
    ZeroMemory(inputs, sizeof(inputs));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    UINT sent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    return sent == ARRAYSIZE(inputs);
}

bool pressMultipleKeys(std::vector<int> keys)
{
    const int arr_size = keys.size() * 2;

    INPUT *inputs = new INPUT[arr_size];
    ZeroMemory(inputs, arr_size * sizeof(INPUT));

    for (int i = 0; i < keys.size(); i++)
    {
        // Press
        inputs[i].type = INPUT_KEYBOARD;
        inputs[i].ki.wVk = keys.at(i);

        // key Up
        inputs[arr_size - i - 1].type = INPUT_KEYBOARD;
        inputs[arr_size - i - 1].ki.wVk = keys.at(i);
        inputs[arr_size - i - 1].ki.dwFlags = KEYEVENTF_KEYUP;
    }

    UINT sent = SendInput(arr_size, inputs, sizeof(INPUT));

    return sent == arr_size;
}