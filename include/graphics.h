#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

bool initGraphics(int SCREEN_WIDTH,int SCREEN_HEIGHT);
bool initGL();
bool initFPSCounter();
void frameCounter();
void frameLimiter();
void refreshGraphics();
void exitGraphics();

#endif