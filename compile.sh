#!/bin/bash
clear
clang -g *.c -o dooke -I ./ -I ./SDL2_Linux/include/ -lm -L ./SDL2_Linux/lib/ -lSDL2 -lSDL2_image -L ./libft/ -lft