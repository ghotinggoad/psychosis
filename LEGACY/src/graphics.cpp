#include "../include/global.h"

// Window we're rendering to
SDL_Window* window = NULL;
// OpenGL Context
SDL_GLContext glContext;
// Surfaces are rendered by the CPU (meaning software rendered), "contains pixels of an image along with all data needed to render it"
// The following renderer is the rendered surface shown in the mainwindow
SDL_Renderer* renderer = NULL;


// fpsTexture = texture used to store rendered text, fpsFont = storing umeboshi_.ttf font file for FPS
cTexture fpsTexture;
TTF_Font* fpsFont;

// timer used to measure time between frames, used for delay to attain inaccurate FPS lock
cTimer frameLimitTimer;
// timer and count used to measure FPS
cTimer frameCountTimer;
int frameCount = 0;

struct vec3d{
    float x, y, z;
};

struct triangle{
    vec3d p[3];
};

struct mesh{
    std::vector<triangle> tris;
};

struct mat4x4{
    float m[4][4] = {0};
};

mesh meshCube;
mat4x4 matProj;
float fTheta;

float fRotX, fRotY, fRotZ;

// initialize SDL2 windows and graphics handler, also PNG and TTF dependencies
bool initGraphics(int SCREEN_WIDTH,int SCREEN_HEIGHT){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        // create window
        window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL ){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        // IMG_Init will return the value that was parsed to it if successful
        if(!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG){
            printf("SDL_image libraries cannot be initialized! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
        else{
            // create a renderer that is hardware accelerated
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
        if(TTF_Init() == -1){
            printf("SDL_ttf libraries cannot be initialized! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }
    success = initGL();
    success = initFPSCounter();
    

    return success;
}

bool initGL(){
    bool success = true;
    GLenum error = GL_NO_ERROR;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    glContext = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;

    glewInit();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    error = glGetError();
    if(error != GL_NO_ERROR) success = false;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    error = glGetError();
    if(error != GL_NO_ERROR) success = false;
    SDL_GL_SetSwapInterval(0);

    meshCube.tris = {
        // https://www.youtube.com/watch?v=ih20l3pJoeU

        // The coordinates here are different from javidx9's example because I want to rotate the cube around its center 
        // and rotation matrix rotate the coordiantes around its origin.
        // Make sure the 3D models' center is the origin before rotating, else it'll look like it's swinging.

		// SOUTH
		{ -0.5f, -0.5f, -0.5f,    -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, -0.5f },
		{ -0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, -0.5f, -0.5f },
		// EAST                                                      
		{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f },
		{ 0.5f, -0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, -0.5f, 0.5f },
		// NORTH                                                     
		{ 0.5f, -0.5f, 0.5f,    0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, 0.5f },
		{ 0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, -0.5f, 0.5f },
		// WEST                                                      
		{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, 0.5f,    -0.5f, 0.5f, -0.5f },
		{ -0.5f, -0.5f, 0.5f,    -0.5f, 0.5f, -0.5f,    -0.5f, -0.5f, -0.5f },
		// TOP                                                       
		{ -0.5f, 0.5f, -0.5f,    -0.5f, 0.5f, 0.5f,    0.5f, 0.5f, 0.5f },
		{ -0.5f, 0.5f, -0.5f,    0.5f, 0.5f, 0.5f,    0.5f, 0.5f, -0.5f },
		// BOTTOM                                                    
		{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f },
		{ 0.5f, -0.5f, 0.5f,    -0.5f, -0.5f, -0.5f,    0.5f, -0.5f, -0.5f }
	};

    // Projection Matrix
	float fNear = 0.1f;
	float fFar = 1000.0f;
    // 103 degrees because overwatch.
	float fFov = 103.0f;
	float fAspectRatio = (float)SCREEN_HEIGHT / (float)SCREEN_WIDTH;
	float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);



	matProj.m[0][0] = fAspectRatio * fFovRad;
	matProj.m[1][1] = fFovRad;
	matProj.m[2][2] = fFar / (fFar - fNear);
	matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = 0.0f;


    return success;
}

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w; o.y /= w; o.z /= w;
	}
}

void rotateCube(){
    // Set up rotation matrices
	mat4x4 matRotX, matRotY, matRotZ; 
	fTheta += 1.0f/50;
    fRotX = 0.5f; 
    fRotY = 1.0f;
    fRotZ = 0.0f;

	// Rotation X
	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(fTheta*fRotX);
	matRotX.m[1][2] = sinf(fTheta*fRotX);
	matRotX.m[2][1] = -sinf(fTheta*fRotX);
	matRotX.m[2][2] = cosf(fTheta*fRotX);
	matRotX.m[3][3] = 1;

    // Rotation Y
    matRotY.m[0][0] = cosf(fTheta*fRotY);
    matRotY.m[0][2] = sinf(fTheta*fRotY);
    matRotY.m[1][1] = 1;
    matRotY.m[2][0] = -sinf(fTheta*fRotY);
    matRotY.m[2][2] = cosf(fTheta*fRotY);
	matRotY.m[3][3] = 1;

	// Rotation Z
	matRotZ.m[0][0] = cosf(fTheta*fRotZ);
	matRotZ.m[0][1] = sinf(fTheta*fRotZ);
	matRotZ.m[1][0] = -sinf(fTheta*fRotZ);
	matRotZ.m[1][1] = cosf(fTheta*fRotZ);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	// Draw Triangles
	for (auto tri : meshCube.tris)
	{
		triangle triProjected, triTranslated, triRotatedX, triRotatedXY, triRotatedXYZ;
		// Rotate in X-Axis
		MultiplyMatrixVector(tri.p[0], triRotatedX.p[0], matRotX);
		MultiplyMatrixVector(tri.p[1], triRotatedX.p[1], matRotX);
		MultiplyMatrixVector(tri.p[2], triRotatedX.p[2], matRotX);

		// Rotate in Y-Axis
		MultiplyMatrixVector(triRotatedX.p[0], triRotatedXY.p[0], matRotY);
		MultiplyMatrixVector(triRotatedX.p[1], triRotatedXY.p[1], matRotY);
		MultiplyMatrixVector(triRotatedX.p[2], triRotatedXY.p[2], matRotY);

		// Rotate in Z-Axis
		MultiplyMatrixVector(triRotatedXY.p[0], triRotatedXYZ.p[0], matRotZ);
		MultiplyMatrixVector(triRotatedXY.p[1], triRotatedXYZ.p[1], matRotZ);
		MultiplyMatrixVector(triRotatedXY.p[2], triRotatedXYZ.p[2], matRotZ);

		// Offset into the screen
		triTranslated = triRotatedXYZ;
		triTranslated.p[0].z = triRotatedXYZ.p[0].z + 1.5f;
		triTranslated.p[1].z = triRotatedXYZ.p[1].z + 1.5f;
		triTranslated.p[2].z = triRotatedXYZ.p[2].z + 1.5f;

		// Project triangles from 3D --> 2D
		MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], matProj);
		MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], matProj);
		MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], matProj);

		// Scale into view
		triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
		triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
		triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;
		triProjected.p[0].x *= 0.5f * (float)SCREEN_WIDTH;
		triProjected.p[0].y *= 0.5f * (float)SCREEN_HEIGHT;
		triProjected.p[1].x *= 0.5f * (float)SCREEN_WIDTH;
		triProjected.p[1].y *= 0.5f * (float)SCREEN_HEIGHT;
		triProjected.p[2].x *= 0.5f * (float)SCREEN_WIDTH;
		triProjected.p[2].y *= 0.5f * (float)SCREEN_HEIGHT;

		// Rasterize triangle
		/*
		DrawTriangle(triProjected.p[0].x, triProjected.p[0].y,
			triProjected.p[1].x, triProjected.p[1].y,
			triProjected.p[2].x, triProjected.p[2].y,
			PIXEL_SOLID, FG_WHITE);
        */
        SDL_Point triangleVectorPoints[4] = {
            {triProjected.p[0].x, triProjected.p[0].y},
            {triProjected.p[1].x, triProjected.p[1].y},
            {triProjected.p[2].x, triProjected.p[2].y},
            {triProjected.p[0].x, triProjected.p[0].y}
        };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLines(renderer, triangleVectorPoints, 4);
    }
};

bool initFPSCounter(){
    frameCountTimer.start();
    frameLimitTimer.start();
    // sets text color of loaded font texture to 
    fpsTexture.setTextColor(255, 255, 255);
    // load TTF to font, the int behind refers to DPI
    fpsFont = TTF_OpenFont("./media/umeboshi_.ttf", SCREEN_WIDTH/24);
    if(fpsFont == NULL) printf("/media/umeboshi_.ttf cannot be loaded!");
    // Change font style, includes TTF_STYLE_NORMAL, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE, TTF_STYLE_STRIKETHROUGH
    TTF_SetFontStyle(fpsFont, TTF_STYLE_BOLD);
    return fpsFont != NULL;
}

void frameCounter(){
    // framesCount is added every render cycle, divided by 1000ms to get FPS
    int avgFPS = frameCount/(frameCountTimer.getTicks()/1000.f);
    fpsTexture.renderText(0, 0, std::to_string(avgFPS).append("FPS"), fpsFont, 0.0, NULL, SDL_FLIP_NONE);
    // this resets the FPS counter every 2.5 seconds, to retain accuracy after program has been running for a long time
    if(frameCount > REFRESH_RATE*2.5){
        frameCountTimer.start();
        frameCount = 0;
    }
    frameCount++;
}

// non-vsync method
void frameLimiter(){
    int frameRemainingTicks = frameLimitTimer.getTicks();
    if(frameRemainingTicks < FRAME_TIME) SDL_Delay(FRAME_TIME - frameRemainingTicks);
    // restarted frameLimitTimer so that frameRemainingTicks will ideally be between 0 and FRAME_TIME every single loop
    frameLimitTimer.start();
}

// this is used to render all graphics wrapper function before game specific renders onto it.
void refreshGraphics(){
    frameCounter();
    frameLimiter();
    // SDL_Delay(16);
    SDL_RenderPresent(renderer);
}

void exitGraphics(){
    // Free loaded texture
    fpsTexture.destroyTexture();
    // Free fonts
    TTF_CloseFont(fpsFont);
    fpsFont = NULL;

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}