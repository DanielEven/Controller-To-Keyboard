# Controller-To-Keyboard🎮⌨

> :warning: **The use of the software is at your own risk:** espacially using high game controller vibration rates. <br />

This is a program to use a game controller as a keyboard, written in c++ using the windows API.<br />
The program uses the _Xipnut.h_ library in order to get inputs from the game controller. The program uses _windows.h_ in order to simulate to keyboard pressing.
## How to use the program
1. Build the program using the _makefile_.🔨
2. Connect a game controller.🎮
3. Configure the mapping between the game controller buttons and the keyboard.📜
## How to configure the mapping between the controller and the keyboard📝
Edit the _.conf_ files under the directory src/config, and add your configurations to the buttons, sticks and triggers.
### Button configuration format
The format is:<br />
*BUTTON_NAME KEY*<br />
You can choose from the following buttons:
Up,
Down,
Left,
Right,
Start,
Back,
Press_Left,
Press_Right,
Back_Left,
Back_Right,
A,
B,
X,
Y.
### Stick configuration format
The format is:<br />
*STICK DIRECTION KEY*<br />
Each one of the STICK and the DIRECTION should be Left/Right.
### Trigger configuration format
The format is:<br />
*TRIGGER KEY*<br />
The TRIGGER should be Left/Right.
### Supported keys list
The KEY parameter should be from the following list:<br />
Add, 
Back, 
Caps_lock, 
Comma, 
Delete, 
Devide, 
Down, 
End, 
Enter, 
Home, 
Insert, 
Left, 
Left_control, 
Left_mouse, 
Left_shift, 
Left_windows, 
Middle_mouse, 
Mouse_button 1, 
Mouse_button 2, 
Multiply, 
Num_lock, 
Page_down, 
Page_up, 
Pause, 
Period, 
Right, 
Right_control, 
Right_mouse, 
Right_shift, 
Right_windows, 
Scroll_lock, 
Space, 
Subtract, 
Tab, 
Up.
