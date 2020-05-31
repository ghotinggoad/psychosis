# psychosis
Retro 3D game from scratch (perpetual WIP)
There will be a lot of seemingly meaningless updates (about once per day) because I basically use this to synchronize my progress between computers.

TO-DO (in order):
- ~~port to glfw & glad build environment~~
- FPS Lock with code runtime independent frame refresh rate
- image scaling for multiple resolution (I think it's pointless now, will delete when I confirm this.)
- sound with OpenAL
- ~~reimplementation of shitai?~~
- object rotation and interaction like HPL Engine (based on their source code, willing to spend a lot of time)
- non-euclidean world mechanics based on HackerPoet's implementation
- something like penumbra

### Build Dependencies
- build-essential (Ubuntu 20.04)
- mingw-w64
- libglfw3-dev
- libgl1-mesa-dev
- xorg-dev

### Libraries Used
- glad 0.1.33 (OpenGL 4.6 Core, 3.3 Core will work fine.)
- glfw 3.3.2
- glm 0.9.9.8

### References
https://learnopengl.com/

^ learnt how to setup environment to build glfw, glad and almost everything from here, thanks I love you.


http://nuclear.mutantstargoat.com/articles/make/

^ learnt how to write makefiles from here, 

https://qiita.com/nullpo24/items/716bad137f1264b776f5

^ macros from here.


https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet

^ README formatting guide.


https://www.youtube.com/watch?v=ih20l3pJoeU

^ Javidx9's tutorial on initializing 3D program required data types and projection matrix from here, god sent.
