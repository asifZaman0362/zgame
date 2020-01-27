# ZGAME

zgame is a lightweight game engine written in C/C++ with SFML(Simple & Fast Multimedia Library).
It primarily targets Linux systems but can run on Windows and Mac as well. Currently, it only features
2D rendering but with some OpenGL knowledge it can be extended to work with 3D as well. Feel free to 
comtribute your work to this project.

# FABQ's

Frequently asked bug related questions :-

**Q:** My window controls are lagging, what to do ?

**A:** It is probably caused by your app not having any framerate limit. This tends to happen most of the time
with non-vsynced windows so try enabling v-sync or atleast set an FPS limit.