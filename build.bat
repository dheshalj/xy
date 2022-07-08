@echo off

mkdir bin>nul 2>&1
mkdir dist>nul 2>&1

echo Building Intermediate Binaries...
g++ xy.cpp -o bin/xy.o -c
g++ ini/ini.c -o bin/ini.o -c
g++ ini/INIReader.cpp -o bin/INIReader.o -c

echo Building Binary...
g++ -o dist/xy bin/xy.o bin/ini.o bin/INIReader.o

echo:
echo Done!