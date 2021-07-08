#include <windows.h>
#include <Xinput.h>

class Controller
{
private:
    XINPUT_STATE state;
    boolean connected;

    boolean updateState();

public:
    Controller();

    // Getting information about the controller.
    boolean isConnected();
    
};