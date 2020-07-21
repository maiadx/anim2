#!/bin/bash

sudo mkdir /usr/share/anim2;
sudo mkdir /usr/include/Anim2;
sudo mkdir /usr/share/anim2/Models;
sudo mkdir /usr/share/anim2/Shaders;

sudo cp ./Bin/Release/Anim /usr/bin/anim2;
sudo cp ./Anim/Include/Anim.h /usr/include/Anim2/Anim.h

sudo cp ./Resources/Models/volleyball.obj /usr/share/anim2/Models/volleyball.obj
sudo cp -r ./Resources/Shaders/* /usr/share/anim2/Shaders/
