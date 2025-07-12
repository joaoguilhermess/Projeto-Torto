@echo off
del main.exe
g++ main.cpp palavras.cpp util.cpp -o main.exe
main.exe