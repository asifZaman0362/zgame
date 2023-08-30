# zgame
A simple and lightweight game framework written from scratch. zgame uses OpenGL for rendering and compiles on linux, win 10+ and latest MacOS. zgame also has its own simple ECS
implementation which should make manipulation of a large number of entities faster. 

### Compiling
#### Linux
If using nix, a shell.nix is provided which should setup a transient shell with all dependencies (excluding cmake). For non-nix users, the following packages are required:
  * glfw3
  * glm

these packages should be available in most package managers.

```sh
mkdir build
cd build
cmake ..
make
```

#### MacOS
First compile and install GLFW3 from source.
Other dependencies are included with the project.

```sh
mkdir build
cd build
cmake ..
make
```

#### Windows (Visual Studio 2022)
Other VS versions may also work but that would require replacing the libraries with the appropriate version compatible with target VS.
[Download](https://www.glfw.org/download.html) the precompiled binary for glfw for windows, look for your target VS version inside the lib folder. Copy the library files into external/lib/windows.
Open the project in Visual Studio and go through the initial CMake setup on screen. Once done, select "zgame.exe" as the executable target and start debugging to build and run.

### Contributing
Any and all suggestions are welcome. This is very early and only a hobby project and is probably not going to be very active.
