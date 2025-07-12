@echo off
del main.exe
g++ main.cpp palavras.cpp util.cpp -I ./include -L ./lib -l SDL3 -l SDL3_ttf -o main.exe
main.exe