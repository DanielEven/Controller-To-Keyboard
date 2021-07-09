#include <windows.h>
#include <algorithm>
#include <vector>

#pragma comment(lib, "user32.lib")

// A function that simulates a press on one key.
bool pressKey(int key);

// A function that simulates a press on multiple keys.
// The function simulates a press on the keys from the array, and then releases all of them.
// the keys are pressed according to the order of the array.
bool pressMultipleKeys(std::vector<int> keys);