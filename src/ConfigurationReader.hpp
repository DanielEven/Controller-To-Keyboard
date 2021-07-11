#include <string>
#include <vector>

typedef unsigned short WORD;

using namespace std;

// Functions to read the configurations from files.

// A function that sets all of the configurations from the configuration files.
void setConfigurations();

// A function that sets all of the button configurations from the configuration files.
void setButtonConfigurations();

// A function that sets all of the stick configurations from the configuration files.
void setStickConfigurations();

// A function that sets all of the trigger configurations from the configuration files.
void setTriggerConfigurations();

// A helper function to split a string with a delimiter.
vector<string> split(const string &s, char delim);