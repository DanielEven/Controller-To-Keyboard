
# Compiling

output: Test.obj Controller.obj Point.obj
	link *.obj

Test.obj: Test.cpp
	cl /c /EHsc Test.cpp

Controller.obj: Controller.cpp
	cl /c Controller.cpp

Point.obj: Point.cpp
	cl /c Point.cpp


# Debugging

debug: Test.pdb Controller.pdb Point.pdb
	link *.obj

Test.pdb: Test.cpp
	cl /c /Zi /EHsc /nologo /Fe Test.cpp

Controller.pdb: Controller.cpp
	cl /c /Zi /EHsc /nologo /Fe Controller.cpp

Point.pdb: Point.cpp
	cl /c /Zi /EHsc /nologo /Fe Point.cpp


# Cleaning

clean:
	del *.pdb *.exe *.obj *.ilk