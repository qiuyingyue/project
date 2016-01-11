//
//  Skybox.h
//  opengltest
//
//  Created by Victor Young on 1/11/16.
//  Copyright (c) 2016 Victor Young. All rights reserved.
//

#ifndef __opengltest__Skybox__
#define __opengltest__Skybox__

#include "CGdrive.h"
/*  Skybox Textures  */
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5

void drawScene();
void drawSkybox(double D);
void initSkybox(void);



#endif /* defined(__opengltest__Skybox__) */
