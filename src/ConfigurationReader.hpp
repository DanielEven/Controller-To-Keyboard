#include <string>
#include <vector>
#include <map>

typedef unsigned short WORD;

using namespace std;

// Functions to read the configurations from files.

// A function that sets all of the configurations from the configuration files.
// The function returns true if the configurations are all right.
bool setConfigurations();

// A function that sets all of the button configurations from the configuration files.
void setButtonConfigurations();

// A function that sets all of the stick configurations from the configuration files.
void setStickConfigurations();

// A function that sets all of the trigger configurations from the configuration files.
void setTriggerConfigurations();

// Helper functions.

// A helper function to split a string with a delimiter.
vector<string> split(const string &s, char delim);

// A helper function for the case when a configuration file doesn't exit.
void fileDoesNotExistMessage(string filename);

// A helper function for the case when the configuration file's format is wrong.
void wrongFileFormatMessage(string filename);
