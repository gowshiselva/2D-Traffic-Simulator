

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
"export DISPLAY=localhost0.0"
```

#clean build
To clean this project you can simply recursively delete all files/directories within the build directory, for example:

```bash
cd ..
rm -rf build/
```