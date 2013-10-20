call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat"
cl/EHsc %1 /Fetemp.exe
temp.exe
del *.obj
del *.exe