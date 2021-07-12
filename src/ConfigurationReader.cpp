#include "ConfigurationReader.hpp"
#include "Controller.hpp"
#include "KeyboardManager.hpp"

#include <fstream>
#include <sstream>
#include <map>

// Declaring about the maps from Mapping.hpp
extern std::map<WORD, int> button_mapping;
extern std::map<int, int> left_stick_x_mapping;
extern std::map<int, int> left_stick_y_mapping;
extern std::map<int, int> right_stick_x_mapping;
extern std::map<int, int> right_stick_y_mapping;
extern int left_trigger_mapping;
extern int right_trigger_mapping;

void finishSetKeyNames();

bool good_configuration = true;

bool setConfigurations()
{
    finishSetKeyNames();

    setButtonConfigurations();
    setStickConfigurations();
    setTriggerConfigurations();

    return good_configuration;
}

// key names.
std::map<string, WORD> key_name_mapping = {
    {"Left_mouse", VK_LBUTTON},
    {"Right_mouse", VK_RBUTTON},
    {"Middle_mouse", VK_MBUTTON},
    {"Mouse_button 1", VK_XBUTTON1},
    {"Mouse_button 2", VK_XBUTTON2},

    {"Back", VK_BACK},
    {"Tab", VK_TAB},
    {"Enter", VK_RETURN},
    {"Left_shift", VK_LSHIFT},
    {"Right_shift", VK_RSHIFT},
    {"Left_control", VK_LCONTROL},
    {"Right_control", VK_RCONTROL},
    {"Space", VK_SPACE},
    {"Left_windows", VK_LWIN},
    {"Right_windows", VK_RWIN},

    {"Pause", VK_PAUSE},
    {"Caps_lock", VK_CAPITAL},
    {"Num_lock", VK_NUMLOCK},
    {"Scroll_lock", VK_SCROLL},

    {"Insert", VK_INSERT},
    {"Delete", VK_DELETE},
    {"Page_up", VK_PRIOR},
    {"Page_down", VK_NEXT},
    {"End", VK_END},
    {"Home", VK_HOME},

    {"Left", VK_LEFT},
    {"Up", VK_UP},
    {"Right", VK_RIGHT},
    {"Down", VK_DOWN},

    {"Add", VK_ADD},
    {"Subtract", VK_SUBTRACT},
    {"Multiply", VK_MULTIPLY},
    {"Devide", VK_DIVIDE},

    {"Period", VK_OEM_PERIOD},
    {"Comma", VK_OEM_COMMA},
};

void finishSetKeyNames()
{
    // Numbers
    for (char c = '0'; c <= '9'; c++)
    {
        string s{c};
        key_name_mapping[s] = c;
    }

    // Letters
    for (char c = 'A'; c <= 'Z'; c++)
    {
        string s{c};
        key_name_mapping[s] = c;
    }

    // Number Pad
    for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; i++)
    {
        string s = to_string(i - 0x30);
        key_name_mapping["Number_pad" + s] = i;
    }

    // F#
    for (int i = VK_F1; i <= VK_F24; i++)
    {
        string s = to_string(i - 0x3F);
        key_name_mapping["F" + s] = i;
    }
}

// Button names.
std::map<string, WORD> button_name_mapping = {
    {"Up", XINPUT_GAMEPAD_DPAD_UP},
    {"Down", XINPUT_GAMEPAD_DPAD_DOWN},
    {"Left", XINPUT_GAMEPAD_DPAD_LEFT},
    {"Right", XINPUT_GAMEPAD_DPAD_RIGHT},
    {"Start", XINPUT_GAMEPAD_START},
    {"Back", XINPUT_GAMEPAD_BACK},
    {"Press_Left", XINPUT_GAMEPAD_LEFT_THUMB},
    {"Press_Right", XINPUT_GAMEPAD_RIGHT_THUMB},
    {"Back_Left", XINPUT_GAMEPAD_LEFT_SHOULDER},
    {"Back_Right", XINPUT_GAMEPAD_RIGHT_SHOULDER},
    {"A", XINPUT_GAMEPAD_A},
    {"B", XINPUT_GAMEPAD_B},
    {"X", XINPUT_GAMEPAD_X},
    {"Y", XINPUT_GAMEPAD_Y}};

void setButtonConfigurations()
{
    ifstream file;
    file.open("config/button.conf");

    if (!file.is_open())
    {
        fileDoesNotExistMessage("config/button.conf");
        return;
    }

    string line;
    while (std::getline(file, line))
    {
        vector<string> two = split(line, ' ');

        if (two.size() == 0)
            continue;
        if (two.size() != 2)
        {
            wrongFileFormatMessage("config/button.conf");
            return;
        }

        string button_name = two.at(0);
        string key_name = two.at(1);

        WORD button = button_name_mapping[button_name];
        int key = key_name_mapping[key_name];
        if (button == 0 || key == 0)
        {
            wrongFileFormatMessage("config/button.conf");
            return;
        }

        button_mapping[button] = key;
    }
}

void setStickConfigurations()
{
    ifstream file;
    file.open("config/stick.conf");

    if (!file.is_open())
    {
        fileDoesNotExistMessage("config/stick.conf");
        return;
    }

    string line;
    while (std::getline(file, line))
    {
        vector<string> three = split(line, ' ');

        if (three.size() == 0)
            continue;
        if (three.size() != 3)
        {
            wrongFileFormatMessage("config/stick.conf");
            return;
        }

        string stick_name = three.at(0);
        string dir_name = three.at(1);
        string key_name = three.at(2);

        int key = key_name_mapping[key_name];
        if (key == 0)
        {
            wrongFileFormatMessage("config/stick.conf");
            return;
        }

        if (stick_name == "Right")
        {
            if (dir_name == "Right")
            {
                right_stick_x_mapping[1] = key;
            }
            else if (dir_name == "Left")
            {
                right_stick_x_mapping[-1] = key;
            }
            else if (dir_name == "Up")
            {
                right_stick_y_mapping[1] = key;
            }
            else if (dir_name == "Down")
            {
                right_stick_y_mapping[-1] = key;
            }

            else
            {
                wrongFileFormatMessage("config/stick.conf");
                return;
            }
        }
        else if (stick_name == "Left")
        {
            if (dir_name == "Right")
            {
                left_stick_x_mapping[1] = key;
            }
            else if (dir_name == "Left")
            {
                left_stick_x_mapping[-1] = key;
            }
            else if (dir_name == "Up")
            {
                left_stick_y_mapping[1] = key;
            }
            else if (dir_name == "Down")
            {
                left_stick_y_mapping[-1] = key;
            }

            else
            {
                wrongFileFormatMessage("config/stick.conf");
                return;
            }
        }
        else
        {
            wrongFileFormatMessage("config/stick.conf");
            return;
        }
    }
}

void setTriggerConfigurations()
{
    ifstream file;
    file.open("config/trigger.conf");

    if (!file.is_open())
    {
        fileDoesNotExistMessage("config/trigger.conf");
        return;
    }

    string line;
    while (std::getline(file, line))
    {
        vector<string> two = split(line, ' ');

        if (two.size() == 0)
            continue;
        if (two.size() != 2)
        {
            wrongFileFormatMessage("config/trigger.conf");
            return;
        }

        string trigger = two.at(0);
        string key_name = two.at(1);

        int key = key_name_mapping[key_name];
        if (key == 0)
        {
            wrongFileFormatMessage("config/trigger.conf");
            return;
        }

        if (trigger == "Left")
        {
            left_trigger_mapping = key;
        }
        else if (trigger == "Right")
        {
            right_trigger_mapping = key;
        }
        else
        {
            wrongFileFormatMessage("config/trigger.conf");
            return;
        }
    }
}

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    std::stringstream ss(s);
    string item;

    while (std::getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

void fileDoesNotExistMessage(string filename)
{
    cout << "The file " << filename << " does not exit." << endl;
    good_configuration = false;
}

void wrongFileFormatMessage(string filename)
{
    // throw std::invalid_argument("The file format of " + filename + " is wrong!");
    cout << "The file format of " << filename << " is wrong." << endl;
    good_configuration = false;
}