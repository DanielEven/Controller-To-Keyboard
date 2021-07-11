#include "ConfigurationReader.hpp"
#include "Controller.hpp"
#include "KeyboardManager.hpp"

#include <iostream> //temp
#include <fstream>
#include <sstream>
#include <map>

extern std::map<WORD, int> button_mapping;
extern std::map<int, int> left_stick_x_mapping;
extern std::map<int, int> left_stick_y_mapping;
extern std::map<int, int> right_stick_x_mapping;
extern std::map<int, int> right_stick_y_mapping;
extern int left_trigger_mapping;
extern int right_trigger_mapping;

void setConfigurations()
{
    setButtonConfigurations();
    setStickConfigurations();
    setTriggerConfigurations();
}

void setButtonConfigurations()
{
    ifstream file;
    file.open("config/button.conf");

    if (!file.is_open())
        return;

    string line;
    while (std::getline(file, line))
    {
        vector<string> two = split(line, ' ');
        cout << two.at(0) << endl
             << two.at(1);
    }
}

void setStickConfigurations()
{
}

void setTriggerConfigurations()
{
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