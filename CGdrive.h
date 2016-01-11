#ifndef cgdrive_h
#define cgdrive_h
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <time.h>
#include <sstream>
#include <Windows.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "SOIL.h"
#pragma comment (lib, "glew32d.lib")
#pragma comment(lib,"lib\\SOIL.lib")
#define IBL 0
#define FLOOR 1
#define WALL 2
#define BED 3
#define WHALE 4
#define ITEM 5
#define MAXTEX 32
#define NUM_SHADERS 1
#define NUM_WALL 18//15+3
#define CUBE_WIDTH 1.0
#define CUBE_HEIGHT 2.0

extern int textpoint;
extern unsigned int textureObjects[MAXTEX];
extern GLuint programs[NUM_SHADERS];
extern int currentShader;
extern int wallunit;
extern bool objExist[19][14];
extern bool bNurb;

void attachMaterial(int ID, int tex, GLint currentProgram);
void attachMaterial(int ID, GLint currentProgram);



#endif