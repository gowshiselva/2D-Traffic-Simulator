This is a project created for the capstone project for the course ELEC-A7151 - Object oriented programming with C++ from Aalto univeristy. 

#Requirements:
Packages required: (install with apt-get for example)
```bash
cmake g++ libsfml-dev python3-dev python3-pip
```
Also using matplotlibcpp requires matplot being installed to your python3 environment:
```bash
pip3 install matplotlib
```

#Instruction to builds

```bash
mkdir build
cd build
cmake ..
make
./traffic-simulator
```

#Guide to install X-server
Install an Xserver for windows
```bash
sudo apt install freerdp2-x11
xfreerdp ...
"export DISPLAY=:0"
```
The idea is the window should have xserver installed. e.g vcxsrc. The the client from linux (e.g wsl ) should have client server to communicate witht that. e.g xfreerdp
#clean build
To clean this project you can simply recursively delete all files/directories within the build directory, for example:

```bash
cd ..x
rm -rf build/
```