
# Compiling

output: Main.obj Controller.obj Point.obj KeyboardManager.obj Direction.obj ConfigurationReader.obj
	link *.obj /OUT:ControllerToKeyboard.exe

Main.obj: Main.cpp
	cl /c /EHsc /nologo Main.cpp

Controller.obj: Controller.cpp
	cl /c /EHsc /nologo Controller.cpp

Point.obj: Point.cpp
	cl /c /EHsc /nologo Point.cpp

KeyboardManager.obj: KeyboardManager.cpp
	cl /c /EHsc /nologo KeyboardManager.cpp

Direction.obj: Direction.cpp
	cl /c /EHsc /nologo Direction.cpp

ConfigurationReader.obj: ConfigurationReader.cpp
	cl /c /EHsc /nologo ConfigurationReader.cpp

# Debugging

debug: Main.pdb Controller.pdb Point.pdb KeyboardManager.pdb Direction.pdb ConfigurationReader.pdb
	link *.obj

Main.pdb: Main.cpp
	cl /c /Zi /EHsc /nologo /Fe Main.cpp

Controller.pdb: Controller.cpp
	cl /c /Zi /EHsc /nologo /Fe Controller.cpp

Point.pdb: Point.cpp
	cl /c /Zi /EHsc /nologo /Fe Point.cpp

KeyboardManager.pdb: KeyboardManager.cpp
	cl /c /Zi /EHsc /nologo /Fe KeyboardManager.cpp

Direction.pdb: Direction.cpp
	cl /c /Zi /EHsc /nologo /Fe Direction.cpp

ConfigurationReader.pdb: ConfigurationReader.cpp
	cl /c /Zi /EHsc /nologo /Fe ConfigurationReader.cpp

# Cleaning

clean:
	del *.pdb *.exe *.obj *.ilk
	cls