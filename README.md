

#Instruction to buils

```bash
mkdir build
cmake..
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